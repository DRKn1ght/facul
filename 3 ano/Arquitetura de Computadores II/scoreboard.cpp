#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#define MAX_INSTRUCTION 1000
#define MAX_REG 12
#define MAX_UNIT 5

#define TRUE "True"
#define FALSE "False"
#define NONE ""

#define INTEGER 0
#define MULT1 1
#define MULT2 2
#define ADD 3
#define DIVIDE 4

struct latencies
{
    int ld = 1;
    int muld = 10;
    int divd = 40;
    int subd = 2;
    int addd = 2;
} Latencies;

struct instructionList
{
    string const validInstructions[MAX_UNIT] = {"ld", "multd", "divd", "subd", "addd"};
    string instruction, regDestino, regBase, regBaseLd, regOperando1, regOperando2;
    int offset, count = 0, processing = 0;
} InstructionList[MAX_INSTRUCTION];

struct instructionStatus
{
    int issue, readOperand, executionOperand, writeResult;
    int issueCount = 0, finalizedCount = 0, functionalUnit = -1;
    int clock = 0;
    vector<int>finalizedList;
} InstructionStatus[MAX_INSTRUCTION];

struct functionalUnitStatus
{
    string const unitList[MAX_UNIT] = {"Integer", "Mult1", "Mult2", "Add", "Divide"};
    string busy = FALSE, rj, rk;
    string op, fi, fj, fk, qj, qk;
    int functionalUnit = -1;
} FunctionalUnitStatus[MAX_UNIT];

struct registerStatus
{
    string status;
} RegisterStatus[MAX_REG];

string IsBusy(int functionalUnit)
{
    return FunctionalUnitStatus[functionalUnit].busy;
}
int RegToInt(string reg)
{
    if (reg == "rb")
        return MAX_REG;
    return stoi(reg.substr(1, reg.length() - 1)) - 1;
}

void ClearFunctionalUnit(int functionalUnit)
{
    string fi = FunctionalUnitStatus[functionalUnit].fi;
    int reg;
    FunctionalUnitStatus[functionalUnit].busy = FALSE;
    FunctionalUnitStatus[functionalUnit].op = NONE;
    FunctionalUnitStatus[functionalUnit].fi = NONE;
    FunctionalUnitStatus[functionalUnit].fj = NONE;
    FunctionalUnitStatus[functionalUnit].fk = NONE;
    FunctionalUnitStatus[functionalUnit].qj = NONE;
    FunctionalUnitStatus[functionalUnit].qk = NONE;
    FunctionalUnitStatus[functionalUnit].rj = NONE;
    FunctionalUnitStatus[functionalUnit].rk = NONE;
    FunctionalUnitStatus[functionalUnit].functionalUnit = -1;
    reg = RegToInt(fi);
    RegisterStatus[reg].status = NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].qj == FunctionalUnitStatus->unitList[functionalUnit]){
            FunctionalUnitStatus[i].qj = NONE;
            FunctionalUnitStatus[i].rj = TRUE;
        }
        if (FunctionalUnitStatus[i].qk == FunctionalUnitStatus->unitList[functionalUnit]){
            FunctionalUnitStatus[i].qk = NONE;
            FunctionalUnitStatus[i].rk = TRUE;
        }
    }
}

string CheckRj(int functionalUnit)
{
    string fj = FunctionalUnitStatus[functionalUnit].fj;
    if (fj == NONE)
        return NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].busy == TRUE && functionalUnit != i)
        {
            if (FunctionalUnitStatus[i].fi == fj)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

string CheckRk(int functionalUnit)
{
    string fk = FunctionalUnitStatus[functionalUnit].fk;

    if (fk == NONE)
        return NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].busy == TRUE && functionalUnit != i)
        {
            if (FunctionalUnitStatus[i].fi == fk)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

string GetQj(int functionalUnit)
{
    string fj = FunctionalUnitStatus[functionalUnit].fj;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].busy == TRUE && functionalUnit != i)
        {
            if (FunctionalUnitStatus[i].fi == fj)
            {
                return FunctionalUnitStatus->unitList[i];
            }
        }
    }
    return NONE;
}

string GetQk(int functionalUnit)
{
    string fk = FunctionalUnitStatus[functionalUnit].fk;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].busy == TRUE && functionalUnit != i)
        {
            if (FunctionalUnitStatus[i].fi == fk)
            {
                return FunctionalUnitStatus->unitList[i];
            }
        }
    }
    return NONE;
}

bool CheckHazard(int instruction)
{
    int functionalUnit = InstructionStatus[instruction].functionalUnit;
    if (functionalUnit == -1)
        return false;
    if (FunctionalUnitStatus[functionalUnit].qj != NONE || FunctionalUnitStatus[functionalUnit].qk != NONE)
        return true;
    return false;
}

int UpdateFunctionalUnitStatus(int instruction)
{
    int functionalUnit;
    string op = InstructionList[instruction].instruction;
    string fi = InstructionList[instruction].regDestino;
    string fj = InstructionList[instruction].regOperando1;
    string fk = InstructionList[instruction].regOperando2;
    string qj, qk, rj, rk;
    if (op == "ld")
    {
        functionalUnit = INTEGER;
        fk = InstructionList[instruction].regBaseLd;
    }
    else if (op == "muld")
    {
        functionalUnit = MULT1;
        if (IsBusy(functionalUnit) == TRUE)
            functionalUnit = MULT2;
    }
    else if (op == "divd")
    {
        functionalUnit = DIVIDE;
    }
    else if (op == "subd" || op == "addd")
    {
        functionalUnit = ADD;
    }

    if (IsBusy(functionalUnit) == FALSE)
    {
        InstructionStatus[instruction].functionalUnit = functionalUnit;
        FunctionalUnitStatus[instruction].functionalUnit = functionalUnit;
        FunctionalUnitStatus[functionalUnit].busy = TRUE;
        FunctionalUnitStatus[functionalUnit].op = op;
        FunctionalUnitStatus[functionalUnit].fi = fi;
        FunctionalUnitStatus[functionalUnit].fj = fj;
        FunctionalUnitStatus[functionalUnit].fk = fk;
        qj = GetQj(functionalUnit);
        qk = GetQk(functionalUnit);
        FunctionalUnitStatus[functionalUnit].qj = qj;
        FunctionalUnitStatus[functionalUnit].qk = qk;
        rj = CheckRj(functionalUnit);
        rk = CheckRk(functionalUnit);
        FunctionalUnitStatus[functionalUnit].rj = rj;
        FunctionalUnitStatus[functionalUnit].rk = rk;
        int reg = RegToInt(fi);
        RegisterStatus[reg].status = FunctionalUnitStatus->unitList[functionalUnit];
        return 1;
    }
    return 0;
}

void PrintInstructions()
{
    int instructionCount = InstructionList->count;
    for (int i = 0; i < instructionCount; i++)
    {
        if (InstructionList[i].instruction == "ld")
        {
            cout << InstructionList[i].instruction << " " << InstructionList[i].regDestino << " " << InstructionList[i].offset << "+ " << InstructionList[i].regBaseLd << endl;
        }
        else
        {
            cout << InstructionList[i].instruction << " " << InstructionList[i].regDestino << " " << InstructionList[i].regOperando1 << " " << InstructionList[i].regOperando2 << endl;
        }
    }
}

void PrintFunctionalUnitStatus()
{

    cout << setw(7) << "FU " << setw(9) << "BUSY " << setfill(' ') << setw(8) << "OP " << setfill(' ') << setw(8) << "Fi " << setfill(' ') << setw(8) << "Fj " << setfill(' ') << setw(8) << "Fk " << setfill(' ') << setw(8) << "Qj " << setfill(' ') << setw(8) << "Qk " << setfill(' ') << setw(8) << "Rj " << setfill(' ') << setw(8) << "Rk " << endl;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        cout << setfill(' ') << setw(7) << FunctionalUnitStatus->unitList[i] << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].busy << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].op << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].fi << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].fj << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].fk << " | " << setfill(' ') << setw(7) << FunctionalUnitStatus[i].qj << " | " << setfill(' ') << setw(7) << FunctionalUnitStatus[i].qk << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].rj << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].rk << endl;
    }
}

void PrintRegisterStatus()
{
    cout << setw(8) << "r1 " << setw(8) << "r2 " << setw(8) << "r3 " << setw(8) << "r4 " << setw(8) << "r5 " << setw(8) << "r6 " << setw(8) << "r7 " << setw(8) << "r8 " << setw(8) << "r9 " << setw(8) << "r10 " << setw(8) << "r11 " << setw(8) << "r12 " << setw(8) << "rb " << setw(8) << endl;
    for (int i = 0; i < MAX_REG; i++)
    {
        cout << RegisterStatus[i].status << " | " << setfill(' ') << setw(5);
    }
    cout << endl;
}

void PrintInstructionStatus()
{
    cout << setfill(' ') << setw(7) << "Issue |" << setfill(' ') << setw(7) << " Read Operand |" << setfill(' ') << setw(7) << " Execution |" << setfill(' ') << setw(7) << " Write Result |"
         << " Intructions" << endl;
    for (int i = 0; i < InstructionList->count; i++)
    {
        cout << setw(5) << InstructionStatus[i].issue << " | " << setfill(' ') << setw(12) << InstructionStatus[i].readOperand << " | " << setfill(' ') << setw(9) << InstructionStatus[i].executionOperand << " | " << setfill(' ') << setw(12) << InstructionStatus[i].writeResult << " | ";
        if (InstructionList[i].instruction == "ld")
        {
            cout << InstructionList[i].instruction << " " << InstructionList[i].regDestino << " " << InstructionList[i].offset << "+ " << InstructionList[i].regBaseLd << endl;
        }
        else
        {
            cout << InstructionList[i].instruction << " " << InstructionList[i].regDestino << " " << InstructionList[i].regOperando1 << " " << InstructionList[i].regOperando2 << endl;
        }
    }
}

void Issue()
{
    int clock = InstructionStatus->clock;
    int processing = InstructionList->processing;
    clock++;
    while (InstructionStatus[processing].issue != 0)
    {
        processing++;
    }

    if (UpdateFunctionalUnitStatus(processing) == 1)
    {
        InstructionStatus[processing].issue = clock;
        InstructionStatus->issueCount++;
    }
}

void ReadOperand()
{
    int clock = InstructionStatus->clock;
    int processing = InstructionList->processing;
    int issueCount = InstructionStatus->issueCount;
    clock++;
    while (processing < issueCount)
    {
        if (CheckHazard(processing) == false && InstructionStatus[processing].issue > 0 && InstructionStatus[processing].readOperand == 0)
            InstructionStatus[processing].readOperand = clock;
        processing++;
    }
}

void ExecutionOperand()
{
    int clock = InstructionStatus->clock;
    int latency;
    int processing = InstructionList->processing;
    int issueCount = InstructionStatus->issueCount;
    string op;
    clock++;
    while (processing < issueCount){
        if (InstructionStatus[processing].readOperand > 0 && InstructionStatus[processing].executionOperand == 0){
            op = InstructionList[processing].instruction;
            if (op == "ld"){
                latency = Latencies.ld;
            }else if (op == "muld"){
                latency = Latencies.muld;
            }else if (op == "divd"){
                latency = Latencies.divd;
            }else if (op == "subd"){
                latency = Latencies.subd;
            }else if (op == "addd"){
                latency = Latencies.addd;
            }
            if (clock == InstructionStatus[processing].readOperand + latency)
                InstructionStatus[processing].executionOperand = clock;
        }
        processing++;
    }
}

void WriteResult()
{
    int clock = InstructionStatus->clock;
    clock++;
    int processing = InstructionList->processing;
    int issueCount = InstructionStatus->issueCount;
    bool canFinish = true;
    while (processing < issueCount){
        if (InstructionStatus[processing].executionOperand > 0 && InstructionStatus[processing].writeResult == 0){
            canFinish = true;
            for (int earlierInstruction = processing; earlierInstruction > 0; earlierInstruction--){
                if (CheckHazard(earlierInstruction) == true && InstructionStatus[earlierInstruction].readOperand == 0){
                    canFinish = false;
                    break;
                }
            }
            if (canFinish){
                InstructionStatus->finalizedList.push_back(processing);
                InstructionStatus[processing].writeResult = clock;
                InstructionStatus->finalizedCount++;
                InstructionStatus[processing].functionalUnit = -1;
            }
        }
        processing++;
    }
}

void FetchInstructions(string instructionLine)
{
    string instruction, regDestino, regBase, regBaseLd, regOperando1, regOperando2;
    int offset;
    int instructionCount = InstructionList->count;
    int spaceIndex = instructionLine.find(" ");
    int commaIndex = instructionLine.find(",");
    instruction = instructionLine.substr(0, spaceIndex);

    regDestino = instructionLine.substr(spaceIndex + 1, commaIndex - spaceIndex - 1);
    if (instruction == "ld")
    {
        int bracketIndex = instructionLine.find("(");
        int secBracketIndex = instructionLine.find(")");
        offset = stoi(instructionLine.substr(bracketIndex + 1, secBracketIndex - bracketIndex - 1)); // - 1 pois queremos um char antes do colchete
        regBaseLd = instructionLine.substr(secBracketIndex + 1, secBracketIndex - instructionLine.length());
    }
    else
    {
        spaceIndex = instructionLine.find(" ", spaceIndex + 1);
        commaIndex = instructionLine.find(",", commaIndex + 1);
        regOperando1 = instructionLine.substr(spaceIndex + 1, commaIndex - spaceIndex - 1);

        spaceIndex = instructionLine.find(" ", spaceIndex + 1);
        commaIndex = instructionLine.find(",", commaIndex + 1);
        regOperando2 = instructionLine.substr(spaceIndex + 1, commaIndex - spaceIndex);
    }
    InstructionList[instructionCount].instruction = instruction;
    InstructionList[instructionCount].regDestino = regDestino;
    InstructionList[instructionCount].regBase = regBase;
    InstructionList[instructionCount].regBaseLd = regBaseLd;
    InstructionList[instructionCount].offset = offset;
    InstructionList[instructionCount].regOperando1 = regOperando1;
    InstructionList[instructionCount].regOperando2 = regOperando2;
    InstructionList->count++;
}

void ReadFile(string dir)
{
    ifstream instructionFile;
    string line;
    instructionFile.open(dir);
    if (!instructionFile)
    {
        cerr << "Nao foi possivel abrir o arquivo de texto." << endl;
        exit(1);
    }

    while (getline(instructionFile, line))
    {
        FetchInstructions(line);
    }
    freopen("output.txt","w",stdout);
    while (InstructionStatus->finalizedCount != InstructionList->count)
    {
        WriteResult();
        ExecutionOperand();
        ReadOperand();
        Issue();
        int finalizedSize = InstructionStatus->finalizedList.size();
        for (int i = finalizedSize; i > 0; i--){
            int finalized = InstructionStatus->finalizedList[i - 1];
            InstructionStatus->finalizedList.pop_back();
            ClearFunctionalUnit(FunctionalUnitStatus[finalized].functionalUnit);
        }
        PrintInstructionStatus();
        cout << endl;
        PrintFunctionalUnitStatus();
        cout << endl;
        PrintRegisterStatus();
        cout << endl;
        InstructionStatus->clock++;
        cout << "Clock: " << InstructionStatus->clock << endl;
        cout << endl;
    }
}

int main()
{
    ReadFile("./entrada2.txt");
    return 0;
}
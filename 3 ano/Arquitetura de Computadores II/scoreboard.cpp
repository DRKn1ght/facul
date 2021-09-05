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
    vector<int>finalizedList;
    int finalizedCount = 0;
    int clock = 0;
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
int RegToInt(string reg){
    return stoi(reg.substr(1, reg.length() - 1)) - 1;
}

void ClearFunctionalUnit(int functionalUnit){
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
}

string CheckRj(int instruction)
{
    string fj = FunctionalUnitStatus[instruction].fj;
    if (fj == NONE)
        return NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].busy == TRUE && instruction != i)
        {
            if (FunctionalUnitStatus[i].fi == fj)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

string CheckRk(int instruction)
{
    string fk = FunctionalUnitStatus[instruction].fk;
    if (fk == NONE)
        return NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (FunctionalUnitStatus[i].busy == TRUE && instruction != i)
        {
            if (FunctionalUnitStatus[i].fk == fk)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}


void UpdateFunctionalUnitStatus(int instruction)
{
    int functionUnit;
    string op = InstructionList[instruction].instruction;
    string fi = InstructionList[instruction].regDestino;
    string fj = InstructionList[instruction].regOperando1;
    string fk = InstructionList[instruction].regOperando2;
    string rj, rk;
    if (op == "ld")
    {
        functionUnit = INTEGER;
        fk = InstructionList[instruction].regBaseLd;
    }
    else if (op == "muld")
    {
        functionUnit = MULT1;
        if (IsBusy(functionUnit) == TRUE)
            functionUnit = MULT2;
    }
    else if (op == "divd")
    {
        functionUnit = DIVIDE;
    }
    else if (op == "subd" || op == "addd")
    {
        functionUnit = ADD;
    }

    if (IsBusy(functionUnit) == FALSE)
    {
        FunctionalUnitStatus[instruction].functionalUnit = functionUnit;
        FunctionalUnitStatus[functionUnit].busy = TRUE;
        FunctionalUnitStatus[functionUnit].op = op;
        FunctionalUnitStatus[functionUnit].fi = fi;
        FunctionalUnitStatus[functionUnit].fj = fj;
        FunctionalUnitStatus[functionUnit].fk = fk;
        //qj
        //qk
        rj = CheckRj(instruction);
        FunctionalUnitStatus[functionUnit].rj = rj;
        rk = CheckRk(instruction);
        FunctionalUnitStatus[functionUnit].rk = rk;
        int reg = RegToInt(fi);
        RegisterStatus[reg].status = FunctionalUnitStatus->unitList[functionUnit];
    }
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

    cout << setw(7) << "FU " << setw(9) << "BUSY " << setfill(' ') << setw(5) << "OP " << setfill(' ') << setw(5) << "Fi " << setfill(' ') << setw(5) << "Fj " << setfill(' ') << setw(5) << "Fk " << setfill(' ') << setw(5) << "Qj " << setfill(' ') << setw(5) << "Qk " << setfill(' ') << setw(5) << "Rj " << setfill(' ') << setw(5) << "Rk " << endl;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        cout << setfill(' ') << setw(7) << FunctionalUnitStatus->unitList[i] << " | " << setfill(' ') << setw(5) << FunctionalUnitStatus[i].busy << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].op << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].fi << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].fj << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].fk << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].qj << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].qk << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].rj << " | " << setfill(' ') << setw(2) << FunctionalUnitStatus[i].rk << endl;
    }
}

void PrintRegisterStatus(){
    cout << setw(8) << "r1 " << setw(8) << "r2 " << setw(8) <<  "r3 " << setw(8) << "r4 " << setw(8) <<  "r5 " << setw(8) << "r6 " << setw(8) <<  "r7 " << setw(8) << "r8 " << setw(8) <<  "r9 " << setw(8) << "r10 " << setw(8) <<  "r11 " << setw(8) << "r12 " << setw(8) <<  "rb " << setw(8) << endl;
    for (int i = 0; i < MAX_REG; i++){
        cout << RegisterStatus[i].status <<  " | " << setfill(' ') << setw(5);
    }
    cout << endl;
}

void PrintInstructionStatus(){
    cout << setfill(' ') << setw(7) << "Issue |" << setfill(' ') << setw(7) << " Read Operand |" << setfill(' ') << setw(7) << " Execution |" << setfill(' ') << setw(7) << " Write Result |" << " Intructions"<< endl;
    for (int i = 0; i < InstructionList->count; i++){
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
    UpdateFunctionalUnitStatus(processing);
    InstructionStatus[processing].issue = clock;
    
}

void ReadOperand(){
    int clock = InstructionStatus->clock;
    int processing = InstructionList->processing;
    clock++;
    InstructionStatus[processing].readOperand = clock;

}

void ExecutionOperand(){
    int clock = InstructionStatus->clock;
    int processing = InstructionList->processing;
    clock++;
    InstructionStatus[processing].executionOperand = clock;

}

int WriteResult(){
    int clock = InstructionStatus->clock;
    int processing = InstructionList->processing;
    if (InstructionStatus[processing].executionOperand == 0){
        return 0;
    }
    InstructionStatus->finalizedList.push_back(processing);
    InstructionStatus->finalizedCount++;
    ClearFunctionalUnit(FunctionalUnitStatus[processing].functionalUnit);
    return 1;
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
    while (InstructionStatus->finalizedCount != InstructionList->count){
        if (WriteResult() == 1){
            
        }
    }
}

int main()
{
    ReadFile("./entrada.txt");
    return 0;
}
/*
Aluno: Guilherme Panobianco Ferrari
RA: 112679
Simulador de ScoreBoarding
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
#define MAX_INSTRUCTION 1000
#define MAX_REG 12
#define MAX_UNIT 5

#define YES "Yes"
#define NO "No"
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
    string instruction, regDestino, regBase, regBaseLd, regOperando1, regOperando2;
    int offset, count = 0, processing = 0;
} InstructionList[MAX_INSTRUCTION];

struct instructionStatus
{
    int issue, readOperand, executionOperand, writeResult;
    int issueCount = 0, finalizedCount = 0, functionalUnit = -1;
    int clock = 0;
    vector<int> finalizedList;
};

struct functionalUnitStatus
{
    string const unitList[MAX_UNIT] = {"Integer", "Mult1", "Mult2", "Add", "Divide"};
    string busy = NO, rj, rk;
    string op, fi, fj, fk, qj, qk;
    int functionalUnit = -1;
};

struct registerStatus
{
    string status;
};

class scoreBoard
{
public:
    instructionStatus InstructionStatus[MAX_INSTRUCTION];
    functionalUnitStatus FunctionalUnitStatus[MAX_UNIT];
    registerStatus RegisterStatus[MAX_REG];
} ScoreBoard;

// Recebe uma unidade funcional e retorna se está ocupada.
string IsBusy(int functionalUnit)
{
    return ScoreBoard.FunctionalUnitStatus[functionalUnit].busy;
}

// Recebe um registro e retorna o index do registro.
int RegToIndex(string reg)
{
    if (reg == "rb")
        return MAX_REG;
    return stoi(reg.substr(1, reg.length() - 1)) - 1;
}

// Recebe uma unidade funcional e a desocupa quando ela é completada.
// Também atualiza os valores de Qj e Rj de todas as unidades funcionais além de atualizar o estado do registrador.
void ClearFunctionalUnit(int functionalUnit)
{
    string fi = ScoreBoard.FunctionalUnitStatus[functionalUnit].fi;
    int reg;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].busy = NO;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].op = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].fi = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].fj = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].fk = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].qj = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].qk = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].rj = NONE;
    ScoreBoard.FunctionalUnitStatus[functionalUnit].rk = NONE;
    reg = RegToIndex(fi);
    ScoreBoard.RegisterStatus[reg].status = NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (ScoreBoard.FunctionalUnitStatus[i].qj == ScoreBoard.FunctionalUnitStatus->unitList[functionalUnit])
        {
            ScoreBoard.FunctionalUnitStatus[i].qj = NONE;
            ScoreBoard.FunctionalUnitStatus[i].rj = YES;
        }
        if (ScoreBoard.FunctionalUnitStatus[i].qk == ScoreBoard.FunctionalUnitStatus->unitList[functionalUnit])
        {
            ScoreBoard.FunctionalUnitStatus[i].qk = NONE;
            ScoreBoard.FunctionalUnitStatus[i].rk = YES;
        }
    }
}

// Recebe uma unidade funcional e verifica se o valor de Rj está pronto.
string CheckRj(int functionalUnit)
{
    string fj = ScoreBoard.FunctionalUnitStatus[functionalUnit].fj;
    if (fj == NONE)
        return NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (ScoreBoard.FunctionalUnitStatus[i].busy == YES && functionalUnit != i)
        {
            if (ScoreBoard.FunctionalUnitStatus[i].fi == fj)
            {
                return NO;
            }
        }
    }
    return YES;
}

// Recebe uma unidade funcional e verifica se o valor de Rk está pronto.
string CheckRk(int functionalUnit)
{
    string fk = ScoreBoard.FunctionalUnitStatus[functionalUnit].fk;

    if (fk == NONE)
        return NONE;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (ScoreBoard.FunctionalUnitStatus[i].busy == YES && functionalUnit != i)
        {
            if (ScoreBoard.FunctionalUnitStatus[i].fi == fk)
            {
                return NO;
            }
        }
    }
    return YES;
}

// Recebe uma unidade funcional e retorna o valor de Qj.
string GetQj(int functionalUnit)
{
    string fj = ScoreBoard.FunctionalUnitStatus[functionalUnit].fj;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (ScoreBoard.FunctionalUnitStatus[i].busy == YES && functionalUnit != i)
        {
            if (ScoreBoard.FunctionalUnitStatus[i].fi == fj)
            {
                return ScoreBoard.FunctionalUnitStatus->unitList[i];
            }
        }
    }
    return NONE;
}

// Recebe uma unidade funcional e retorna o valor de Qk.
string GetQk(int functionalUnit)
{
    string fk = ScoreBoard.FunctionalUnitStatus[functionalUnit].fk;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        if (ScoreBoard.FunctionalUnitStatus[i].busy == YES && functionalUnit != i)
        {
            if (ScoreBoard.FunctionalUnitStatus[i].fi == fk)
            {
                return ScoreBoard.FunctionalUnitStatus->unitList[i];
            }
        }
    }
    return NONE;
}

// Recebe uma instrução e retorna true caso houver hazards estruturais. Retorna falso caso contrário.
bool CheckHazard(int instruction)
{
    int functionalUnit = ScoreBoard.InstructionStatus[instruction].functionalUnit;
    if (functionalUnit == -1)
        return false;
    if (ScoreBoard.FunctionalUnitStatus[functionalUnit].qj != NONE || ScoreBoard.FunctionalUnitStatus[functionalUnit].qk != NONE)
        return true;

    if (ScoreBoard.FunctionalUnitStatus[functionalUnit].rj == YES)
        ScoreBoard.FunctionalUnitStatus[functionalUnit].rj = NO;
    if (ScoreBoard.FunctionalUnitStatus[functionalUnit].rk == YES)
        ScoreBoard.FunctionalUnitStatus[functionalUnit].rk = NO;
    return false;
}

// Recebe uma instrução e atualiza o status da unidade funcional quando a instrução for emitida.
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
        if (IsBusy(functionalUnit) == YES)
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
    string regDestino = InstructionList[instruction].regDestino;
    if (IsBusy(functionalUnit) == NO && ScoreBoard.RegisterStatus[RegToIndex(regDestino)].status == NONE)
    {
        ScoreBoard.InstructionStatus[instruction].functionalUnit = functionalUnit;
        ScoreBoard.FunctionalUnitStatus[instruction].functionalUnit = functionalUnit;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].busy = YES;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].op = op;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].fi = fi;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].fj = fj;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].fk = fk;
        qj = GetQj(functionalUnit);
        qk = GetQk(functionalUnit);
        ScoreBoard.FunctionalUnitStatus[functionalUnit].qj = qj;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].qk = qk;
        rj = CheckRj(functionalUnit);
        rk = CheckRk(functionalUnit);
        ScoreBoard.FunctionalUnitStatus[functionalUnit].rj = rj;
        ScoreBoard.FunctionalUnitStatus[functionalUnit].rk = rk;
        int reg = RegToIndex(fi);
        ScoreBoard.RegisterStatus[reg].status = ScoreBoard.FunctionalUnitStatus->unitList[functionalUnit];
        return 1;
    }
    return 0;
}

// Imprime o status da unidade funcional no arquivo de saída.
void PrintFunctionalUnitStatus()
{

    cout << setw(7) << "FU " << setw(9) << "BUSY " << setfill(' ') << setw(8) << "OP " << setfill(' ') << setw(8) << "Fi " << setfill(' ') << setw(8) << "Fj " << setfill(' ') << setw(8) << "Fk " << setfill(' ') << setw(8) << "Qj " << setfill(' ') << setw(8) << "Qk " << setfill(' ') << setw(8) << "Rj " << setfill(' ') << setw(8) << "Rk " << endl;
    for (int i = 0; i < MAX_UNIT; i++)
    {
        cout << setfill(' ') << setw(7) << ScoreBoard.FunctionalUnitStatus->unitList[i] << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].busy << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].op << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].fi << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].fj << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].fk << " | " << setfill(' ') << setw(7) << ScoreBoard.FunctionalUnitStatus[i].qj << " | " << setfill(' ') << setw(7) << ScoreBoard.FunctionalUnitStatus[i].qk << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].rj << " | " << setfill(' ') << setw(5) << ScoreBoard.FunctionalUnitStatus[i].rk << endl;
    }
}

// Imprime o status do registrador no arquivo de saída.
void PrintRegisterStatus()
{
    cout << setw(8) << "r1 " << setw(8) << "r2 " << setw(8) << "r3 " << setw(8) << "r4 " << setw(8) << "r5 " << setw(8) << "r6 " << setw(8) << "r7 " << setw(8) << "r8 " << setw(8) << "r9 " << setw(8) << "r10 " << setw(8) << "r11 " << setw(8) << "r12 " << setw(8) << "rb " << setw(8) << endl;
    for (int i = 0; i < MAX_REG; i++)
    {
        cout << ScoreBoard.RegisterStatus[i].status << " | " << setfill(' ') << setw(5);
    }
    cout << endl;
}

// Imprime o status das instruções no arquivo de saída.
void PrintInstructionStatus()
{
    cout << setfill(' ') << setw(7) << "Issue |" << setfill(' ') << setw(7) << " Read Operand |" << setfill(' ') << setw(7) << " Execution |" << setfill(' ') << setw(7) << " Write Result |"
         << " Intructions" << endl;
    for (int i = 0; i < InstructionList->count; i++)
    {
        cout << setw(5) << ScoreBoard.InstructionStatus[i].issue << " | " << setfill(' ') << setw(12) << ScoreBoard.InstructionStatus[i].readOperand << " | " << setfill(' ') << setw(9) << ScoreBoard.InstructionStatus[i].executionOperand << " | " << setfill(' ') << setw(12) << ScoreBoard.InstructionStatus[i].writeResult << " | ";
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

// Método que emite a instrução.
void Issue()
{
    int clock = ScoreBoard.InstructionStatus->clock;
    int processing = InstructionList->processing;
    clock++;
    while (ScoreBoard.InstructionStatus[processing].issue != 0)
    {
        processing++;
    }

    if (UpdateFunctionalUnitStatus(processing) == 1)
    {
        ScoreBoard.InstructionStatus[processing].issue = clock;
        ScoreBoard.InstructionStatus->issueCount++;
    }
}

// Método que faz a leitura do operando da instrução.
void ReadOperand()
{
    int clock = ScoreBoard.InstructionStatus->clock;
    int processing = InstructionList->processing;
    int issueCount = ScoreBoard.InstructionStatus->issueCount;
    clock++;
    while (processing < issueCount)
    {
        if (CheckHazard(processing) == false && ScoreBoard.InstructionStatus[processing].issue > 0 && ScoreBoard.InstructionStatus[processing].readOperand == 0)
        {
            ScoreBoard.InstructionStatus[processing].readOperand = clock;
        }
        processing++;
    }
}

// Método que executa a instrução.
void ExecutionOperand()
{
    int clock = ScoreBoard.InstructionStatus->clock;
    int latency;
    int processing = InstructionList->processing;
    int issueCount = ScoreBoard.InstructionStatus->issueCount;
    string op;
    clock++;
    while (processing < issueCount)
    {
        if (ScoreBoard.InstructionStatus[processing].readOperand > 0 && ScoreBoard.InstructionStatus[processing].executionOperand == 0)
        {
            op = InstructionList[processing].instruction;
            if (op == "ld")
            {
                latency = Latencies.ld;
            }
            else if (op == "muld")
            {
                latency = Latencies.muld;
            }
            else if (op == "divd")
            {
                latency = Latencies.divd;
            }
            else if (op == "subd")
            {
                latency = Latencies.subd;
            }
            else if (op == "addd")
            {
                latency = Latencies.addd;
            }
            if (clock == ScoreBoard.InstructionStatus[processing].readOperand + latency)
                ScoreBoard.InstructionStatus[processing].executionOperand = clock;
        }
        processing++;
    }
}

// Método que escreve o resultado da instrução.
void WriteResult()
{
    int clock = ScoreBoard.InstructionStatus->clock;
    clock++;
    int processing = InstructionList->processing;
    int issueCount = ScoreBoard.InstructionStatus->issueCount;
    bool canFinish = true;
    while (processing < issueCount)
    {
        if (ScoreBoard.InstructionStatus[processing].executionOperand > 0 && ScoreBoard.InstructionStatus[processing].writeResult == 0)
        {
            canFinish = true;
            for (int earlierInstruction = processing; earlierInstruction > 0; earlierInstruction--)
            {
                if (CheckHazard(earlierInstruction) == true && ScoreBoard.InstructionStatus[earlierInstruction].readOperand == 0)
                {
                    canFinish = false;
                    break;
                }
            }
            if (canFinish)
            {
                ScoreBoard.InstructionStatus->finalizedList.push_back(processing);
                ScoreBoard.InstructionStatus[processing].writeResult = clock;
                ScoreBoard.InstructionStatus->finalizedCount++;
                ScoreBoard.InstructionStatus[processing].functionalUnit = -1;
            }
        }
        processing++;
    }
}

// Método que recebe uma instrução, coleta os dados de cada uma e atualiza a estrutura InstructionList.
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

// Método que inicia o ScoreBoard e gera o arquivo de saída.
void InitScoreBoard(string fileName)
{
    string outputFile;
    fileName = fileName.replace(0, 2, "");
    int dotIndex = fileName.find(".");
    fileName = fileName.substr(0, dotIndex);
    fileName = fileName + ".out";
    freopen(fileName.c_str(), "w", stdout);
    while (ScoreBoard.InstructionStatus->finalizedCount != InstructionList->count)
    {
        WriteResult();
        ExecutionOperand();
        ReadOperand();
        Issue();
        int finalizedSize = ScoreBoard.InstructionStatus->finalizedList.size();
        for (int i = finalizedSize; i > 0; i--)
        {
            int finalized = ScoreBoard.InstructionStatus->finalizedList[i - 1];
            ScoreBoard.InstructionStatus->finalizedList.pop_back();
            ClearFunctionalUnit(ScoreBoard.FunctionalUnitStatus[finalized].functionalUnit);
        }
        PrintInstructionStatus();
        cout << endl;
        PrintFunctionalUnitStatus();
        cout << endl;
        PrintRegisterStatus();
        cout << endl;
        ScoreBoard.InstructionStatus->clock++;
        cout << "Clock: " << ScoreBoard.InstructionStatus->clock << endl;
        cout << endl;
    }
}

// Método que lê o arquivo.
void ReadFile(string fileName)
{
    ifstream instructionFile;
    string line;
    instructionFile.open(fileName);
    if (!instructionFile)
    {
        cerr << "Nao foi possivel abrir o arquivo. Verifique se esta na mesma pasta." << endl;
        exit(1);
    }

    while (getline(instructionFile, line))
    {
        FetchInstructions(line);
    }
    InitScoreBoard(fileName);
}

int main(int argc, char **argv)
{
    string fileName = argv[1];
    ReadFile("./" + fileName);
    return 0;
}
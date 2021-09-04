#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define MAX_INSTRUCTION 1000
#define MAX_UNIT 5
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
    int offset, count = 0;
} InstructionList[MAX_INSTRUCTION];

struct instructionStatus
{
    int issue, readOperand, executionOperand, writeResult;
} InstructionStatus[MAX_INSTRUCTION];

struct functionalUnitStatus
{
    bool busy = false, rj, rk;
    string op, fi, fj, fk, qj, qk;
} FunctionalUnitStatus[MAX_UNIT];

struct registerStatus
{
    string status;
} RegisterStatus[MAX_INSTRUCTION];

void PrintInstructions(){
    int instructionCount = InstructionList->count;
    for (int i = 0; i < instructionCount; i++){
        if (InstructionList[i].instruction == "ld"){
            cout << InstructionList[i].instruction << " " << InstructionList[i].regDestino << " " << InstructionList[i].offset << "+ " << InstructionList[i].regBaseLd << endl;
        }else{
            cout << InstructionList[i].instruction << " " << InstructionList[i].regDestino << " " << InstructionList[i].regOperando1 << " " << InstructionList[i].regOperando2 << endl;
        }
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
    //cout << instruction << endl;
    regDestino = instructionLine.substr(spaceIndex + 1, commaIndex - spaceIndex - 1);
    //cout << regDestino << endl;
    if (instruction == "ld")
    { // Caso for ld, o tratamento para achar os parametros sao diferentes.
        //cout << regDestino << endl;
        int bracketIndex = instructionLine.find("(");
        int secBracketIndex = instructionLine.find(")");
        offset = stoi(instructionLine.substr(bracketIndex + 1, secBracketIndex - bracketIndex - 1)); // - 1 pois queremos um char antes do colchete
        //cout << offset << endl;
        regBaseLd = instructionLine.substr(secBracketIndex + 1, secBracketIndex - instructionLine.length());
        //cout << regBase << endl;
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
    PrintInstructions();
}

int main()
{
    ReadFile("./entrada.txt");
    return 0;
}
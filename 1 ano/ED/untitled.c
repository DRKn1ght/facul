#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000
int qntaluno = 0;
struct aluno {
 char ra[100];
 char nome[100];
};
struct aluno Alunos[MAXCHAR];

int procurar(char *RA)
{
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "/tmp/guest-6zcbws/alunos.txt";
    fp = fopen(filename, "r+");
	struct aluno alunos;
	int line = 0;
  while (fgets(str, MAXCHAR, fp) != NULL){
    	if (strstr(str, RA)){
    		printf("%s", Alunos[line].nome);
    		fprintf(fp, "0");
    	}
        line++;
    }
fclose(fp);
return 0;
}
int main(){
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "/tmp/guest-6zcbws/alunos.txt";
    fp = fopen(filename, "r");
	struct aluno alunos;
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL){
    	//printf("%s - %i ", str, index);
    	strncpy(alunos.ra, str, 6);
    	strncpy(alunos.nome, str + 7, strlen(str));
        Alunos[qntaluno] = alunos;
        qntaluno++;
    }
    procurar("301968");
    fclose(fp);


}
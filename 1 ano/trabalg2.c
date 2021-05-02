#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000
int qntaluno = 0;

struct aluno {
 char ra[100];
 char nome[100];
};

struct aluno Alunos[MAXCHAR];




void buscar(int i){
	FILE *arquivo;
    int n = 0;
	struct aluno alunos;
	if (arquivo != NULL){

		char ra[7];
		char str[MAXCHAR];
		int n=0;
		printf("Digite o RA do aluno desejado(6 numeros)");
		scanf("%s",ra);

        if (i == 1){
		    for(int index2 = 0; index2 < qntaluno; index2++){
			    if (!strcmp(Alunos[index2].ra, ra)){
                   printf("%s", Alunos[index2].nome);
                   n++;
                  break;
		    	}
	    	}
            if (n == 0){
                printf("Usuario nao encontrado");
            }
        return;
        }

        if (i == 2)
        {
            arquivo = fopen("C:/Users/guipa/Desktop/C E PITON/alunos.txt","w");
            for(int index2 = 0; index2 < qntaluno; index2++){
			    if (!strcmp(Alunos[index2].ra, ra)){
                    fprintf(arquivo, "%s\r%s\n", Alunos[index2].ra, " SERJAO ");   
                    printf("Usuario %s alterado para SERJAO", Alunos[index2].nome);      
			    }else{
                    fprintf(arquivo, "%s %s", Alunos[index2].ra, Alunos[index2].nome);
                }
		    }
        return;
        }

	}	
	else{
		printf("Arquivo nao encontrado");
	}


	fclose(arquivo);

}



//menu




int main(){
	int i = 0;
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "C:/Users/guipa/Desktop/C E PITON/alunos.txt";
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
        Alunos[i] = alunos;
        i++;
        qntaluno++;
}
	while(i != 5){
		printf("\nDigite a opcao desejada\n");
		printf("OPCAO 1- Buscar aluno por RA \n");
		printf("OPCAO 2- Alterar aluno \n");
		printf("OPCAO 3- Remover aluno \n");
		printf("OPCAO 4- Gerar relatorio \n");
		printf("OPCAO 5- Encerrar o programa \n");
		scanf("%d",&i);

		//switch case
	switch(i){
		case 1:
			buscar(1);
		break;	
		case 2:
		buscar(2);
		break;	

		case 3:
		printf("a\t\na");
		break;	

		case 4:
		
		break;	

		case 5:
		
		break;	
	
		default:
			printf("\nOpcao nao existe");	
	break;	
	}	

	}	
return 0;

}

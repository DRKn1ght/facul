#include <stdio.h>
#include <malloc.h>
#include "pilha.h"
int tMax = 50; //Tamanho máximo da pilha
typedef struct Pilha {
	int topo; /* posicao do elemento do topo */
	int tamanho;
	float *pElem;
}ppilha;

TPilha* criapilha(){ //cria a lista
    TPilha *p;
    p = (TPilha *) malloc(sizeof(TPilha));
    p->topo = -1;
    p->tamanho = tMax;
    p->pElem = (float*) malloc (tMax * sizeof(float));
}

int isEmpty ( TPilha *p ){ //Verifica se a pilha está vazia
   if( p-> topo == -1 )
      return 1; 
    return 0; 
}

int isFull ( TPilha *p ){ //Verifica se a pilha está cheia
	if (p->topo == p->tamanho - 1)
	    return 1;
	return 0;
}

void push ( TPilha *p, int v){ //Empilha um elemento no topo da pilha
	p->topo++;
	p->pElem [p->topo] = v;
}

int pop ( TPilha *p ){ //Desempilha o elemento do topo da pilha
   float aux = p->pElem [p->topo];
   p->topo--;
   return aux;
}

int topo ( TPilha *p ){ //Retorna o elemento do topo da pilha
   return p->pElem [p->topo];
}

int Operation(int x, int y, char op) //Faz as operações matemáticas 
{
    int valor;
    struct Pilha minhapilha;
    switch (op){
        case '+':
            pop(&minhapilha); //Desempilha o elemento que estava sendo usado para somar, para inserir o resultado.
            valor = x + y;
            break;

        case '-':
            pop(&minhapilha);
            valor = x - y;
            break;

        case '*':
            pop(&minhapilha);
            valor = x * y;
            break;

        case '/':
            pop(&minhapilha);
            valor = x / y;
            break;
        default:
        printf("Operacao nao reconhecida");
        break;
    }
    return valor;
}
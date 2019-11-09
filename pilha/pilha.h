#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct Pilha TPilha;

TPilha* criapilha(); //Cria a pilha

int isEmpty (TPilha *p ); //Verifica se está vazia

int isFull (TPilha *p ); //verifica se está cheia

void push (TPilha *p, int v); //Empilha elemento

int pop (TPilha *p ); //Desempilha elemento

int topo (TPilha *p ); //Retorna o elemento to topo

int Operation(int x, int y, char op); //Faz as operações matemáticas

#endif // LISTA_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "lista.h"
#define MAX 20

struct Lista{
    char* elm;
    int qnt;
};

TLista* cria_lista(){
    TLista * lista = (TLista *) malloc(sizeof(TLista));
    lista->elm = (char *) malloc(sizeof(char)*MAX);
    lista->qnt = 0; //lista com 0 elementos
    return lista;
}

int insere (TLista* lista, char x, int pos){
    if (pos < 1 || pos > lista->qnt + 1 || lista->qnt == MAX)
        return 0;
    int i = lista->qnt;
    for(i; i >= pos; i--){
        lista->elm[i] = lista->elm[i-1];
    }
    lista->elm[i]=x;
    lista->qnt++;
    return 1;
}

int remover (TLista* lista, int pos){
    if (pos < 1 || pos > lista->qnt)
        return 0;
    for(int i = pos-1; i < lista->qnt; i++){
        lista->elm[i] = lista->elm[i+1];
    }
    lista->qnt--;
    return 1;
}

int acessa (TLista* lista, int pos, char* elem){
    if (pos < 1 || pos > lista->qnt)
        return 0;
    *elem = lista->elm[pos-1];
    return 1;
}

int devolve (TLista* lista, char x, int*pos){
    for (int i = 0; i < lista->qnt; i++){
        if (lista->elm[i] == x){
            *pos = i+1;
            return 1;
        }
    }
    return 0;
}

int tamanho (TLista* lista){
    return lista->qnt;
} 

void imprimeLista (TLista* lista){
    printf("\nLista:\n");
    for (int i = 0; i < lista->qnt; i++)
        printf("%c - ", lista->elm[i]);
    printf("\n");
}

void destroi (TLista* lista){
    free(lista);
}
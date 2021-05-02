#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct sNo{
    char elem;
    ponteiro prox;
    ponteiro ant;
}Tno;

typedef struct sLista{
    ponteiro prim;
    int qnt; //quantidade de elementos
}Lista;

void imprimeLista (TLista* lista){
    printf("\n\nImprimindo a Lista: \n");
    ponteiro pos = lista->prim;
    if(lista->qnt == 0){
      printf("A lista está vazia.");
    }else{
      while(pos->prox != lista->prim){
        printf("%c -> ",pos->elem);
        pos = pos->prox;
    }
		printf("%c\n", pos->elem);
    }
}

void imprimir_inversa (TLista* lista){
	if(tamanho(lista)) {
		ponteiro pos = lista -> prim -> ant;
		while(pos!=lista->prim) {
			printf("%c -> ", pos->elem);
			pos = pos->ant;
		}
		printf("%c\n", pos->elem);
	}
}

TLista* cria_lista(){
  TLista* lista;
  lista = (TLista *) malloc(sizeof(TLista));
  lista->qnt = 0;
  lista->prim = NULL;
}


int exclui (TLista* lista, char x){
  ponteiro pos = busca(lista, x);
	if(pos){
		if(pos == lista->prim){
			lista->prim = pos->prox;
		}
		pos->ant->prox = pos->prox;
		pos->prox->ant = pos->ant;
		lista->qnt--;
		return 1;
	}
	return 0;
  }


ponteiro busca(TLista* lista, char x){
//retorna um ponteiro para o conteúdo buscado ou NULL
    ponteiro pos;
    pos = lista->prim;
    while(pos!=NULL && pos->elem != x){
        pos = pos->prox;
    }
    if(pos->elem!=x)
      return NULL;
    return pos;
}

int acessa(TLista* lista, int pos, char *x){
    if (pos < 1 || pos > lista->qnt) //a posição não existe
        return -1;
    else {
       int cont = 1; 
       ponteiro i = lista->prim;
       while(cont < pos){
          i = i->prox;
          cont++;
       }
       *x = i->elem;
       return 1;
    }
}

int tamanho (TLista* lista){
    return lista->qnt;
}

int insere(TLista* lista, char x){
    ponteiro novo, pos;
    pos = lista->prim;
    novo = (ponteiro) malloc(sizeof(Tno));
    novo->elem = x;
    if (lista->qnt == 0){ //lista  ou início da lista
        novo->ant = novo;
        novo->prox = novo;
        lista->prim = novo;
    } else if (x < pos->elem){
      novo -> ant = pos -> ant;
		  novo -> prox = pos;
		  pos -> ant -> prox = novo;
		  pos -> ant = novo;
		  lista -> prim = novo;//lista meio cheia
      }else{
        while(pos->prox!=lista->prim && pos->elem < x){
            pos = pos->prox;
        }
        novo->prox = pos;
        novo->ant = pos->ant;
        pos->ant->prox = novo;
        pos->ant = novo;
      }
      lista->qnt++;
      return 1;
    }

int destroi(TLista* lista){
  ponteiro pos = lista->prim, aux;
  int cont = 1;
  while (cont < lista->qnt) {
    aux = pos->prox;
    free(pos);
    pos = aux;
    cont++;
  }
  free(pos);
  free(lista);
  lista->qnt = 0;
  return 1;
}
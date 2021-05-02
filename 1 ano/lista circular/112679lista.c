#include <stdio.h>
#include <stdlib.h>
#include "112679lista.h"

typedef struct sNo{
    char elem;
    ponteiro prox;
    ponteiro ant;
}Tno;

typedef struct sLista{
    ponteiro prim;
    int qnt; //quantidade de elementos
}Lista;

void imprimeInversa(TLista* lista)
{
  ponteiro pos = lista->prim->ant;
  if (tamanho(lista) == 0){
    printf("lista vazia");
  }else{
  while(pos->ant != lista->prim->ant){
    printf(" %c -> ", pos->elem);
    pos = pos->ant;
  }
  printf("%c -> ", pos->elem);
}
}

void imprimeLista (TLista* lista){
    ponteiro pos = lista->prim;
    if(tamanho(lista) == 0){
      printf("Erro: Lista vazia");
    }else{
      while(pos->prox != lista->prim){
        printf(" %c -> ",pos->elem);
        pos = pos->prox;
    }
    printf(" %c -> ", pos->elem);
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
    ponteiro pos = lista->prim;
    while(pos!= NULL && pos->elem != x){
        pos = pos->prox;
    }
    if(pos->elem!=x)
      return NULL;
    return pos;
}

int acessa(TLista* lista, int pos, char *x){
    if (pos < 1 || pos > tamanho(lista))
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
    if (tamanho(lista) == 0){
        novo->ant = novo;
        novo->prox = novo;
        lista->prim = novo;
    } else if (x < pos->elem){
      novo -> ant = pos -> ant;
		  novo -> prox = pos;
		  pos -> ant -> prox = novo;
		  pos -> ant = novo;
		  lista -> prim = novo;
      }else{
        int i =0;
        while(x > pos->elem && i < lista->qnt){
          i++;
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

void destroi(TLista* lista){
  ponteiro pos = lista->prim, aux;
  for(int cont = 0; cont < lista->qnt; cont++) {
    aux = pos->prox;
    free(pos);
    pos = aux;
  }
  free(pos);
  free(lista);
  //lista->qnt = 0;
}
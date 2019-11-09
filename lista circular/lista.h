#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct sNo* ponteiro;

typedef struct sLista TLista;

void imprimeLista (TLista* lista);

TLista* cria_lista ();

int exclui (TLista* lista, char x);

ponteiro busca(TLista* lista, char x);

int acessa(TLista* lista, int pos, char *x);

int tamanho (TLista* lista);

int insere(TLista* lista, char x);

#endif // LISTA_H_INCLUDED

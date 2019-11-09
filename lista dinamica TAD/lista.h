#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct Lista TLista;

TLista* cria_lista ();

int insere(TLista* lista, char x, int pos);
//int insere(TLista* lista, char x); // lista ordenada
/*Insere o elemento x na posi��o pos da lista
  Retorna 1 em caso de sucesso e 0 caso a posi��o
  n�o seja v�lida ou a lista esteja cheia*/

int remover(TLista* lista, int pos);
//int remover(TLista* lista, char x); //lista ordenada 
/*Remove o elemento x da posi��o pos da lista
  Retorna 1 em caso de sucesso e 0 caso a posi��o
  n�o seja v�lida ou a lista esteja vazia*/

int acessa(TLista* lista, int pos, char* elem);
/*Acessa o elemento elem da posi��o pos da lista
  Retorna 1 em caso de sucesso e 0 caso a posi��o
  n�o seja v�lida*/

int devolve(TLista* lista, char x, int *pos);
/*Devolve a posi��o pos na qual se encontra a
  primeira ocorr�ncia do elemento x na lista.
  Retorna 1 em caso de sucesso e 0 caso o elemento
  x n�o fa�a parte da lista*/

int tamanho (TLista* lista);
/*retorna o tamanho (quantide de elementos) da lista*/

void imprimeLista(TLista* lista);
/*Imprime a quantidade de elementos, assim como os
  elementos da lista*/

void destroi(TLista* lista);
/*Libera a mem�ria alocada pela lista*/


#endif // LISTA_H_INCLUDED

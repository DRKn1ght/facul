#include <stdio.h>
#include <stdlib.h>
#include "112679lista.h"

int main(){
TLista *vlista;
vlista = cria_lista();
printf("\n\nInsere: B retornou: %i",insere(vlista, 'B'));
imprimeLista(vlista);
printf("\n\nInsere: G retornou: %i",insere(vlista, 'G'));
imprimeLista(vlista);
printf("\n\nInsere: C retornou: %i",insere(vlista, 'C'));
imprimeLista(vlista);
printf("\n\nInsere: A retornou: %i",insere(vlista, 'A'));
imprimeLista(vlista);
printf("\n\nInsere: H retornou: %i",insere(vlista, 'H'));
imprimeLista(vlista);
printf("\n\nInsere: M retornou: %i",insere(vlista, 'M'));
imprimeLista(vlista);
printf("\n\nInsere: J retornou: %i",insere(vlista, 'J'));
imprimeLista(vlista);
printf("\n\nInsere: K retornou: %i",insere(vlista, 'K'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: X retornou: %i",insere(vlista, 'X'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: D retornou: %i",insere(vlista, 'D'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: F retornou: %i",insere(vlista, 'F'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: N retornou: %i",insere(vlista, 'N'));
imprimeLista(vlista);
//printf("\n\nBuscar: K retornou um ponteiro para o conteudo: %c",(busca(vlista, 'K'))->info);
imprimeLista(vlista);
char x; int res = acessa(vlista, 3, &x);
printf("\n\nAcessa: 3� posicao retornou: %i info: %c ",res,x);
imprimeLista(vlista);
res = acessa(vlista, 7, &x);
printf("\n\nAcessa: 7� posicao retornou: %i info: %c ",res,x);
imprimeLista(vlista);
res = acessa(vlista, 12, &x);
printf("\n\nAcessa: 12� posicao retornou: %i info: %c ",res,x);
imprimeLista(vlista);
res = acessa(vlista, -1, &x);
printf("\n\nAcessa: -1� posicao retornou: %i info: %c ",res,x);
imprimeLista(vlista);
printf("\n\nRemove: M retornou: %i",exclui(vlista, 'M'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nRemove: B retornou: %i",exclui(vlista, 'B'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nRemove: X retornou: %i",exclui(vlista, 'X'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nRemove: A retornou: %i",exclui(vlista, 'A'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: R retornou: %i",insere(vlista, 'R'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: T retornou: %i",insere(vlista, 'T'));
imprimeLista(vlista);
printf("\nTamanho da Lista: %i", tamanho(vlista));
printf("\n\nInsere: B retornou: %i",insere(vlista, 'B'));
imprimeLista(vlista);
printf("\nInversa: ");
imprimeInversa(vlista);
printf("\nTamanho da Lista: %i\n", tamanho(vlista));
destroi(vlista);
return 0;
}


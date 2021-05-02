#include <stdio.h>
#include "lista.h"
int main(){
    TLista* vlista = cria_lista();
    printf("Insercao de A em 1: %i", insere(vlista, 'A', 1));
    printf("\nInsercao de B em 2: %i", insere(vlista, 'B', 2));
    printf("\nInsercao de C em 3: %i", insere(vlista, 'C', 3));
    imprimeLista(vlista);
    printf("Remover elemento da posicao 2: %i", remover(vlista, 2));
    imprimeLista(vlista);
    printf("tamanho: %i", tamanho(vlista));
    char elemento;
    acessa(vlista, 1, &elemento);
    printf("\nprimeiro elemento: %c\n", elemento);
    int pos;
    devolve(vlista, 'C', &pos);
    printf("Posicao da primeira ocorrencia do C: %i\n", pos);
    destroi(vlista);
    return 0;
}
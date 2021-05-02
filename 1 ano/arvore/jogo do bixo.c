#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
//testar no linux
typedef enum{false, true} boolean;

  typedef struct No{
  
  char animal[64];
  struct No* esquerda;
  struct No* direita;
}No;

  typedef struct{
  No* raiz;
}Arvore;


void cria_arvore(Arvore* arv) {
  arv->raiz = NULL;
}


boolean eh_nulo(No* No_atual){
  if(No_atual == NULL)
    return true;
  return false;
}


No* insere(char cod[], No* No_atual,int x) {
  if(eh_nulo(No_atual)==true){
    No_atual = (No*) malloc(sizeof(No));
    strcpy(No_atual-> animal,cod);  
    No_atual->esquerda = NULL;
    No_atual->direita = NULL;
  }
  else if(x==1) {
    No_atual->esquerda = insere(cod, No_atual->esquerda,x);
  }
  else {
    No_atual->direita = insere(cod, No_atual->direita,x);
  }
  return No_atual;
}


void jogo_animal(Arvore*arvore);

void inicio(Arvore*arvore){
  printf("Pense num animal\n");

  jogo_animal(arvore);
}

void pergunta(No* no_atual, int x, Arvore*arvore){
  char animal[64], caract[64];
  if(x == 1){
    if (no_atual->esquerda == NULL){
      printf("acertei");
      return;
    }
    printf("Seu animal %s?\n-> ", no_atual->esquerda);

    scanf("%i", &x);
    getchar();
    
    pergunta(no_atual->esquerda, x, arvore);
    
  
  }else{
    if (no_atual->direita == NULL){
      printf("Qual animal voce pensou?\n-> ");
 
      scanf("%[^\n]s", animal);
      getchar();

      printf("O que o %s faz?\n-> ", animal);
 
      scanf("%[^\n]s", caract);
      getchar();
      no_atual = insere(caract, no_atual, x);
      no_atual->direita = insere(animal, no_atual->direita, 1);
      inicio(arvore);
      return;
      }
    printf("Seu animal %s\n-> ", no_atual->direita);
    scanf("%i", &x);
    getchar();
    pergunta(no_atual->direita, x, arvore);
  }
}

void jogo_animal(Arvore*arvore){
  int x = 0;
  char caracteristica[64];
  printf("SIM = 1  NAO = 2\n" );
  printf("Seu animal eh %s?\n-> ", arvore->raiz);
  scanf("%i",&x);
  getchar();
  pergunta(arvore->raiz, x, arvore);
  return;
}  


int main(){
 
  char respo;
  int i=10;
  Arvore *arvore = malloc(sizeof(Arvore));
  arvore->raiz = insere("terrestre",arvore->raiz,0);
  arvore->raiz = insere("late",arvore->raiz,1);
  arvore->raiz = insere("cachorro",arvore->raiz,1);
  inicio(arvore);
}
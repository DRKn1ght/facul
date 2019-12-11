#include <stdio.h>
#include <math.h>
#include <stdlib.h>

  typedef enum{false, true} boolean;

  typedef struct No{
  int codigo;
  struct No* esquerda;
  struct No* direita;
}No;

  typedef struct{
  No* raiz;
}Arvore;

void cria_arvore(Arvore* arv) {
  arv->raiz = NULL;
}

boolean eh_nulo(No* No_atual) {
  return (No_atual == NULL);
}


No* insere(int cod, No* No_atual) {
  if(eh_nulo(No_atual)) {
    
    No_atual = (No*) malloc(sizeof(No));
    No_atual->codigo = cod;
    No_atual->esquerda = NULL;
    No_atual->direita = NULL;
  }
  else if(cod < No_atual->codigo) {
    
    No_atual->esquerda = insere(cod, No_atual->esquerda);
    
  }
  else {
    
    No_atual->direita = insere(cod, No_atual->direita);
  
  }
  return No_atual;
}

boolean pesquisa(int cod, No* No_atual) {
  if(No_atual == NULL) {
    return false;
  }
  else if(cod < No_atual->codigo) {
    pesquisa(cod, No_atual->esquerda);
  }
  else if(cod > No_atual->codigo) {
  pesquisa(cod, No_atual->direita);
  }
  else {
  return true;
  }
}


No* antecessor(No *atual, No *ant) {
  if(ant->direita != NULL)
    ant->direita = antecessor(atual,
    ant->direita);
  else {
    No *aux;
    atual->codigo = ant->codigo;
    aux = ant;
    ant = ant->esquerda;
    free(aux);
  }
  return ant;
  }


No* remocao(int cod, No* No_atual) {
  No* aux;
  if(No_atual == NULL)
    return NULL;
  else if(cod < No_atual->codigo)
  No_atual->esquerda = remocao(cod, No_atual->esquerda);
  
  else if(cod > No_atual->codigo)
  No_atual->direita = remocao(cod, No_atual->direita);
  
  else if(No_atual->direita == NULL) {
    aux = No_atual;
    No_atual = No_atual->esquerda;
    free(aux);
  }
  else if(No_atual->esquerda == NULL) {
    aux = No_atual;
    No_atual = No_atual->direita;
  free(aux);
}
else {
  No_atual->esquerda = antecessor(No_atual,
  No_atual->esquerda);
  }
  return No_atual;
}


int altura(No* No_atual){
  if(No_atual == NULL || No_atual->esquerda == NULL && No_atual->direita == NULL){
    return 0;
  }
  
  if(altura(No_atual->esquerda) > altura(No_atual->direita))
    return altura(No_atual->esquerda)+1;
  else
    return altura(No_atual->direita)+1;
  }

int arvoreNivel(No* No_atual){
  return altura(No_atual) - 1;
}

void pre_ordem(No* No_atual) {
  if(No_atual != NULL) {
  printf("%d \n", No_atual->codigo);
  pre_ordem(No_atual->esquerda);
  pre_ordem(No_atual->direita);
  }
}

void em_ordem(No* No_atual) {
  if(No_atual != NULL) {
  em_ordem(No_atual->esquerda);
  printf("%d \n", No_atual->codigo);
  em_ordem(No_atual->direita);

  }
}


void pos_ordem(No* No_atual) {
  if(No_atual != NULL) {
  pos_ordem(No_atual->esquerda);
  pos_ordem(No_atual->direita);
  printf("%d \n", No_atual->codigo);
  }
}

int contarNos(No *pRaiz){
   if(pRaiz == NULL)
        return 0;
   else
        return 1 + contarNos(pRaiz->esquerda) + contarNos(pRaiz->direita);
}

boolean eh_folha(No *No_atual) 
{ 
   if (No_atual == NULL) 
       return false; 
   if (No_atual->esquerda == NULL && No_atual->direita == NULL) 
       return true; 
   return false; 
} 

int soma_folha(No* No_atual){
  if(No_atual==NULL){   
    return 0;
  } 

  if(eh_folha(No_atual)){   
    return No_atual->codigo;
  }           
  return soma_folha(No_atual->esquerda) + soma_folha(No_atual->direita);  
}


int contarFolhas(No *pRaiz){
   if(pRaiz == NULL)
        return 0;
   if(pRaiz->esquerda == NULL && pRaiz->direita == NULL)
        return 1;
   return contarFolhas(pRaiz->esquerda) + contarFolhas(pRaiz->direita);
}


int nivel_no(int x,No *No_atual){
  if(pesquisa(x,No_atual)==true){
  }
}

int pega_nivel(No *No_atual,int cod, int nivel) 
{ 
    if (No_atual == NULL) 
        return 0; 
  
    if (No_atual -> codigo == cod) 
        return nivel; 
  
    int downlevel = pega_nivel(No_atual -> esquerda,cod, nivel + 1); 
    if (downlevel != 0) 
        return downlevel; 
  
    downlevel = pega_nivel(No_atual->direita, cod, nivel + 1); 
    return downlevel; 
}
  

int nivelNo(No *No_atual, int cod) 
{ 
    return pega_nivel(No_atual, cod, 1); 
} 
 
boolean Descendentes(No *No_atual, int x) 
{ 
  
  if (No_atual == NULL) 
     return false; 
  
  if (No_atual->codigo == x){
     pre_ordem(No_atual);
     return true;
  }else{
    Descendentes(No_atual->direita, x);
    Descendentes(No_atual->esquerda, x);
  }
  
  return false; 
}


int main(){
  int x = 0, p, i = 1, resp  = 0, inserir;
  float y;
  Arvore *arvore = malloc(sizeof(Arvore));
  cria_arvore(arvore);

  printf("MENU\n");
  while(i!= 11){
    printf("\nDigite a opcao desejada\n");
        printf("OPCAO 1- INSERE \n");
        printf("OPCAO 2- PESQUISA\n");
        printf("OPCAO 3- IMPRIME \n");
        printf("OPCAO 4- ALTURA \n");
        printf("OPCAO 5- SOMA FOLHA \n");
        printf("OPCAO 6 - NUMERO DE NOS\n");
        printf("OPCAO 7 - NUMERO DE FOLHAS\n");
        printf("OPCAO 8 - NIVEL DE UM NO\n");
        printf("OPCAO 9 - NIVEL DA ARVORE\n");
        printf("OPCAO 10 - IMPRIMIR DESCENDENTES NO\n");
        printf("OPCAO 11- ENCERRAR O PROGRAMA\n");
        scanf("%d",&i);
          //switch case
    switch(i){
        case 1:
        
        scanf("%d",&inserir);
        arvore->raiz = insere(inserir, arvore->raiz);         
         
        break;    
        case 2:
        printf("digite o numero desejado\n");
        scanf("%d",&p);

        if(pesquisa(p, arvore->raiz)){
          printf("O numero pesquisado esta presente");
        } 
        else{
          printf("nao esta presente\n");
        }          
        break;    

        case 3:
        printf("PRE ORDEM:\n");
        pre_ordem(arvore->raiz);
        printf("\n");
        printf("EM ORDEM:\n");
        em_ordem(arvore->raiz);
        printf("\n");
        printf("POS ORDEM:\n");
        pos_ordem(arvore->raiz);


        break;    

        case 4:
          x = altura(arvore->raiz);
          printf("A altura eh %d\n", x);
         
        
        break; 

        case 5:

         x = soma_folha(arvore->raiz); 
         printf("A soma eh %d",x);
        break;

        case 6:
        x = contarNos(arvore->raiz);
        printf("Soma nos: %i", x);
        break;
        case 7:
        x = contarFolhas(arvore->raiz);
        printf("N' dos nos: %i", x);
        break;

        case 8:
        printf("\nDigite o elemento:\n> ");
        scanf("%i", &x);
        printf("nivel do no: %i",nivelNo(arvore->raiz, x));
        break;

        case 9:
        x = arvoreNivel(arvore->raiz);
        printf("Nivel da arvore: %i", x);
        break;

        case 10:
        printf("\nDigite o elemento:\n> ");
        scanf("%i", &x);
        Descendentes(arvore->raiz, x);

        default:
            printf("\n");    
    break;    
      } 
  }

return 0;
}
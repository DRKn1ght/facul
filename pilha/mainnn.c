#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
struct Pilha {
	int topo; /* posiÃ§Ã£o elemento topo */
	int tamanho;
	float *pElem;
};

void criapilha( struct Pilha *p, int c ){
   p->topo = -1;
   p->tamanho = c;
   p->pElem = (float*) malloc (c * sizeof(float));
}
int isEmpty ( struct Pilha *p ){

   if( p-> topo == -1 )
      return 1; 
    return 0; 
}

int isFull ( struct Pilha *p ){
	if (p->topo == p->tamanho - 1)
	    return 1;
	return 0;
}

void push ( struct Pilha *p, int v){
	p->topo++;
	p->pElem [p->topo] = v;
}

int pop ( struct Pilha *p ){
   float aux = p->pElem [p->topo];
   p->topo--;
   return aux;
}

int topo ( struct Pilha *p ){
   return p->pElem [p->topo];
}

int Operation(int x, int y, char op)
{
    int valor;
    struct Pilha minhapilha;
    switch (op){
        case '+':
            pop(&minhapilha);
            valor = x + y;
            break;

        case '-':
            pop(&minhapilha);
            valor = x - y;
            break;

        case '*':
            pop(&minhapilha);
            valor = x * y;
            break;

        case '/':
            pop(&minhapilha);
            valor = x / y;
            break;
        default:
        printf("a");
        break;
    }
    return valor;
}

int main(){

	struct Pilha minhapilha;
	int capacidade = 10, valor, i = 0, x, y;
    char a[256], op;
    criapilha (&minhapilha, capacidade);
    scanf("%[^\n]", a);
    while(a[i] != '\0'){
        if (isdigit(a[i]) == 0)
        {
            op = a[i];
            y = pop(&minhapilha);
            x = topo(&minhapilha);
            valor = Operation(x, y, op);
            push(&minhapilha, valor);
            printf("%i %c %i = %i\n", x, op, y, valor);
        }else{
            push(&minhapilha, a[i] - '0');
        }
        //printf(" %i, ", topo(&minhapilha));
        i++;
    }
    return 0;
	}


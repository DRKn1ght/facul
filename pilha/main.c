#include <stdio.h>
#include "pilha.h"
#include <ctype.h> //Para usar a função isdigit na linha 11
int main(){
	TPilha *vpilha;
    vpilha = criapilha();
	int valor, i = 0, x, y;
    char exp[256], op; //Exp = expressão; op = operação
    scanf("%[^\n]", exp); //scaneia uma string
    while(exp[i] != '\0'){ //'\0' em string = NULL
        if (isdigit(exp[i]) == 0)
        {
            op = exp[i]; //Salva o operador (+, -, *, /)
            y = pop(vpilha); //Valor do primeiro número a ser operado
            x = topo(vpilha); //Valor do segundo número a ser operado
            valor = Operation(x, y, op);
            push(vpilha, valor); //Empilha o resultado na lista
            printf("%i %c %i = %i\n", x, op, y, valor);
        }else{
            push(vpilha, exp[i] - '0'); // - '0' é para converter um char para int. '0' em int é o valor em char do elemento 0, que no caso é 48.
        }
        i++;
    }
    return 0;
	}
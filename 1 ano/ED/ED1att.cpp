#include <iostream>
#include <malloc.h>
using namespace std;
struct lista
{
    int element;
    struct lista *prox;
};
lista *head = NULL, *tail = NULL; 

void imprimir(lista *pe)
{
    if (pe == NULL)
    {
        cout << "A lista esta vazia" << endl;
    }else{
        while(pe != NULL)
        {
            cout << pe->element << " ";
            pe = pe->prox;
        }
        cout << endl;
    }
}

void inserir(int x, lista *p)
{
    lista *nova;
    nova = (lista*)malloc(sizeof(lista));
    nova->element = x;
    nova->prox = NULL;
    if (p == NULL)
    {
        head = nova;
        tail = nova;
    }else{
        tail->prox = nova;
        tail = tail->prox;
    }
    cout << "Elemento " << x << " inserido." << endl;
}

lista* procurar(int x, lista *p)
{
    lista *pe = NULL;
    lista *aux = p;
    while (aux != NULL)
    {
        if (aux->element == x){
            pe = aux;
            break;
        }
        aux = aux->prox;
    }
    return pe;
}

void inserir_pos(int x, int y, lista *p)
{
	lista *HTemp = procurar(y, p);
    if (HTemp == NULL){
        cout << "O elemento " << y << " nao esta na lista" << endl;
        return;
    }
    lista *novo;
    novo = (lista*)malloc(sizeof(lista));
    novo->element = x;
    novo->prox = HTemp->prox;
    HTemp->prox = novo;
    cout << "Elemento " << x << " inserido na frente do elemento " << y << endl;  
}
 
void deletar(int x, lista *p)
{
	lista* HTemp = procurar(x, p);
	if (HTemp == NULL){
        cout << "O elemento " << x << " nao esta na lista" << endl;
        return;
    }
    lista *aux = p;
    lista *pe = NULL;
    if (HTemp == head)
    {
    	head = HTemp->prox;
    	HTemp->prox = NULL;
    	free(HTemp);
    	return;
    }else{
    while (aux != NULL)
    {
        if (aux->prox->element == x){
            pe = aux;
            break;
        }
        aux = aux->prox;
    }
}
    pe->prox = HTemp->prox;
    free(HTemp);

}

int main ()
{
        cout << "[1] - Inserir um valor na lista\n"
            "[2] - Inserir um valor no meio\n"
            "[3] - Imprimir lista\n"
            "[4] - Mostrar o menu novamente\n"
            "[0] - Finalizar\n";
    int option, p1, p2, on = 1;
    while (on == 1)
    {
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Digite o valor a ser inserido: ";
            cin >> p1;
            inserir(p1, head);
            break;

        case 2:
            cout << "\nDigite o valor a ser inserido e o valor que o antecederá: ";
            cin >> p1 >> p2;
            inserir_pos(p1, p2, head);
            break;
        
        case 3:
            imprimir(head);
            break;
        
        case 4:
            cout << "[1] - Inserir um valor na lista\n"
                    "[2] - Inserir um valor no meio\n"
                    "[3] - Imprimir lista\n"
                    "[4] - Mostrar o menu novamente\n"
                    "[0] - Finalizar\n";

        break;
        case 5:
        cin >> p1;
        deletar(p1, head);
        break;

        case 0:
        	on == 0;
            break;

        default:
            break;
        }
    }
    return 0;
}
#include <iostream>
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
            cout << pe->element << endl;
            pe = pe->prox;
        }
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

int procurar(int x, lista *p)
{
    int encontrou = 0;
    while (p != NULL)
    {
        if (p->element == x){
            encontrou = 1;
            break;
        }
        p = p->prox;
    }
    return encontrou;
}

void inserir_pos(int x, int y, lista *p)
{
    if (procurar(y, p) == 0){
        cout << "O elemento " << y << " nao esta na lista" << endl;
        return;
    }
    lista *novo;
    lista *HTemp = head;
    novo = (lista*)malloc(sizeof(lista));
    novo->element = x;
    novo->prox = NULL;
    while (p != NULL)
    {
        if (p->element == y){
            HTemp = p;
            break;
        }
        p = p->prox;
    }
    novo->prox = HTemp->prox;
    p->prox = novo;
   cout << "Elemento " << x << " inserido na frente do elemento " << y << endl;  
}
 
int main ()
{
        cout << "[1] - Inserir um valor na lista\n"
            "[2] - Inserir um valor no meio\n"
            "[3] - Imprimir lista\n"
            "[4] - Mostrar o menu novamente\n"
            "[0] - Finalizar\n";
    int option, p1, p2;
    while (true)
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

        case 0:
            break;

        default:
            break;
        }
    }
    return 0;
}
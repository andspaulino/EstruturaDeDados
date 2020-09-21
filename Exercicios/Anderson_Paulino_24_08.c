// Anderson de Souza Paulino, 00101112.
#include <stdio.h>
#include <stdlib.h>

// Em C crie uma estrutura que represente um nó de uma árvore;
typedef struct no
{
    int chave;
    struct no *esq;
    struct no *dir;
};

//Defina um tipo novo para ponteiros dessa estrutura para não precisarmos ficar o tempo todo usando notação de ponteiros;
typedef struct no *no;

//Crie a função de inicializar a arvore. Ela deverá retornar um ponteiro para nó
//(na verdade deve ser usado o tipo que você definiu no item anterior). Por hora o retorno deverá ser nulo;
no criarArvore()
{
    return NULL;
}

//Crie a função que cria um novo nó. Ele não é inserido na árvore, a função que insere será outra.
no criarNo(int valor)
{
    no novo = (no)malloc(sizeof(no));
    novo->chave = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int main()
{
    return 0;
}
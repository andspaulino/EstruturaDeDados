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
typedef struct no *NO;

//Crie a função de inicializar a arvore. Ela deverá retornar um ponteiro para nó
//(na verdade deve ser usado o tipo que você definiu no item anterior). Por hora o retorno deverá ser nulo;
NO criarArvore()
{
    return NULL;
}

//Crie a função que cria um novo nó. Ele não é inserido na árvore, a função que insere será outra.
NO criarNo(int valor)
{
    NO novo = (NO)malloc(sizeof(NO));
    novo->chave = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

//Função para ixibir a arvore
void exibirArvore(NO raiz)
{
    if (raiz != NULL)
    {
        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

//Função para adionar elementos.
NO adiciona(NO raiz, NO no)
{
    if (raiz == NULL)
        return no;
    else
    {
        if (no->chave < raiz->chave)
            raiz->esq = adiciona(raiz->esq, no);
        else
            raiz->dir = adiciona(raiz->dir, no);
    }
    return raiz;
}

int main()
{
    int valor;

    NO r = criarArvore();
    NO novo = criarNo(valor);

    //Loop para adicionar elementos a arvore
    do
    {
        printf("Digite um valor positivo a para arvore: ");
        scanf("%i", &valor);

        if (valor == 0)
        {
            break;
        }

        novo = criarNo(valor);
        r = adiciona(r, novo);
    } while (valor != 0);

    exibirArvore(r);
}

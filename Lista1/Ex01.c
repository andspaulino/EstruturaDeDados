//Anderson de Souza Paulino, 00101112

#include <stdio.h>
#include <stdlib.h>

//declara o nó
struct no
{
    int valor;
    struct no *prox;
};

//imprime na tela a lista
void mostrarListaEncadeada(struct no *p)
{
    while (p)
    {
        printf("%d ", p->valor);
        p = p->prox;
    }
}

void gerarSequenciaFibonacci(int quantidadeDeItems)
{
    struct no *fibonacci[quantidadeDeItems];

    for (int i = 0; i < quantidadeDeItems; i++)
    {
        //aloca a memoria
        fibonacci[i] = (struct no *)malloc(sizeof(struct no *));

        //atribui os valores
        if (i >= 2)
        {
            fibonacci[i]->valor = fibonacci[i - 1]->valor + fibonacci[i - 2]->valor;
        }
        else
        {
            fibonacci[i]->valor = 1;
        }
    }

    //conecta os nos
    for (int i = 0; i < quantidadeDeItems; i++)
    {
        if (quantidadeDeItems - 1 == i)
        {
            fibonacci[i]->prox = NULL;
        }
        else
        {
            fibonacci[i]->prox = fibonacci[i + 1];
        }
    }

    //mostra o resultado
    if (fibonacci[0])
    {
        printf("\nSequencia de Fibonacci:\n");
        mostrarListaEncadeada(fibonacci[0]);
        inverterSequencia(&fibonacci[0]);
        printf("\nSequencia de Fibonacci Invertida:\n");
        mostrarListaEncadeada(fibonacci[0]);
        printf("\n");
    }
}

void inverterSequencia(struct no **referencia)
{
    struct no *anterior = NULL;
    struct no *atual = *referencia;
    struct no *proximo = NULL;
    while (atual != NULL)
    {
        // Armaneza o proximo valor;
        proximo = atual->prox;

        // Inverte o valor do ponteiro atual.
        atual->prox = anterior;

        // Passa o valor para o proximo.
        anterior = atual;
        atual = proximo;
    }
    *referencia = anterior;
}

int main(void)
{
    int tamanhoDaSequencia;

    printf("Inserir o tamanho desejado para a sequencia: ");
    scanf("%d", &tamanhoDaSequencia);

    gerarSequenciaFibonacci(tamanhoDaSequencia);
}
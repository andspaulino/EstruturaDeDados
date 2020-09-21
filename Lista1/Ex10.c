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

//Função para adicionar elementos.
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

//Verificar se há um determinado elemento
NO contem(int chave, NO raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (raiz->chave == chave)
    {
        return raiz;
    }

    if (raiz->chave > chave)
    {
        return contem(chave, raiz->esq);
    }

    return contem(chave, raiz->dir);
}

//Função para verificar se há um determinado elemento modificada, utilizando a função anterior.
void contemNaArvore(int chave, NO raiz)
{
    NO n = contem(chave, raiz);

    //Se não encontrar o valor solicitado retorna mensagem.
    if (!n)
    {
        printf("\nO valor inserido não foi encontrado na arvore.");
        return;
    }

    //Se valor inserido for a raiz, informa ao usuario seus respectivos elementos, se houver.
    if (n == raiz)
    {
        printf("\nO nó encontrado é a raiz");
        if (n->esq)
        {
            printf("\nO elemento da esquerda é: %d", n->esq->chave);
        }

        if (n->dir)
        {
            printf("\nO elemento da direita é: %d", n->dir->chave);
        }

        return;
    }

    //Se o nó for uma folha, informa ao usuario.
    if (!n->esq && !n->dir)
    {
        printf("\nO nó encontrado é uma folha");
    }

    else
    {
        //Se for nó interno, informa ao usuario e caso exista, tambem infroma seus subelementos.
        printf("\nO nó encontrado é um nó interno");

        if (n->esq)
        {
            printf("\nO elemento da esquerda é: %d", n->esq->chave);
        }

        if (n->dir)
        {
            printf("\nO elemento da direita é: %d", n->dir->chave);
        }
    }
}

// Busca bin�ria n�o recursiva, para que possamos ter o pai do n� cuja chave n�s procuramos
// fun��o auxiliar para a remo��o
NO buscaNo(NO raiz, int ch, NO *pai)
{
    // Variavel auxiliar para a itera��o da arvore
    NO atual = raiz;
    // Como � um ponteiro para PONT, acaba sendo que essa variavel � um ponteiro para ponteiro.
    //Arqui vamos armazenar o endere�o do pai do elemento buscado
    *pai = NULL;
    // Enquanto atual for v�lido
    while (atual)
    {
        // se o elemento buscado for o atual, ent�o retornamos o elemento. Como o pai � um ponteiro
        // e alteramos ele diretamente, ele n�o precisa ser retornado
        if (atual->chave == ch)
            return atual;
        // Caso o elemento atual n�o seja o que estamos buscando, atualizamos o pai para ser igual
        // o elemento atual, para podermos continuar indo pela subarvore da esquerda ou da direita
        *pai = atual;
        // se a chave buscada for menor que do elemento atual, buscamos pela subarvore da esquerda
        if (ch < atual->chave)
            atual = atual->esq;
        // caso contrario buscamos pela subarvore da direita.
        else
            atual = atual->dir;
    }
    return NULL;
}

// Remover um n� da arvore em qualquer posi��o
// Para a remo��o precisamos garantir que a propriedades da arvore binaria ainda sejam v�lidas.
NO removeNo(int ch, NO raiz)
{
    NO pai, no, p, q;
    no = buscaNo(raiz, ch, &pai);
    if (no == NULL)
        return raiz;
    // Aqui tratamos o caso de o n� a ser removido ter apenas um filho
    if (!no->esq || !no->dir)
    {
        if (!no->esq)
            q = no->dir;
        else
            q = no->esq;
    }
    // Aqui tratamos o caso do n� ter os dois filhos
    else
    {
        // Se chegamos aqui, � porque o n� a aser buscado tem as duas subarvores
        // Nesse caso precisamos ir o mais a direita poss�vel na subarvore da esquerda
        // do no a ser removido. Nesse processo, sempre marcamos quem � o n� a direita e
        // o pai dele. Isso porque quiando chegarmos no elemento mais a direita,
        // teremos que fazer o pai dele "adotar" seus filhos, uma vez que o no mais a direita
        // ser� "promovido" para a posi��o do o no sendo removido
        p = no;
        q = no->esq;
        while (q->dir)
        {
            p = q;
            q = q->dir;
        }

        // Depois que encontramos o n� mais a esquerda, precisamos modificar os ponteiros para
        // que eles possam promover o no mais a direita e fazer a promo��o do no mais a direita da
        // subarvore da esquerda
        if (p != no)
        {
            p->dir = q->esq;
            q->esq = no->esq;
        }

        q->dir = no->dir;
    }

    // Aqui tratamos se o n� a ser movido � a raiz
    if (!pai)
    {
        free(no);
        return q;
    }

    // Aqui tratamos se o n� a ser removido n�o for a raiz
    if (ch < pai->chave)
        pai->esq = q;
    else
        pai->dir = q;
    free(no);
    return raiz;
}

// Contagem do total de n�s na �rvore
int totalDeNos(NO raiz)
{
    // Se a raiz for null, n�o temos n� nenhum, logo total � 0
    if (raiz == NULL)
        return 0;

    // Caminhamos pela subarvore da esquerda, quando voltamos para raiz, contamos ela
    // e depois vamos para subarvore da direita.
    // Aqui percebemos explicitamente que percorremos a �rovre in-ordem.
    // Podemos alterar o m�todo percorre-la e n�o vai influenciar na contagem,
    // mas se percorrermos para a impress�o dos dados da �rvore, por exemplo,
    // cada modo de percorrer produzir� um resultado diferente.
    return totalDeNos(raiz->esq) + 1 + totalDeNos(raiz->dir);
}

//Função para exibir a arvore
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

int main()
{
    int valor;
    int count = 0;

    NO r = criarArvore();
    NO novo = criarNo(valor);

    //Loop para adicionar elementos a arvore
    printf("\n\nCaso queira para a inserção, digite o caracter %d.\n", 0);
    do
    {
        printf("%d# - Digite um valor positivo a para arvore: ", count + 1);
        scanf("%i", &valor);

        if (valor == 0)
        {
            break;
        }

        novo = criarNo(valor);
        r = adiciona(r, novo);
        count++;
    } while (valor != 0);

    //Imprimi a arvore.
    printf("\nA arvore gerada: \n");
    exibirArvore(r);

    //Chama a função para busca MODIFICADA.
    printf("\n\nInsira o valor a ser buscado na arvore: ");
    scanf("%i", &valor);
    contemNaArvore(valor, r);

    //Exibe total de nos.
    printf("\nTotal de elementos: %d\n", totalDeNos(r));

    //Remove algum elemento.
    printf("\n\nQuer remover algum elemento?\n");
    printf("1 - SIM.\n");
    printf("2 - NÃO.\n");
    scanf("%d", &valor);

    if (valor == 1)
    {
        printf("Qual elemento quer remover?\n");
        scanf("%d", &valor);
        r = removeNo(valor, r);
        //Imprime a arvore novamente.
        printf("\n\n");
        exibirArvore(r);
        printf("\n\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No
{
    Item dados;
    struct No *proximo;
} No;

// ------------------- VARIÁVEIS GLOBAIS PARA CONTADORES -------------------
int comparacoesBuscaSequencial = 0;
int comparacoesBuscaBinaria = 0;

// ------------------- FUNÇÕES PARA VETOR -------------------

// Inserir item no vetor
void inserirItemVetor(Item vetor[], int *qtdItens)
{
    if (*qtdItens >= MAX_ITENS)
    {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item (max 29 caracteres): ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    if (novoItem.quantidade <= 0)
    {
        printf("Quantidade invalida. Operacao cancelada.\n");
        return;
    }

    vetor[*qtdItens] = novoItem;
    (*qtdItens)++;

    printf("Item '%s' cadastrado com sucesso no vetor!\n", novoItem.nome);
}

// Remover item do vetor por nome
void removerItemVetor(Item vetor[], int *qtdItens)
{
    if (*qtdItens == 0)
    {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < *qtdItens; i++)
    {
        if (strcmp(vetor[i].nome, nomeBusca) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Item '%s' nao encontrado no vetor.\n", nomeBusca);
        return;
    }

    for (int i = pos; i < *qtdItens - 1; i++)
    {
        vetor[i] = vetor[i + 1];
    }
    (*qtdItens)--;

    printf("Item '%s' removido com sucesso do vetor!\n", nomeBusca);
}

// Listar itens do vetor
void listarItensVetor(Item vetor[], int qtdItens)
{
    if (qtdItens == 0)
    {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila (vetor):\n");
    printf("-------------------------------\n");
    for (int i = 0; i < qtdItens; i++)
    {
        printf("Nome: %s\n", vetor[i].nome);
        printf("Tipo: %s\n", vetor[i].tipo);
        printf("Quantidade: %d\n", vetor[i].quantidade);
        printf("-------------------------------\n");
    }
}

// Ordenar vetor por nome (Selection Sort)
void ordenarVetor(Item vetor[], int qtdItens)
{
    for (int i = 0; i < qtdItens - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < qtdItens; j++)
        {
            if (strcmp(vetor[j].nome, vetor[min_idx].nome) < 0)
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            Item temp = vetor[i];
            vetor[i] = vetor[min_idx];
            vetor[min_idx] = temp;
        }
    }
    printf("Vetor ordenado por nome com sucesso.\n");
}

// Busca sequencial no vetor (retorna índice ou -1)
int buscarSequencialVetor(Item vetor[], int qtdItens, const char *nomeBusca)
{
    comparacoesBuscaSequencial = 0;
    for (int i = 0; i < qtdItens; i++)
    {
        comparacoesBuscaSequencial++;
        if (strcmp(vetor[i].nome, nomeBusca) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Busca binária no vetor ordenado (retorna índice ou -1)
int buscarBinariaVetor(Item vetor[], int qtdItens, const char *nomeBusca)
{
    comparacoesBuscaBinaria = 0;
    int inicio = 0;
    int fim = qtdItens - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        comparacoesBuscaBinaria++;
        int cmp = strcmp(vetor[meio].nome, nomeBusca);
        if (cmp == 0)
        {
            return meio;
        }
        else if (cmp < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
    return -1;
}

// ------------------- FUNÇÕES PARA LISTA ENCADEADA -------------------

// Inserir item no início da lista encadeada
void inserirItemLista(No **cabeca)
{
    // Contar tamanho da lista para limitar a 10 itens
    int tamanho = 0;
    No *aux = *cabeca;
    while (aux != NULL)
    {
        tamanho++;
        aux = aux->proximo;
    }
    if (tamanho >= MAX_ITENS)
    {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item (max 29 caracteres): ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    if (novoItem.quantidade <= 0)
    {
        printf("Quantidade invalida. Operacao cancelada.\n");
        return;
    }

    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo)
    {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    novoNo->dados = novoItem;
    novoNo->proximo = *cabeca;
    *cabeca = novoNo;

    printf("Item '%s' cadastrado com sucesso na lista encadeada!\n", novoItem.nome);
}

// Remover item da lista encadeada por nome
void removerItemLista(No **cabeca)
{
    if (*cabeca == NULL)
    {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No *atual = *cabeca;
    No *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->dados.nome, nomeBusca) == 0)
        {
            if (anterior == NULL)
            {
                // Remover o primeiro nó
                *cabeca = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item '%s' removido com sucesso da lista encadeada!\n", nomeBusca);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item '%s' nao encontrado na lista encadeada.\n", nomeBusca);
}

// Listar itens da lista encadeada
void listarItensLista(No *cabeca)
{
    if (cabeca == NULL)
    {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila (lista encadeada):\n");
    printf("-------------------------------\n");
    No *atual = cabeca;
    while (atual != NULL)
    {
        printf("Nome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);
        printf("-------------------------------\n");
        atual = atual->proximo;
    }
}

// Busca sequencial na lista encadeada (retorna ponteiro para nó ou NULL)
No *buscarSequencialLista(No *cabeca, const char *nomeBusca)
{
    comparacoesBuscaSequencial = 0;
    No *atual = cabeca;
    while (atual != NULL)
    {
        comparacoesBuscaSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// ------------------- MENU E FLUXO PRINCIPAL -------------------

void menuVetor(Item vetor[], int *qtdItens)
{
    int opcao;
    do
    {
        printf("\n--- Sistema de Mochila (Vetor) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (busca sequencial)\n");
        printf("5 - Ordenar itens por nome\n");
        printf("6 - Buscar item (busca binaria) [apenas apos ordenar]\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            inserirItemVetor(vetor, qtdItens);
            break;
        case 2:
            removerItemVetor(vetor, qtdItens);
            break;
        case 3:
            listarItensVetor(vetor, *qtdItens);
            break;
        case 4:
        {
            if (*qtdItens == 0)
            {
                printf("Mochila vazia. Nenhum item para buscar.\n");
                break;
            }
            char nomeBusca[30];
            printf("Digite o nome do item a buscar (busca sequencial): ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            int pos = buscarSequencialVetor(vetor, *qtdItens, nomeBusca);
            if (pos != -1)
            {
                printf("Item encontrado:\n");
                printf("Nome: %s\n", vetor[pos].nome);
                printf("Tipo: %s\n", vetor[pos].tipo);
                printf("Quantidade: %d\n", vetor[pos].quantidade);
            }
            else
            {
                printf("Item '%s' nao encontrado.\n", nomeBusca);
            }
            printf("Comparacoes realizadas: %d\n", comparacoesBuscaSequencial);
            break;
        }
        case 5:
            ordenarVetor(vetor, *qtdItens);
            break;
        case 6:
        {
            if (*qtdItens == 0)
            {
                printf("Mochila vazia. Nenhum item para buscar.\n");
                break;
            }
            char nomeBusca[30];
            printf("Digite o nome do item a buscar (busca binaria): ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            int pos = buscarBinariaVetor(vetor, *qtdItens, nomeBusca);
            if (pos != -1)
            {
                printf("Item encontrado:\n");
                printf("Nome: %s\n", vetor[pos].nome);
                printf("Tipo: %s\n", vetor[pos].tipo);
                printf("Quantidade: %d\n", vetor[pos].quantidade);
            }
            else
            {
                printf("Item '%s' nao encontrado.\n", nomeBusca);
            }
            printf("Comparacoes realizadas: %d\n", comparacoesBuscaBinaria);
            break;
        }
        case 0:
            printf("Retornando ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void menuLista(No **cabeca)
{
    int opcao;
    do
    {
        printf("\n--- Sistema de Mochila (Lista Encadeada) ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (busca sequencial)\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            inserirItemLista(cabeca);
            break;
        case 2:
            removerItemLista(cabeca);
            break;
        case 3:
            listarItensLista(*cabeca);
            break;
        case 4:
        {
            if (*cabeca == NULL)
            {
                printf("Mochila vazia. Nenhum item para buscar.\n");
                break;
            }
            char nomeBusca[30];
            printf("Digite o nome do item a buscar (busca sequencial): ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            No *resultado = buscarSequencialLista(*cabeca, nomeBusca);
            if (resultado != NULL)
            {
                printf("Item encontrado:\n");
                printf("Nome: %s\n", resultado->dados.nome);
                printf("Tipo: %s\n", resultado->dados.tipo);
                printf("Quantidade: %d\n", resultado->dados.quantidade);
            }
            else
            {
                printf("Item '%s' nao encontrado.\n", nomeBusca);
            }
            printf("Comparacoes realizadas: %d\n", comparacoesBuscaSequencial);
            break;
        }
        case 0:
            printf("Retornando ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main()
{
    Item mochilaVetor[MAX_ITENS];
    int qtdItensVetor = 0;
    No *mochilaLista = NULL;

    int opcaoPrincipal;

    printf("=== Sistema de Mochila: Vetor vs Lista Encadeada ===\n");

    do
    {
        printf("\nEscolha a estrutura de dados para a mochila:\n");
        printf("1 - Vetor (lista sequencial)\n");
        printf("2 - Lista encadeada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch (opcaoPrincipal)
        {
        case 1:
            menuVetor(mochilaVetor, &qtdItensVetor);
            break;
        case 2:
            menuLista(&mochilaLista);
            break;
        case 0:
            printf("Encerrando o sistema. Boa sorte na ilha!\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcaoPrincipal != 0);

    // Liberar memória da lista encadeada antes de sair
    No *atual = mochilaLista;
    while (atual != NULL)
    {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    return 0;
}

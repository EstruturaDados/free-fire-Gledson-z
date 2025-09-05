#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item que representa cada objeto coletado
typedef struct
{
    char nome[30];  // Nome do item
    char tipo[20];  // Tipo do item (ex: arma, munição, cura)
    int quantidade; // Quantidade do item
} Item;

// Protótipos das funções
void inserirItem(Item inventario[], int *qtdItens);
void removerItem(Item inventario[], int *qtdItens);
void listarItens(Item inventario[], int qtdItens);
void buscarItem(Item inventario[], int qtdItens);

int main()
{
    Item inventario[MAX_ITENS]; // Vetor que armazena até 10 itens
    int qtdItens = 0;           // Quantidade atual de itens no inventário
    int opcao;

    printf("=== Sistema de Inventario Inicial ===\n");

    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch (opcao)
        {
        case 1:
            inserirItem(inventario, &qtdItens);
            listarItens(inventario, qtdItens);
            break;
        case 2:
            removerItem(inventario, &qtdItens);
            listarItens(inventario, qtdItens);
            break;
        case 3:
            listarItens(inventario, qtdItens);
            break;
        case 4:
            buscarItem(inventario, qtdItens);
            break;
        case 0:
            printf("Encerrando o sistema. Boa sorte na ilha!\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

/**
 * Função para inserir um novo item no inventário.
 * Recebe o vetor de itens e o ponteiro para a quantidade atual.
 * Verifica se há espaço e cadastra o item com dados fornecidos pelo jogador.
 */
void inserirItem(Item inventario[], int *qtdItens)
{
    if (*qtdItens >= MAX_ITENS)
    {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item (max 29 caracteres): ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remove o \n do fgets

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // Limpar buffer

    if (novoItem.quantidade <= 0)
    {
        printf("Quantidade invalida. Operacao cancelada.\n");
        return;
    }

    // Adiciona o novo item no vetor
    inventario[*qtdItens] = novoItem;
    (*qtdItens)++;

    printf("Item '%s' cadastrado com sucesso!\n", novoItem.nome);
}

/**
 * Função para remover um item do inventário pelo nome.
 * Recebe o vetor de itens e o ponteiro para a quantidade atual.
 * Realiza busca sequencial para localizar o item e remove deslocando os demais.
 */
void removerItem(Item inventario[], int *qtdItens)
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
        if (strcmp(inventario[i].nome, nomeBusca) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
        return;
    }

    // Remove o item deslocando os seguintes para a esquerda
    for (int i = pos; i < *qtdItens - 1; i++)
    {
        inventario[i] = inventario[i + 1];
    }
    (*qtdItens)--;

    printf("Item '%s' removido com sucesso!\n", nomeBusca);
}

/**
 * Função para listar todos os itens cadastrados no inventário.
 * Recebe o vetor de itens e a quantidade atual.
 * Exibe os dados de cada item de forma clara.
 */
void listarItens(Item inventario[], int qtdItens)
{
    if (qtdItens == 0)
    {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    printf("-------------------------------\n");
    for (int i = 0; i < qtdItens; i++)
    {
        printf("Nome: %s\n", inventario[i].nome);
        printf("Tipo: %s\n", inventario[i].tipo);
        printf("Quantidade: %d\n", inventario[i].quantidade);
        printf("-------------------------------\n");
    }
}

/**
 * Função para buscar um item pelo nome no inventário.
 * Recebe o vetor de itens e a quantidade atual.
 * Realiza busca sequencial e exibe os dados do item encontrado.
 */
void buscarItem(Item inventario[], int qtdItens)
{
    if (qtdItens == 0)
    {
        printf("Mochila vazia. Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < qtdItens; i++)
    {
        if (strcmp(inventario[i].nome, nomeBusca) == 0)
        {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Tipo: %s\n", inventario[i].tipo);
            printf("Quantidade: %d\n", inventario[i].quantidade);
            return;
        }
    }

    printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
}

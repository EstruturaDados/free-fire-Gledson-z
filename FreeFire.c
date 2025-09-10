#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 10

// Struct que representa um componente da torre
typedef struct
{
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para contagem de comparações
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;
int comparacoesBuscaBinaria = 0;

// Função para limpar o buffer do teclado (stdin)
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função para cadastrar componentes
void cadastrarComponentes(Componente componentes[], int *qtd)
{
    printf("Cadastro de componentes (max %d):\n", MAX_COMPONENTES);
    while (*qtd < MAX_COMPONENTES)
    {
        Componente c;
        printf("\nComponente %d:\n", *qtd + 1);

        printf("Nome (max 29 chars): ");
        fgets(c.nome, sizeof(c.nome), stdin);
        c.nome[strcspn(c.nome, "\n")] = '\0';
        if (strlen(c.nome) == 0)
        {
            printf("Nome vazio, encerrando cadastro.\n");
            break;
        }

        printf("Tipo (ex: controle, suporte, propulsao): ");
        fgets(c.tipo, sizeof(c.tipo), stdin);
        c.tipo[strcspn(c.tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        if (scanf("%d", &c.prioridade) != 1)
        {
            printf("Entrada invalida para prioridade.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (c.prioridade < 1 || c.prioridade > 10)
        {
            printf("Prioridade invalida. Deve ser entre 1 e 10.\n");
            continue;
        }

        componentes[*qtd] = c;
        (*qtd)++;
    }
    printf("\nCadastro finalizado. Total de componentes: %d\n", *qtd);
}

// Bubble sort por nome (string)
void bubbleSortNome(Componente componentes[], int n)
{
    comparacoesBubble = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            comparacoesBubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0)
            {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou)
            break; // Otimização: para se não houve troca
    }
}

// Insertion sort por tipo (string)
void insertionSortTipo(Componente componentes[], int n)
{
    comparacoesInsertion = 0;
    for (int i = 1; i < n; i++)
    {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0)
        {
            comparacoesInsertion++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0)
            {
                componentes[j + 1] = componentes[j];
                j--;
            }
            else
            {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Selection sort por prioridade (int)
void selectionSortPrioridade(Componente componentes[], int n)
{
    comparacoesSelection = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            comparacoesSelection++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade)
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            Componente temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
        }
    }
}

// Busca binária por nome (string) - vetor deve estar ordenado por nome
int buscaBinariaPorNome(Componente componentes[], int n, const char *nomeBusca)
{
    comparacoesBuscaBinaria = 0;
    int inicio = 0, fim = n - 1;
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        comparacoesBuscaBinaria++;
        int cmp = strcmp(componentes[meio].nome, nomeBusca);
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

// Mostrar componentes formatados
void mostrarComponentes(Componente componentes[], int n)
{
    if (n == 0)
    {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("\nComponentes:\n");
    printf("-------------------------------------------------\n");
    printf("| %-29s | %-15s | Prioridade |\n", "Nome", "Tipo");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %-29s | %-15s |     %2d     |\n",
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("-------------------------------------------------\n");
}

// Função para medir tempo de execução de um algoritmo de ordenação
typedef void (*AlgoritmoOrdenacao)(Componente[], int);

void medirTempo(AlgoritmoOrdenacao algoritmo, Componente componentes[], int n, int *comparacoes, const char *nomeAlgoritmo)
{
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, componentes, sizeof(Componente) * n);

    clock_t inicio = clock();
    algoritmo(copia, n);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Definir o ponteiro para a variável global correta de comparações
    if (strcmp(nomeAlgoritmo, "Bubble Sort (Nome)") == 0)
    {
        *comparacoes = comparacoesBubble;
    }
    else if (strcmp(nomeAlgoritmo, "Insertion Sort (Tipo)") == 0)
    {
        *comparacoes = comparacoesInsertion;
    }
    else if (strcmp(nomeAlgoritmo, "Selection Sort (Prioridade)") == 0)
    {
        *comparacoes = comparacoesSelection;
    }
    else
    {
        *comparacoes = 0;
    }

    printf("\n%s concluido.\n", nomeAlgoritmo);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Comparacoes realizadas: %d\n", *comparacoes);

    // Mostrar componentes ordenados
    mostrarComponentes(copia, n);
}

// Menu principal e fluxo do programa
void menu()
{
    Componente componentes[MAX_COMPONENTES];
    int qtdComponentes = 0;
    int ordenadoPorNome = 0; // flag para indicar se vetor está ordenado por nome

    printf("=== Sistema de Montagem da Torre de Fuga ===\n");
    cadastrarComponentes(componentes, &qtdComponentes);

    if (qtdComponentes == 0)
    {
        printf("Nenhum componente cadastrado. Encerrando programa.\n");
        return;
    }

    int opcao;
    do
    {
        printf("\nEscolha a estrategia de ordenacao:\n");
        printf("1 - Por Nome\n");
        printf("2 - Por Tipo\n");
        printf("3 - Por Prioridade\n");
        printf("4 - Buscar componente-chave (busca binaria por nome) [apenas apos ordenar por nome]\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao)
        {
        case 1:
            // Ordenar por nome com bubble sort e mostrar resultados
            bubbleSortNome(componentes, qtdComponentes);
            ordenadoPorNome = 1;
            printf("\nComponentes ordenados por nome (Bubble Sort):\n");
            mostrarComponentes(componentes, qtdComponentes);
            printf("Comparacoes realizadas: %d\n", comparacoesBubble);
            break;

        case 2:
            // Ordenar por tipo com insertion sort e mostrar resultados
            insertionSortTipo(componentes, qtdComponentes);
            ordenadoPorNome = 0;
            printf("\nComponentes ordenados por tipo (Insertion Sort):\n");
            mostrarComponentes(componentes, qtdComponentes);
            printf("Comparacoes realizadas: %d\n", comparacoesInsertion);
            break;

        case 3:
            // Ordenar por prioridade com selection sort e mostrar resultados
            selectionSortPrioridade(componentes, qtdComponentes);
            ordenadoPorNome = 0;
            printf("\nComponentes ordenados por prioridade (Selection Sort):\n");
            mostrarComponentes(componentes, qtdComponentes);
            printf("Comparacoes realizadas: %d\n", comparacoesSelection);
            break;

        case 4:
            if (!ordenadoPorNome)
            {
                printf("Erro: Para realizar busca binaria, ordene primeiro por nome (opcao 1).\n");
                break;
            }
            {
                char chave[30];
                printf("Digite o nome do componente-chave para buscar: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';

                int pos = buscaBinariaPorNome(componentes, qtdComponentes, chave);
                if (pos != -1)
                {
                    printf("\nComponente-chave encontrado:\n");
                    printf("Nome: %s\n", componentes[pos].nome);
                    printf("Tipo: %s\n", componentes[pos].tipo);
                    printf("Prioridade: %d\n", componentes[pos].prioridade);
                }
                else
                {
                    printf("Componente-chave '%s' nao encontrado.\n", chave);
                }
                printf("Comparacoes realizadas na busca binaria: %d\n", comparacoesBuscaBinaria);
            }
            break;

        case 0:
            printf("Encerrando o sistema. Boa sorte na montagem da torre!\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main()
{
    menu();
    return 0;
}

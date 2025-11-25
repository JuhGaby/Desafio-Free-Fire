#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct Item para representar cada item do inventário
struct Item {
    char nome[30];      // Nome do item (ex: "AK-47", "Bandagem")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;     // Quantidade do item
};

// Definição do nó para lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// Variáveis globais para contadores de comparação
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Protótipos das funções para VETOR
void inserirItemVetor(struct Item mochila[], int *totalItens);
void removerItemVetor(struct Item mochila[], int *totalItens);
void listarItensVetor(struct Item mochila[], int totalItens);
void buscarSequencialVetor(struct Item mochila[], int totalItens);
void ordenarVetor(struct Item mochila[], int totalItens);
void buscarBinariaVetor(struct Item mochila[], int totalItens);
void menuVetor();

// Protótipos das funções para LISTA ENCADEADA
void inserirItemLista(struct No** cabeca);
void removerItemLista(struct No** cabeca);
void listarItensLista(struct No* cabeca);
void buscarSequencialLista(struct No* cabeca);
int contarItensLista(struct No* cabeca);
void liberarLista(struct No** cabeca);
void menuLista();

// Funções utilitárias
void limparBuffer();
void resetarContadores();

int main() {
    printf("=== SISTEMA DE INVENTÁRIO AVANÇADO ===\n");
    printf("Comparação: VETOR vs LISTA ENCADEADA\n\n");
    
    int opcaoPrincipal;
    
    do {
        printf("=== MENU PRINCIPAL ===\n");
        printf("1. Gerenciar mochila com VETOR\n");
        printf("2. Gerenciar mochila com LISTA ENCADEADA\n");
        printf("3. Sair do sistema\n");
        printf("Escolha uma opção (1-3): ");
        
        scanf("%d", &opcaoPrincipal);
        limparBuffer();
        
        switch (opcaoPrincipal) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 3:
                printf("\n=== ENCERRANDO SISTEMA ===\n");
                printf("Obrigado por usar o sistema de inventário avançado!\n");
                break;
            default:
                printf("❌ Opção inválida! Digite um número entre 1 e 3.\n");
        }
        
    } while (opcaoPrincipal != 3);
    
    return 0;
}

// =============================================
// FUNÇÕES UTILITÁRIAS
// =============================================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void resetarContadores() {
    comparacoesSequencial = 0;
    comparacoesBinaria = 0;
}

// =============================================
// IMPLEMENTAÇÃO COM VETOR (LISTA SEQUENCIAL)
// =============================================

void inserirItemVetor(struct Item mochila[], int *totalItens) {
    if (*totalItens >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO ITEM (VETOR) ===\n");
    
    printf("Nome do item: ");
    scanf("%29s", mochila[*totalItens].nome);
    limparBuffer();
    
    printf("Tipo do item (arma/municao/cura/ferramenta): ");
    scanf("%19s", mochila[*totalItens].tipo);
    limparBuffer();
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer();
    
    printf("\n✅ Item '%s' adicionado com sucesso!\n", mochila[*totalItens].nome);
    (*totalItens)++;
    
    listarItensVetor(mochila, *totalItens);
}

void removerItemVetor(struct Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM (VETOR) ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser removido: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    resetarContadores();
    int indice = -1;
    
    // Busca sequencial para encontrar o item
    for (int i = 0; i < *totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("Comparações realizadas: %d\n", comparacoesSequencial);
        return;
    }
    
    printf("Removendo item: %s (%s) - Quantidade: %d\n", 
           mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    printf("Comparações realizadas: %d\n", comparacoesSequencial);
    
    // Remove o item deslocando os elementos subsequentes
    for (int i = indice; i < *totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    (*totalItens)--;
    printf("✅ Item removido com sucesso!\n");
    
    listarItensVetor(mochila, *totalItens);
}

void listarItensVetor(struct Item mochila[], int totalItens) {
    printf("\n=== INVENTÁRIO DA MOCHILA (VETOR) ===\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item coletado.\n");
        return;
    }
    
    printf("Itens na mochila (%d/10):\n", totalItens);
    printf("----------------------------------------\n");
    printf("Nº | Nome               | Tipo          | Quantidade\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%-2d | %-18s | %-13s | %-10d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------------\n");
}

void buscarSequencialVetor(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA SEQUENCIAL (VETOR) ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser buscado: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    resetarContadores();
    int encontrado = 0;
    
    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Posição no inventário: %d\n", i + 1);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("Comparações realizadas: %d\n", comparacoesSequencial);
    }
}

void ordenarVetor(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para ordenar.\n");
        return;
    }
    
    printf("\n=== ORDENANDO VETOR (Bubble Sort) ===\n");
    
    resetarContadores();
    int trocas = 0;
    
    // Bubble Sort para ordenar por nome
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            comparacoesSequencial++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                // Troca os elementos
                struct Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    printf("✅ Vetor ordenado com sucesso!\n");
    printf("Comparações realizadas: %d\n", comparacoesSequencial);
    printf("Trocas realizadas: %d\n", trocas);
    
    listarItensVetor(mochila, totalItens);
}

void buscarBinariaVetor(struct Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA BINÁRIA (VETOR) ===\n");
    printf("⚠️  Aviso: A busca binária requer que o vetor esteja ordenado!\n");
    
    char nomeBusca[30];
    printf("Digite o nome do item a ser buscado: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    resetarContadores();
    
    int inicio = 0;
    int fim = totalItens - 1;
    int encontrado = 0;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Posição no inventário: %d\n", meio + 1);
            printf("Comparações realizadas: %d\n", comparacoesBinaria);
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("Comparações realizadas: %d\n", comparacoesBinaria);
    }
}

void menuVetor() {
    struct Item mochila[10];
    int totalItens = 0;
    int opcao;
    
    do {
        printf("\n=== MENU VETOR (Lista Sequencial) ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Busca sequencial por nome\n");
        printf("5. Ordenar vetor (Bubble Sort)\n");
        printf("6. Busca binária (requer ordenação)\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha uma opção (1-7): ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                inserirItemVetor(mochila, &totalItens);
                break;
            case 2:
                removerItemVetor(mochila, &totalItens);
                break;
            case 3:
                listarItensVetor(mochila, totalItens);
                break;
            case 4:
                buscarSequencialVetor(mochila, totalItens);
                break;
            case 5:
                ordenarVetor(mochila, totalItens);
                break;
            case 6:
                buscarBinariaVetor(mochila, totalItens);
                break;
            case 7:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("❌ Opção inválida! Digite um número entre 1 e 7.\n");
        }
        
    } while (opcao != 7);
}

// =============================================
// IMPLEMENTAÇÃO COM LISTA ENCADEADA
// =============================================

void inserirItemLista(struct No** cabeca) {
    // Verifica capacidade máxima (10 itens)
    if (contarItensLista(*cabeca) >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO ITEM (LISTA) ===\n");
    
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("❌ Erro de alocação de memória!\n");
        return;
    }
    
    printf("Nome do item: ");
    scanf("%29s", novoNo->dados.nome);
    limparBuffer();
    
    printf("Tipo do item (arma/municao/cura/ferramenta): ");
    scanf("%19s", novoNo->dados.tipo);
    limparBuffer();
    
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBuffer();
    
    // Insere no início da lista (mais eficiente)
    novoNo->proximo = *cabeca;
    *cabeca = novoNo;
    
    printf("\n✅ Item '%s' adicionado com sucesso!\n", novoNo->dados.nome);
    listarItensLista(*cabeca);
}

void removerItemLista(struct No** cabeca) {
    if (*cabeca == NULL) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM (LISTA) ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser removido: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    resetarContadores();
    struct No* atual = *cabeca;
    struct No* anterior = NULL;
    int encontrado = 0;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            encontrado = 1;
            
            printf("Removendo item: %s (%s) - Quantidade: %d\n", 
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            
            if (anterior == NULL) {
                // Remove o primeiro nó
                *cabeca = atual->proximo;
            } else {
                // Remove nó do meio ou final
                anterior->proximo = atual->proximo;
            }
            
            free(atual);
            printf("✅ Item removido com sucesso!\n");
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("Comparações realizadas: %d\n", comparacoesSequencial);
    } else {
        listarItensLista(*cabeca);
    }
}

void listarItensLista(struct No* cabeca) {
    printf("\n=== INVENTÁRIO DA MOCHILA (LISTA ENCADEADA) ===\n");
    
    if (cabeca == NULL) {
        printf("Mochila vazia! Nenhum item coletado.\n");
        return;
    }
    
    int total = contarItensLista(cabeca);
    printf("Itens na mochila (%d/10):\n", total);
    printf("----------------------------------------\n");
    printf("Nº | Nome               | Tipo          | Quantidade\n");
    printf("----------------------------------------\n");
    
    struct No* atual = cabeca;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%-2d | %-18s | %-13s | %-10d\n", 
               contador, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }
    printf("----------------------------------------\n");
}

void buscarSequencialLista(struct No* cabeca) {
    if (cabeca == NULL) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA SEQUENCIAL (LISTA) ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser buscado: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    resetarContadores();
    struct No* atual = cabeca;
    int posicao = 1;
    int encontrado = 0;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Posição na lista: %d\n", posicao);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
        posicao++;
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("Comparações realizadas: %d\n", comparacoesSequencial);
    }
}

int contarItensLista(struct No* cabeca) {
    int count = 0;
    struct No* atual = cabeca;
    
    while (atual != NULL) {
        count++;
        atual = atual->proximo;
    }
    
    return count;
}

void liberarLista(struct No** cabeca) {
    struct No* atual = *cabeca;
    struct No* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    *cabeca = NULL;
}

void menuLista() {
    struct No* cabeca = NULL;
    int opcao;
    
    do {
        printf("\n=== MENU LISTA ENCADEADA ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Busca sequencial por nome\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opção (1-5): ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                inserirItemLista(&cabeca);
                break;
            case 2:
                removerItemLista(&cabeca);
                break;
            case 3:
                listarItensLista(cabeca);
                break;
            case 4:
                buscarSequencialLista(cabeca);
                break;
            case 5:
                printf("Retornando ao menu principal...\n");
                liberarLista(&cabeca); // Libera a memória alocada
                break;
            default:
                printf("❌ Opção inválida! Digite um número entre 1 e 5.\n");
        }
        
    } while (opcao != 5);
}
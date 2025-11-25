#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item para representar cada item do inventário
struct Item {
    char nome[30];      // Nome do item (ex: "AK-47", "Bandagem")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;     // Quantidade do item
};

// Variáveis globais
struct Item mochila[10]; // Vetor para armazenar até 10 itens
int totalItens = 0;     // Contador de itens na mochila

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void menuPrincipal();
void limparBuffer();

int main() {
    printf("=== SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo ao sistema de gerenciamento de inventário!\n\n");
    
    menuPrincipal();
    return 0;
}

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar um novo item na mochila
void inserirItem() {
    // Verifica se a mochila está cheia
    if (totalItens >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO ITEM ===\n");
    
    // Solicita os dados do item
    printf("Nome do item: ");
    scanf("%29s", mochila[totalItens].nome);
    limparBuffer();
    
    printf("Tipo do item (arma/municao/cura/ferramenta): ");
    scanf("%19s", mochila[totalItens].tipo);
    limparBuffer();
    
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();
    
    printf("\n✅ Item '%s' adicionado com sucesso!\n", mochila[totalItens].nome);
    totalItens++;
    
    // Lista todos os itens após a inserção
    listarItens();
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser removido: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    // Busca sequencial pelo item
    int indice = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        return;
    }
    
    // Exibe o item que será removido
    printf("Removendo item: %s (%s) - Quantidade: %d\n", 
           mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    
    // Remove o item deslocando os elementos subsequentes
    for (int i = indice; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    totalItens--;
    printf("✅ Item removido com sucesso!\n");
    
    // Lista todos os itens após a remoção
    listarItens();
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n=== INVENTÁRIO DA MOCHILA ===\n");
    
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

// Função de busca sequencial por um item pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCAR ITEM ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser buscado: ");
    scanf("%29s", nomeBusca);
    limparBuffer();
    
    // Busca sequencial pelo item
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Posição no inventário: %d\n", i + 1);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// Função para exibir o menu principal e processar as opções
void menuPrincipal() {
    int opcao;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item por nome\n");
        printf("5. Sair do sistema\n");
        printf("Escolha uma opção (1-5): ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\n=== ENCERRANDO SISTEMA ===\n");
                printf("Obrigado por usar o sistema de inventário!\n");
                printf("Itens salvos na mochila: %d\n", totalItens);
                break;
            default:
                printf("❌ Opção inválida! Digite um número entre 1 e 5.\n");
        }
        
    } while (opcao != 5);
}
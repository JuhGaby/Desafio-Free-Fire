#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Componente para representar cada peça da torre
struct Componente {
    char nome[30];      // Nome do componente (ex: "chip central", "propulsor")
    char tipo[20];      // Tipo do componente (ex: "controle", "suporte", "propulsão")
    int prioridade;     // Prioridade de 1 a 10 (1 = mais importante)
};

// Variáveis globais para medição de desempenho
int comparacoes = 0;
int trocas = 0;
clock_t inicio, fim;

// Protótipos das funções
void cadastrarComponentes(struct Componente componentes[], int *total);
void bubbleSortNome(struct Componente componentes[], int total);
void insertionSortTipo(struct Componente componentes[], int total);
void selectionSortPrioridade(struct Componente componentes[], int total);
void buscaBinariaPorNome(struct Componente componentes[], int total, char nomeBusca[]);
void mostrarComponentes(struct Componente componentes[], int total);
void medirDesempenho(void (*algoritmo)(struct Componente[], int), struct Componente componentes[], int total, char nomeAlgoritmo[]);
void resetarContadores();
void limparBuffer();
void menuPrincipal();

int main() {
    printf("=== SISTEMA DE MONTAGEM DA TORRE DE RESGATE ===\n");
    printf("🚀 Fase Final: Escape da Ilha 🚀\n\n");
    printf("A zona segura está se fechando! Monte sua torre rapidamente!\n\n");
    
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    struct Componente componentes[20];
    int totalComponentes = 0;
    int opcao;
    int ordenadoPorNome = 0; // Flag para verificar se está ordenado por nome
    
    do {
        printf("\n=== MENU PRINCIPAL - TORRE DE RESGATE ===\n");
        printf("1. Cadastrar componentes (%d/20)\n", totalComponentes);
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar componentes\n");
        printf("4. Buscar componente-chave\n");
        printf("5. Montar torre (exibir ordem final)\n");
        printf("6. Sair do sistema\n");
        printf("Escolha uma opção (1-6): ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &totalComponentes);
                ordenadoPorNome = 0; // Reset da flag ao adicionar novos componentes
                break;
            case 2:
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 3:
                if (totalComponentes == 0) {
                    printf("\n❌ Nenhum componente cadastrado!\n");
                    break;
                }
                printf("\n=== ALGORITMOS DE ORDENAÇÃO ===\n");
                printf("1. Bubble Sort - Ordenar por NOME\n");
                printf("2. Insertion Sort - Ordenar por TIPO\n");
                printf("3. Selection Sort - Ordenar por PRIORIDADE\n");
                printf("Escolha o algoritmo (1-3): ");
                
                int opcaoOrdenacao;
                scanf("%d", &opcaoOrdenacao);
                limparBuffer();
                
                switch (opcaoOrdenacao) {
                    case 1:
                        medirDesempenho(bubbleSortNome, componentes, totalComponentes, "Bubble Sort (Nome)");
                        ordenadoPorNome = 1;
                        break;
                    case 2:
                        medirDesempenho(insertionSortTipo, componentes, totalComponentes, "Insertion Sort (Tipo)");
                        ordenadoPorNome = 0;
                        break;
                    case 3:
                        medirDesempenho(selectionSortPrioridade, componentes, totalComponentes, "Selection Sort (Prioridade)");
                        ordenadoPorNome = 0;
                        break;
                    default:
                        printf("❌ Opção inválida!\n");
                }
                break;
            case 4:
                if (totalComponentes == 0) {
                    printf("\n❌ Nenhum componente cadastrado!\n");
                    break;
                }
                if (!ordenadoPorNome) {
                    printf("\n⚠️  Aviso: Para busca binária, os componentes devem estar ordenados por NOME!\n");
                    printf("Deseja ordenar por nome primeiro? (s/n): ");
                    char resposta;
                    scanf("%c", &resposta);
                    limparBuffer();
                    if (resposta == 's' || resposta == 'S') {
                        medirDesempenho(bubbleSortNome, componentes, totalComponentes, "Bubble Sort (Nome)");
                        ordenadoPorNome = 1;
                    } else {
                        break;
                    }
                }
                
                char nomeBusca[30];
                printf("\n🔍 BUSCA DO COMPONENTE-CHAVE\n");
                printf("Digite o nome do componente a ser buscado: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove quebra de linha
                
                buscaBinariaPorNome(componentes, totalComponentes, nomeBusca);
                break;
            case 5:
                if (totalComponentes == 0) {
                    printf("\n❌ Nenhum componente cadastrado para montagem!\n");
                    break;
                }
                printf("\n=== ORDEM FINAL DE MONTAGEM DA TORRE ===\n");
                printf("🧱 Iniciando montagem da torre de resgate...\n\n");
                mostrarComponentes(componentes, totalComponentes);
                printf("\n✅ Torre montada com sucesso! Preparando para decolagem...\n");
                break;
            case 6:
                printf("\n=== ENCERRANDO SISTEMA ===\n");
                printf("Obrigado por usar o sistema de montagem da torre!\n");
                printf("Componentes cadastrados: %d\n", totalComponentes);
                break;
            default:
                printf("❌ Opção inválida! Digite um número entre 1 e 6.\n");
        }
        
    } while (opcao != 6);
}

void cadastrarComponentes(struct Componente componentes[], int *total) {
    if (*total >= 20) {
        printf("\n❌ Capacidade máxima atingida! (20 componentes)\n");
        return;
    }
    
    printf("\n=== CADASTRO DE COMPONENTES ===\n");
    printf("Componentes cadastrados: %d/20\n", *total);
    
    int quantidade;
    printf("Quantos componentes deseja cadastrar? ");
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (*total + quantidade > 20) {
        printf("❌ Não há espaço para %d componentes. Espaço disponível: %d\n", 
               quantidade, 20 - *total);
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Componente %d ---\n", *total + 1);
        
        printf("Nome: ");
        fgets(componentes[*total].nome, 30, stdin);
        componentes[*total].nome[strcspn(componentes[*total].nome, "\n")] = 0;
        
        printf("Tipo (controle/suporte/propulsao/energia): ");
        fgets(componentes[*total].tipo, 20, stdin);
        componentes[*total].tipo[strcspn(componentes[*total].tipo, "\n")] = 0;
        
        printf("Prioridade (1-10, onde 1 é mais importante): ");
        scanf("%d", &componentes[*total].prioridade);
        limparBuffer();
        
        // Validação da prioridade
        if (componentes[*total].prioridade < 1 || componentes[*total].prioridade > 10) {
            printf("⚠️  Prioridade ajustada para valor padrão 5\n");
            componentes[*total].prioridade = 5;
        }
        
        (*total)++;
        printf("✅ Componente '%s' cadastrado com sucesso!\n", componentes[*total - 1].nome);
    }
    
    printf("\n🎯 Total de componentes cadastrados: %d/20\n", *total);
}

void bubbleSortNome(struct Componente componentes[], int total) {
    resetarContadores();
    
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os elementos
                struct Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocas++;
            }
        }
    }
}

void insertionSortTipo(struct Componente componentes[], int total) {
    resetarContadores();
    
    for (int i = 1; i < total; i++) {
        struct Componente chave = componentes[i];
        int j = i - 1;
        
        comparacoes++;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            componentes[j + 1] = componentes[j];
            j = j - 1;
            trocas++;
            comparacoes++;
        }
        componentes[j + 1] = chave;
    }
}

void selectionSortPrioridade(struct Componente componentes[], int total) {
    resetarContadores();
    
    for (int i = 0; i < total - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            // Troca os elementos
            struct Componente temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
            trocas++;
        }
    }
}

void buscaBinariaPorNome(struct Componente componentes[], int total, char nomeBusca[]) {
    resetarContadores();
    inicio = clock();
    
    int esquerda = 0;
    int direita = total - 1;
    int encontrado = 0;
    int posicao = -1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        
        int resultado = strcmp(componentes[meio].nome, nomeBusca);
        
        if (resultado == 0) {
            encontrado = 1;
            posicao = meio;
            break;
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n=== RESULTADO DA BUSCA BINÁRIA ===\n");
    if (encontrado) {
        printf("🎯 COMPONENTE-CHAVE ENCONTRADO! 🎯\n");
        printf("Nome: %s\n", componentes[posicao].nome);
        printf("Tipo: %s\n", componentes[posicao].tipo);
        printf("Prioridade: %d\n", componentes[posicao].prioridade);
        printf("Posição na lista: %d\n", posicao + 1);
        printf("\n🚀 Torre destravada! Iniciando sequência de escape...\n");
    } else {
        printf("❌ Componente '%s' não encontrado!\n", nomeBusca);
        printf("Verifique se o nome está correto e se a lista está ordenada por nome.\n");
    }
    
    printf("\n📊 Estatísticas da busca:\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);
}

void mostrarComponentes(struct Componente componentes[], int total) {
    if (total == 0) {
        printf("\n❌ Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n=== LISTA DE COMPONENTES (%d itens) ===\n", total);
    printf("------------------------------------------------------------\n");
    printf("Nº | Nome                     | Tipo              | Prioridade\n");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        printf("%-2d | %-24s | %-16s | %-10d\n", 
               i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("------------------------------------------------------------\n");
    
    // Calcular estatísticas
    int prioridadeMax = componentes[0].prioridade;
    int prioridadeMin = componentes[0].prioridade;
    float prioridadeMedia = 0;
    
    for (int i = 0; i < total; i++) {
        if (componentes[i].prioridade > prioridadeMax) prioridadeMax = componentes[i].prioridade;
        if (componentes[i].prioridade < prioridadeMin) prioridadeMin = componentes[i].prioridade;
        prioridadeMedia += componentes[i].prioridade;
    }
    prioridadeMedia /= total;
    
    printf("\n📊 Estatísticas:\n");
    printf("Prioridade máxima: %d\n", prioridadeMax);
    printf("Prioridade mínima: %d\n", prioridadeMin);
    printf("Prioridade média:  %.2f\n", prioridadeMedia);
}

void medirDesempenho(void (*algoritmo)(struct Componente[], int), struct Componente componentes[], int total, char nomeAlgoritmo[]) {
    printf("\n⚡ Executando %s...\n", nomeAlgoritmo);
    
    // Faz uma cópia do array para não modificar o original durante a medição
    struct Componente copia[20];
    memcpy(copia, componentes, sizeof(struct Componente) * total);
    
    resetarContadores();
    inicio = clock();
    
    // Executa o algoritmo
    algoritmo(copia, total);
    
    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    // Atualiza o array original com a versão ordenada
    memcpy(componentes, copia, sizeof(struct Componente) * total);
    
    printf("✅ Ordenação concluída!\n");
    printf("\n📊 Relatório de Desempenho - %s:\n", nomeAlgoritmo);
    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Número de comparações: %d\n", comparacoes);
    printf("Número de trocas: %d\n", trocas);
    printf("Eficiência: %.2f comparações por elemento\n", (float)comparacoes / total);
    
    // Classificação da eficiência
    if (tempo < 0.001) printf("🏆 Velocidade: Excelente!\n");
    else if (tempo < 0.01) printf("🚀 Velocidade: Muito Boa!\n");
    else if (tempo < 0.1) printf("👍 Velocidade: Boa\n");
    else printf("🐌 Velocidade: Lenta\n");
    
    printf("\n");
    mostrarComponentes(componentes, total);
}

void resetarContadores() {
    comparacoes = 0;
    trocas = 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
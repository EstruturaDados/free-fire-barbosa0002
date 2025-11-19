/*
 * Sistema de Torre de Resgate - Free Fire
 * Módulo avançado de organização de componentes para fuga final
 * Implementa ordenação e busca otimizada com análise de desempenho
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definição da capacidade máxima de componentes
#define MAX_COMPONENTES 20

/*
 * Struct Componente
 * Representa cada peça necessária para a montagem da torre
 * Campos:
 *   - nome: identificador do componente (até 30 caracteres)
 *   - tipo: categoria (controle, suporte, propulsão, etc.)
 *   - prioridade: nível de importância (1 a 10)
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais
Componente torre[MAX_COMPONENTES];  // Vetor de componentes
int totalComponentes = 0;            // Contador de componentes cadastrados
long comparacoes = 0;                // Contador de comparações

/*
 * Função: limparBuffer
 * Limpa o buffer do teclado para evitar leituras indesejadas
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Função: cadastrarComponente
 * Permite o cadastro de um novo componente na torre
 */
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n[AVISO] Capacidade máxima atingida! (%d componentes)\n", MAX_COMPONENTES);
        return;
    }
    
    Componente novo;
    
    printf("\n=== CADASTRAR COMPONENTE ===\n");
    
    // Leitura do nome
    printf("Nome do componente: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; // Remove newline
    
    // Leitura do tipo
    printf("Tipo (controle/suporte/propulsao/estrutura): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;
    
    // Leitura da prioridade
    printf("Prioridade (1-10): ");
    scanf("%d", &novo.prioridade);
    limparBuffer();
    
    // Validação da prioridade
    if (novo.prioridade < 1 || novo.prioridade > 10) {
        printf("\n[ERRO] Prioridade deve estar entre 1 e 10!\n");
        return;
    }
    
    // Adiciona o componente
    torre[totalComponentes] = novo;
    totalComponentes++;
    
    printf("\n[SUCESSO] Componente '%s' cadastrado! (%d/%d)\n", 
           novo.nome, totalComponentes, MAX_COMPONENTES);
}

/*
 * Função: listarComponentes
 * Exibe todos os componentes cadastrados
 */
void listarComponentes() {
    printf("\n========================================\n");
    printf("      COMPONENTES DA TORRE DE FUGA\n");
    printf("========================================\n");
    
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
    } else {
        printf("Total: %d/%d componentes\n\n", totalComponentes, MAX_COMPONENTES);
        
        for (int i = 0; i < totalComponentes; i++) {
            printf("[%02d] %-25s | Tipo: %-12s | Prioridade: %d\n",
                   i + 1, torre[i].nome, torre[i].tipo, torre[i].prioridade);
        }
    }
    printf("========================================\n");
}

/*
 * Função: bubbleSort
 * Ordena os componentes por NOME usando Bubble Sort
 * Complexidade: O(n²)
 */
void bubbleSort() {
    comparacoes = 0;
    clock_t inicio = clock();
    
    printf("\n[EXECUTANDO] Bubble Sort por NOME...\n");
    
    // Algoritmo Bubble Sort
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            // Compara strings lexicograficamente
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                // Troca os elementos
                Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n[CONCLUÍDO] Bubble Sort\n");
    printf("├─ Comparações: %ld\n", comparacoes);
    printf("└─ Tempo: %.4f ms\n", tempo);
}

/*
 * Função: insertionSort
 * Ordena os componentes por TIPO usando Insertion Sort
 * Complexidade: O(n²) no pior caso, O(n) no melhor caso
 */
void insertionSort() {
    comparacoes = 0;
    clock_t inicio = clock();
    
    printf("\n[EXECUTANDO] Insertion Sort por TIPO...\n");
    
    // Algoritmo Insertion Sort
    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = torre[i];
        int j = i - 1;
        
        // Move elementos maiores para frente
        while (j >= 0) {
            comparacoes++;
            if (strcmp(torre[j].tipo, chave.tipo) > 0) {
                torre[j + 1] = torre[j];
                j--;
            } else {
                break;
            }
        }
        torre[j + 1] = chave;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n[CONCLUÍDO] Insertion Sort\n");
    printf("├─ Comparações: %ld\n", comparacoes);
    printf("└─ Tempo: %.4f ms\n", tempo);
}

/*
 * Função: selectionSort
 * Ordena os componentes por PRIORIDADE usando Selection Sort
 * Complexidade: O(n²)
 */
void selectionSort() {
    comparacoes = 0;
    clock_t inicio = clock();
    
    printf("\n[EXECUTANDO] Selection Sort por PRIORIDADE...\n");
    
    // Algoritmo Selection Sort (ordem decrescente de prioridade)
    for (int i = 0; i < totalComponentes - 1; i++) {
        int maxIdx = i;
        
        // Encontra o elemento com maior prioridade
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (torre[j].prioridade > torre[maxIdx].prioridade) {
                maxIdx = j;
            }
        }
        
        // Troca se necessário
        if (maxIdx != i) {
            Componente temp = torre[i];
            torre[i] = torre[maxIdx];
            torre[maxIdx] = temp;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n[CONCLUÍDO] Selection Sort\n");
    printf("├─ Comparações: %ld\n", comparacoes);
    printf("└─ Tempo: %.4f ms\n", tempo);
}

/*
 * Função: buscaBinaria
 * Realiza busca binária por nome (requer ordenação prévia)
 * Complexidade: O(log n)
 */
void buscaBinaria() {
    if (totalComponentes == 0) {
        printf("\n[AVISO] Nenhum componente cadastrado!\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\n=== BUSCA BINÁRIA ===\n");
    printf("ATENÇÃO: A lista deve estar ordenada por NOME!\n");
    printf("Nome do componente-chave: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    comparacoes = 0;
    clock_t inicio = clock();
    
    // Algoritmo de busca binária
    int esquerda = 0;
    int direita = totalComponentes - 1;
    int encontrado = -1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        
        int cmp = strcmp(torre[meio].nome, nomeBusca);
        
        if (cmp == 0) {
            encontrado = meio;
            break;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    if (encontrado != -1) {
        printf("\n[COMPONENTE ENCONTRADO]\n");
        printf("╔════════════════════════════════════════╗\n");
        printf("║  COMPONENTE-CHAVE LOCALIZADO!          ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║ Nome: %-32s ║\n", torre[encontrado].nome);
        printf("║ Tipo: %-32s ║\n", torre[encontrado].tipo);
        printf("║ Prioridade: %-26d ║\n", torre[encontrado].prioridade);
        printf("║ Posição: %-29d ║\n", encontrado + 1);
        printf("╠════════════════════════════════════════╣\n");
        printf("║ Comparações: %-25ld ║\n", comparacoes);
        printf("║ Tempo: %.4f ms                       ║\n", tempo);
        printf("╚════════════════════════════════════════╝\n");
        printf("\n🚀 Torre de fuga ATIVADA! Prepare-se para a extração!\n");
    } else {
        printf("\n[ERRO] Componente '%s' não encontrado!\n", nomeBusca);
        printf("├─ Comparações: %ld\n", comparacoes);
        printf("└─ Tempo: %.4f ms\n", tempo);
        printf("\n⚠️  Verifique se a lista está ordenada por NOME!\n");
    }
}

/*
 * Função: menuOrdenacao
 * Exibe menu de opções de ordenação
 */
void menuOrdenacao() {
    int opcao;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║     ESTRATÉGIAS DE ORGANIZAÇÃO         ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ 1. Bubble Sort (por Nome)              ║\n");
    printf("║ 2. Insertion Sort (por Tipo)           ║\n");
    printf("║ 3. Selection Sort (por Prioridade)     ║\n");
    printf("║ 4. Voltar ao menu principal            ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("Escolha a estratégia: ");
    scanf("%d", &opcao);
    limparBuffer();
    
    switch(opcao) {
        case 1:
            bubbleSort();
            listarComponentes();
            break;
        case 2:
            insertionSort();
            listarComponentes();
            break;
        case 3:
            selectionSort();
            listarComponentes();
            break;
        case 4:
            return;
        default:
            printf("\n[ERRO] Opção inválida!\n");
    }
}

/*
 * Função: preencherDadosTeste
 * Preenche automaticamente com componentes de exemplo
 */
void preencherDadosTeste() {
    if (totalComponentes > 0) {
        printf("\n[AVISO] Já existem componentes cadastrados!\n");
        printf("Deseja limpar e preencher com dados de teste? (s/n): ");
        char resp;
        scanf("%c", &resp);
        limparBuffer();
        if (resp != 's' && resp != 'S') return;
        totalComponentes = 0;
    }
    
    // Componentes de exemplo
    strcpy(torre[0].nome, "Chip Central");
    strcpy(torre[0].tipo, "controle");
    torre[0].prioridade = 10;
    
    strcpy(torre[1].nome, "Motor Propulsor");
    strcpy(torre[1].tipo, "propulsao");
    torre[1].prioridade = 9;
    
    strcpy(torre[2].nome, "Antena Satelite");
    strcpy(torre[2].tipo, "controle");
    torre[2].prioridade = 8;
    
    strcpy(torre[3].nome, "Base Estrutural");
    strcpy(torre[3].tipo, "estrutura");
    torre[3].prioridade = 7;
    
    strcpy(torre[4].nome, "Painel Solar");
    strcpy(torre[4].tipo, "suporte");
    torre[4].prioridade = 6;
    
    strcpy(torre[5].nome, "Sistema Navegacao");
    strcpy(torre[5].tipo, "controle");
    torre[5].prioridade = 9;
    
    strcpy(torre[6].nome, "Tanque Combustivel");
    strcpy(torre[6].tipo, "propulsao");
    torre[6].prioridade = 8;
    
    strcpy(torre[7].nome, "Escudo Termico");
    strcpy(torre[7].tipo, "estrutura");
    torre[7].prioridade = 7;
    
    totalComponentes = 8;
    
    printf("\n[SUCESSO] %d componentes de teste carregados!\n", totalComponentes);
}

/*
 * Função: exibirMenu
 * Mostra o menu principal do sistema
 */
void exibirMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║   TORRE DE RESGATE - MISSÃO FINAL      ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ 1. Cadastrar componente                ║\n");
    printf("║ 2. Listar componentes                  ║\n");
    printf("║ 3. Ordenar componentes                 ║\n");
    printf("║ 4. Busca binária (componente-chave)    ║\n");
    printf("║ 5. Carregar dados de teste             ║\n");
    printf("║ 6. Sair da missão                      ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

/*
 * Função: main
 * Ponto de entrada do programa
 */
int main() {
    int opcao;
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║     FREE FIRE - TORRE DE RESGATE       ║\n");
    printf("║                                        ║\n");
    printf("║  A safe zone está se fechando!         ║\n");
    printf("║  Monte a torre de fuga estrategicamente║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    // Loop principal
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                listarComponentes();
                break;
            case 3:
                if (totalComponentes == 0) {
                    printf("\n[AVISO] Nenhum componente cadastrado!\n");
                } else {
                    menuOrdenacao();
                }
                break;
            case 4:
                buscaBinaria();
                break;
            case 5:
                preencherDadosTeste();
                listarComponentes();
                break;
            case 6:
                printf("\n╔════════════════════════════════════════╗\n");
                printf("║  MISSÃO ENCERRADA!                     ║\n");
                printf("║  Boa sorte na próxima batalha! 🎮      ║\n");
                printf("╚════════════════════════════════════════╝\n\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida! Tente novamente.\n");
        }
        
    } while(opcao != 6);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("\n========================================\n");
    printf("DICIONÁRIO COM HASH\n");
    printf("\n========================================\n");
    printf("1. Adicionar palavra e significado\n");
    printf("2. Buscar palavra\n");
    printf("3. Remover palavra\n");
    printf("4. Listar todas as palavras\n");
    printf("5. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opção: ");
}

int main() {
    int tamanho_tabela = 100;
    TabelaHash *dicionario = criarTabela(tamanho_tabela);

    if (dicionario == NULL) {
        printf("Erro: não foi possível criar o dicionário.\n");
        return 1;
    }

    int opcao;
    char palavra[100];
    char significado[256];

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            limpar_buffer();
            opcao = 0;
            continue;
        }

        limpar_buffer(); // Limpa o teclado

        switch (opcao) {
            case 1:
                printf("Digite a palavra: ");
                palavra[0] = '\0'; // limpa o buffer de palavra
                scanf("%99[^\n]", palavra);
                limpar_buffer();

                printf("Digite o significado: ");
                significado[0] = '\0'; // limpa o buffer do significado
                scanf("%99[^\n]", significado);
                limpar_buffer();

                insPalavra(dicionario, palavra, significado);
                printf("'%s' adicionada com sucesso!\n", palavra);
                break;
                
            case 2:
                printf("DIgite a palavra a ser buscada: ");
                scanf("%99[^\n]", palavra);
                limpar_buffer();

                EntradaHash *entrada = buscarPalavra(dicionario, palavra);
                if (entrada != NULL) {
                    printf("\nPalavra encontrada: %s\n", entrada -> palavra);
                    Significado *sig = entrada -> significados;
                    int count = 1;

                    while(sig != NULL) {
                        printf("Significado %d: %s\n", count, sig -> definicao);
                        sig = sig -> proximo;
                        count++;
                    }
                } else {
                    printf("Palavra '%s' não encontrada.\n", palavra);
                } break;

            case 3:
                printf("Digite a palavra a ser removida: ");
                scanf("%99[^\n]", palavra);
                limpar_buffer();
                removerPalavra(dicionario, palavra);
                break;

            case 4:
                listar(dicionario);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 5);

    return 0;
}
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Função de Hash
static unsigned long funcaoHash(const char *str, int tam_tabela) {
    
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % tam_tabela;
}

TabelaHash *criarTabela(int tamanho) {

    // Alocação de memória para a principal estrutura
    TabelaHash *tabelaHash = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (tabelaHash == NULL) {
        perror("Erro ao alocar Tabela!");
        return NULL;
    }

    tabelaHash -> tamanho = tamanho;

    // Alocação de memória para o array de ponteiros
    tabelaHash -> tabela = (EntradaHash**) malloc(sizeof(EntradaHash*) * tamanho);
    if (tabelaHash -> tabela == NULL) {
        perror("Erro de alocar array!");
        free(tabelaHash); // LIbera memória alocada
        return NULL;
    }

    // Inicializa todos os buckets como vazios
    for (int i = 0; i < tamanho; i++) {
        tabelaHash -> tabela[i] = NULL;
    }

    return tabelaHash;
}
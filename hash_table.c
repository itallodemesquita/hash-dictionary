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

void insPalavra(TabelaHash *tabela, const char *palavra, const char *significado) {
    if (tabela == NULL) return;

    // Cálculo do índice com função hash
    unsigned int indice = funcaoHash(palavra, tabela -> tamanho);

    // Verifica se a palavra já existe no bucket
    EntradaHash *atual = tabela -> tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual -> palavra, palavra) == 0) {
            // Se a palavra já existe, adicionamos um novo significado
            Significado *novoSignificado = (Significado*) malloc(sizeof(Significado));
            if(novoSignificado == NULL) return;

            novoSignificado -> definicao = strdup(significado);
            novoSignificado -> proximo = atual -> significados;
            atual -> significados = novoSignificado;
            return;
        }

        atual = atual -> proximo;
    }

    // Cria nova entrada (se a palavra não for encontrada)
    EntradaHash *novaEntrada = (EntradaHash*) malloc(sizeof(EntradaHash));
    if(novaEntrada == NULL) return;

    novaEntrada -> palavra = strdup(palavra);

    // Cria o primeiro nó da lista de significados
    novaEntrada -> significados == (Significado*) malloc(sizeof(Significado));
    if(novaEntrada -> significados == NULL) {
        free(novaEntrada -> palavra);
        free(novaEntrada);
        return;
    }
    novaEntrada -> significados -> definicao = strdup(significado);
    novaEntrada -> significados -> proximo = NULL;

    // Insere a nova entrada no início da lista
    novaEntrada -> proximo = tabela -> tabela[indice];
    tabela -> tabela[indice];
}
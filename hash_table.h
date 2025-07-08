#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

// Lista ligada de significados
typedef struct Significado {
    char *definicao;
    struct Significado *proximo;
} Significado;

// Entrada na tabela hash
typedef struct EntradaHash {
    char *palavra;
    Significado *significados; // Aponta pro início da lista
    struct EntradaHash *proximo;
} EntradaHash;

// Estrutura para a hash
typedef struct TabelaHash {
    int tamanho;
    EntradaHash **tabela; // Array de ponteiros para EntradaHash
} TabelaHash;


TabelaHash *criarTabela(int tamanho);

void insPalavra(TabelaHash *tabela, const char *palavra, const char *significado);

EntradaHash *buscarPalavra(TabelaHash *tabela, const char *palavra);

void removerPalavra(TabelaHash *tabela, const char *palavra);

void listar(TabelaHash *tabela);

#endif
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
    struct EntradaHash *próximo;
} EntradaHash;

// Estrutura para a hash
typedef struct HashTable {
    int tamanho;
    EntradaHash **tabela; // Array de ponteiros para EntradaHash
} TabelaHash;

// Função de Hash
unsigned long funcaoHash(const char *str, int tam_tabela) {
    
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % tam_tabela;
}
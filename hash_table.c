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

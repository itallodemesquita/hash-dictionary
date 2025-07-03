#include <stdio.h>

// Lista ligada de significados
typedef struct Significado {
    char *definicao;
    struct Significado *proximo;
} Significado;
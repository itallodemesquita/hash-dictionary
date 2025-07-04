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
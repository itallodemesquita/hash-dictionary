#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define MAX_LINES 1024 // Tamanho máximo de linhas aceito pelo programa

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
    novaEntrada -> significados = (Significado*) malloc(sizeof(Significado));
    if(novaEntrada -> significados == NULL) {
        free(novaEntrada -> palavra);
        free(novaEntrada);
        return;
    }
    novaEntrada -> significados -> definicao = strdup(significado);
    novaEntrada -> significados -> proximo = NULL;

    // Insere a nova entrada no início da lista
    novaEntrada -> proximo = tabela -> tabela[indice];
    tabela -> tabela[indice] = novaEntrada;
}

EntradaHash *buscarPalavra(TabelaHash *tabela, const char *palavra) {
    if (tabela == NULL) return NULL;

    // Calcula o índice da palavra
    unsigned int indice = funcaoHash(palavra, tabela -> tamanho);

    // Percorre a lista ligada
    EntradaHash *atual = tabela -> tabela[indice];
    while (atual != NULL) {
        // Compara a palavra atual com a buscada
        if (strcmp(atual -> palavra, palavra) == 0) {
            return atual;
        }
        atual = atual -> proximo;
    }

    // Caso a palavra não seja encontrada
    return NULL;
}

void removerPalavra(TabelaHash *tabela, const char *palavra) {
    if (tabela == NULL) return;

    unsigned int indice = funcaoHash(palavra, tabela -> tamanho);

    EntradaHash *atual = tabela -> tabela[indice];
    EntradaHash *anterior = NULL;

    // Eccontra a palavra na lista
    while (atual != NULL && strcmp(atual -> palavra, palavra) != 0) {
        anterior = atual;
        atual = atual -> proximo;
    }

    // Se for vazio, a palavra não foi encontrada
    if (atual == NULL) {
        printf("Palavra '%s' não foi encontrada para remoção.\n", palavra);
        return;
    }

    // Liga os elementos da lista novamente
    if (anterior == NULL) {
        // Remove o primeiro nó
        tabela -> tabela[indice] = atual -> proximo;
    } else {
        // O nó está no meio ou no fim da lista
        anterior -> proximo = atual -> proximo;
    }

    // Libera memória para a entrada
    Significado *sigAtual = atual -> significados;
    while (sigAtual != NULL) {
        Significado *proximoSig = sigAtual -> proximo;
        free(sigAtual -> definicao);
        free(sigAtual);
        sigAtual = proximoSig;
    }

    // LIbera a palavra e o nó da entrada principal
    free(atual -> palavra);
    free(atual);

    printf("Palavra '%s' removida com sucesso!\n", palavra);
}

void listar(TabelaHash *tabela) {
    if (tabela == NULL) return;

    printf("\n-- Lista de palavras no dicionário --\n");
    int cont = 0;

    // Percorre cada bucket da tabela hash
    for (int i = 0; i < tabela -> tamanho; i++) {
        EntradaHash *entrada = tabela -> tabela[i];

        // Se não estiver vazio, percorre a lista ligada
        while (entrada != NULL) {
            cont++;
            printf("\n%d. Palavra: %s\n", cont, entrada -> palavra);

            // Percorre e imprime todos os significados da palavra
            Significado *sig = entrada -> significados;
            int sig_count = 1;
            while (sig != NULL) {
                printf("Significado %d: %s\n", sig_count, sig -> definicao);
                sig = sig -> proximo;
                sig_count++;
            }

            entrada = entrada -> proximo;
        }
    }

    if (cont == 0) {
        printf("\nO dicionário está vazio.\n");
    }

    printf("\n-- Fim da lista -- \n");
}

void carregarDicionario(TabelaHash *tabela, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); // Arquivo em modo leitura
    if (arquivo == NULL) {
        // se não existe...
        printf("Arquivo nao encontrado.");
        return;
    }

    char linha[MAX_LINES];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Se houver, remove '\n' do final
        linha[strcspn(linha, "\n")] = 0;

        // Pega tudo antes de : (a palavra)
        char *palavra = strtok(linha, ":");
        if (palavra == NULL) continue; // Significa que o dicionario esta mal formatado

        // Pega a string com o(s) significado(s)
        char *todos_sigs = strtok(NULL, "");
        if (todos_sigs == NULL) continue; // Palavra sem significado

        // Divide os significados por "|"
        char *significado = strtok(todos_sigs, "|");
        while (significado != NULL) {
            // Insere as palavras e significados na tabela
            insPalavra(tabela, palavra, significado);
            significado = strtok(NULL, "|");
        }
    }

    fclose(arquivo);
    printf("Dicionario carregado com sucesso!\n");

}
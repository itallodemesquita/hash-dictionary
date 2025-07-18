# Documentação de Teste de Software: Projeto de Dicionário com Tabela Hash

**Data da documentação:** 18 de julho de 2025

## Introdução

Esta seção busca detalhar o processo de testes funcionais realizados para o software "Dicionário com Tabela Hash". O objetivo dos testes foi verificar a corretude, robustez e funcionalidade do software de acordo com os requisitos do projeto, assim garantindo um código de boa qualidade. Foi adotada a estratégia de testes funcionais manuais focados em cenários de uso comum, casos de borda e tratamento de entradas inválidas.

**Escopo dos Testes:**
* **Funcionalidades Principais:** Inserção, Busca, Remoção e Listagem de palavras e significados.
* **Funcionalidades de Persistência:** Salvamento do dicionário em arquivo e Carregamento do dicionário a partir de um arquivo.

## Ambiente de testes

* **Linguagem de Programação:** C
* **Compilador:** GCC (GNU Compiler Collection)
* **Sistema Operacional:** Testado em ambiente baseado em Linux (Ubuntu).
* **Controle de Versão:** Git, utilizando um modelo de fluxo de trabalho GitFlow Simplificado com branches `main`, `develop` e `feature/*`.

## 3. Testes das Funcionalidades Principais

### 3.1. Testes da Função de Inserção (`inserirPalavra`)

| Teste | Ação Realizada                                                         | Resultado Esperado                                                                                      | Status        |
| :---- | :--------------------------------------------------------------------- | :------------------------------------------------------------------------------------------------------ | :------------ |
| TC-01 | **(Caminho Feliz)** Inserir uma palavra nova (ex: "software") com um significado.  | A palavra é adicionada com sucesso. A busca e a listagem subsequentes devem exibir a nova palavra. | ✅ |
| TC-02 | **(Caso de Borda)** Inserir a mesma palavra ("software") com um segundo significado diferente. | Nenhuma entrada duplicada é criada. A palavra "software" passa a ter dois significados associados.   | ✅ |

### 3.2. Testes da Função de Busca (`buscarPalavra`)

| Teste | Ação Realizada                                              | Resultado Esperado                                                                                   | Status        |
| :---- | :---------------------------------------------------------- | :--------------------------------------------------------------------------------------------------- | :------------ |
| TC-03 | **(Caminho Feliz)** Buscar uma palavra existente no dicionário. | A palavra e todos os seus significados são exibidos corretamente.                                    | ✅ |
| TC-04 | **(Caso Inválido)** Buscar uma palavra que não existe no dicionário. | O sistema exibe uma mensagem informativa, como "Palavra '...' não encontrada...", sem causar erros. | ✅ |

### 3.3. Testes da Função de Remoção (`removerPalavra`)

| Teste | Ação Realizada                                          | Resultado Esperado                                                                                             | Status        |
| :---- | :------------------------------------------------------ | :------------------------------------------------------------------------------------------------------------- | :------------ |
| TC-05 | **(Caminho Feliz)** Remover uma palavra existente.          | O sistema confirma a remoção. Uma busca posterior pela mesma palavra falha, e ela não aparece mais na listagem. | ✅ |
| TC-06 | **(Caso Inválido)** Tentar remover uma palavra que não existe. | O sistema exibe uma mensagem informativa e o estado do dicionário permanece inalterado.                  | ✅ |

### 3.4. Testes da Função de Listagem (`listarPalavras`)

| Teste | Ação Realizada                                | Resultado Esperado                                                                   | Status        |
| :---- | :-------------------------------------------- | :----------------------------------------------------------------------------------- | :------------ |
| TC-07 | **(Caso de Borda)** Solicitar a listagem de um dicionário vazio. | O sistema exibe uma mensagem informativa, como "O dicionário está vazio.". | ✅ |

## 4. Testes das Funcionalidades de Persistência de Arquivo

### 4.1. Testes da Função de Salvamento (`salvarDicionario`)

| Teste | Ação Realizada                                                                               | Resultado Esperado                                                                                              | Status        |
| :---- | :------------------------------------------------------------------------------------------- | :-------------------------------------------------------------------------------------------------------------- | :------------ |
| TC-08 | **(Caminho Feliz)** Adicionar múltiplas entradas e sair do programa.                             | Um arquivo `dicionario.txt` é criado e seu conteúdo reflete com precisão o estado do dicionário. | ✅ |
| TC-09 | **(Sobrescrita)** Iniciar com um `dicionario.txt` existente, modificar o dicionário e sair. | O arquivo `dicionario.txt` original é sobrescrito com o novo estado do dicionário.                       | ✅ |

### 4.2. Testes da Função de Carregamento (`carregarDicionario`)

| Teste | Ação Realizada                                                                               | Resultado Esperado                                                                                                       | Status        |
| :---- | :------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------- | :------------ |
| TC-10 | **(Caminho Feliz)** Iniciar com um `dicionario.txt` bem-formatado e populado.                  | O sistema carrega todas as palavras e significados corretamente.                                                         | ✅ |
| TC-11 | **(Arquivo Inexistente)** Iniciar sem um arquivo `dicionario.txt`.                           | O programa inicia com um dicionário vazio e exibe uma mensagem indicando que um novo dicionário foi criado.           | ✅ |
| TC-12 | **(Robustez)** Iniciar com um `dicionario.txt` contendo linhas malformadas.                  | O programa ignora as linhas malformadas sem travar, carregando apenas as entradas formatadas corretamente.          | ✅ |

## 5. Teste de Interação Completa (Ciclo de Vida)

| Teste | Ação Realizada                                                                                                                                                             | Resultado Esperado                                                                                                                                                                      | Status        |
| :---- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :------------ |
| TC-13 | **(Sessão de Uso Completa)** <br> 1. Carregar um dicionário base.<br>2. Modificá-lo (adicionar/remover).<br>3. Sair para salvar.<br>4. Reiniciar o programa. | O estado final do dicionário na segunda sessão corresponde exatamente às modificações feitas na primeira, confirmando que o ciclo carregar -> modificar -> salvar funciona perfeitamente. | ✅ |

## 6. Conclusão

Todos os casos de teste planejados foram executados e obtiveram os resultados esperados. Os testes confirmam que as funcionalidades principais do dicionário e o sistema de persistência de dados estão operando de forma correta e robusta. O software é considerado estável e pronto para a entrega final.

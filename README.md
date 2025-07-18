# Dicionário com Tabela Hash em C

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Licença](https://img.shields.io/badge/Licen%C3%A7a-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-brightgreen.svg)

Projeto acadêmico desenvolvido para a disciplina de **Laboratório de Algoritmos e Estruturas de Dados II**. Nosso objetivo principal é aplicar o conceito de Tabelas Hash em uma aplicação real para manipular dados textuais, funcionando como um dicionário de palavras e significados.

## 🚀 Principais funcionalidades

O programa oferece uma interface de linha de comando para interagir com um dicionário que permite as seguintes operações:
* **Adicionar palavra:** Insere uma nova palavra e seu respectivo significado.
* **Adicionar múltiplos significados:** Se uma palavra já existe, um novo significado é adicionado a ela
* **Buscar palavra:** Procura por uma palavra e exibe todos os seus significados.
* **Remover palavra:** Exclui uma palavra e todos os seus significados do dicionário.
* **Listar tudo:** Exibe todas as palavras e significados armazenados.
* **Persistência dos dados:** Salva automaticamente o dicionário em um arquivo `dicionario.txt` ao sair e o carrega ao iniciar.

## 📂 Estrutura modular do projeto

O projeto foi estruturado de forma modular para separar responsabilidades, facilitar a manutenção e a compreensão do código, conforme boas práticas de programação.

* [`main.c`](https://github.com/itallodemesquita/hash-dictionary/blob/main/main.c): Contém a interface do usuário (menu interativo) e o laço principal do programa. É o ponto de entrada da aplicação.
* [`hash_table.h`](https://github.com/itallodemesquita/hash-dictionary/blob/main/hash_table.h): O arquivo de cabeçalho (header). Funciona como o "contrato" do nosso módulo de hash, definindo as estruturas de dados (`TabelaHash`, `EntradaHash`, `Significado`) e os protótipos das funções públicas.
* [`hash_table.c`](https://github.com/itallodemesquita/hash-dictionary/blob/main/hash_table.c): A implementação (código-fonte) de toda a lógica da tabela hash. Contém as funções de criar, inserir, buscar, remover, listar, salvar e carregar.
* [`dicionario.txt`](): Arquivo de texto gerado automaticamente para armazenar os dados do dicionário, garantindo a persistência das informações entre as sessões de uso.

## 🛠️ Tecnologias e frameworks utilizados

* **Linguagem:** C
* **Estrutura de Dados:** Tabela Hash
* **Função de Hash:** djb2
* **Tratamento de colisões:** Encadeamento Separado (Separate Chaining)
* **Controle de versão:** Git e GitHub, com um fluxo de trabalho **GitFlow Simplificado**.

## ⚙️ Compilação e execução

Para compilar e executar o projeto em um ambiente Linux/Windows com o GCC instalado, siga os passos:

**1. Clone o repositório:**
```bash
git clone https://github.com/itallodemesquita/hash-dictionary.git
```
**2. Navegue até a pasta do projeto:**
```bash
cd hash-dictionary
```
**3. Compile o programa:**
Este comando irá compilar os arquivos-fonte e cria um executável chamado `dicionario`.
```bash
gcc main.c tabela_hash.c -o dicionario
```
**4. Execute o programa:**
```bash
./dicionario
```

## 👥 Papéis do projeto

O desenvolvimento seguiu a metodologia de trabalho proposta, com papéis bem definidos para organizar a colaboração.

* **GitMaster:** Ítallo de Mesquita
* **Codificador:** Ítallo de Mesquita
* **Apresentador:** Isabel Freire
* **Redator:** Isabel Freire

## 📜 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](https://github.com/itallodemesquita/hash-dictionary/blob/main/LICENSE) para mais detalhes.
# Gerador de Leads (CRM) em C

Programa de console para Windows que permite cadastrar, listar e buscar leads, mantendo os dados salvos em arquivo texto.

## Funcionalidades

- Cadastro de leads com ID, nome, origem e temperatura.
- Listagem dos registros salvos.
- Busca pelo nome exato.
- Validação de entradas e prevenção de IDs duplicados.
- Persistência dos dados após fechar o programa.
- Limpeza da tela com `system("cls")`.

## Arquivos do projeto

| Arquivo | Função |
| --- | --- |
| `main.c` | Menu principal e chamada das operações. |
| `leads.c` | Cadastro, listagem, busca, validação e armazenamento. |
| `leads.h` | Estrutura `Lead`, constantes e declarações das funções. |

O arquivo `programa.c`, caso esteja no repositório, é uma versão anterior e **não deve ser incluído na compilação desta versão**.

## Como executar no Dev-C++

1. Baixe o repositório em **Code → Download ZIP**.
2. Extraia o ZIP para uma pasta.
3. No Dev-C++, acesse **Arquivo → Novo → Projeto**.
4. Escolha **Console Application**, selecione a linguagem **C** e salve o projeto na pasta dos arquivos.
5. Remova do projeto o arquivo de exemplo criado automaticamente, sem apagar o `main.c` baixado.
6. Em **Projeto → Adicionar ao projeto**, selecione `main.c`, `leads.c` e `leads.h`.
7. Pressione **F11 — Compilar e Executar**.

## Como compilar com GCC

Na pasta dos arquivos, execute:

```sh
gcc -std=c99 -Wall -Wextra -Wpedantic main.c leads.c -o crm.exe
```

Depois, no PowerShell:

```powershell
.\crm.exe
```

Compile somente `main.c` e `leads.c`. O cabeçalho `leads.h` é incluído pelo próprio código.

## Como usar

| Opção | Operação |
| --- | --- |
| **1** | Cadastrar um novo lead. |
| **2** | Listar os leads salvos. |
| **3** | Buscar pelo nome exato. |
| **4** | Encerrar o programa. |

Após cada operação, pressione **Enter** para voltar ao menu.

## Regras de cadastro

- O ID deve ser positivo e não pode se repetir.
- Origem e temperatura aceitam valores de **1 a 3**.
- O nome é obrigatório e pode ocupar até **49 bytes**.
- O nome não pode conter ponto e vírgula (`;`) ou caracteres de controle.
- O limite é de **50 leads**.
- A busca diferencia letras maiúsculas de minúsculas e mostra todos os registros com o nome informado.

## Armazenamento

Os dados ficam em `dados_leads.txt`, criado na pasta de execução ao salvar o primeiro cadastro.

Cada linha segue este formato:

```text
id;nome;origem;temperatura
```

Exemplo:

```text
1;Ana Silva;2;3
```

Os registros permanecem salvos após encerrar e reabrir o programa. Faça uma cópia de segurança antes de modificar o arquivo manualmente.

Registros inválidos são informados durante a leitura. Novos cadastros ficam bloqueados até que esses registros sejam corrigidos.

## Testes realizados

A lógica corrigida passou por **63 cenários automatizados**, incluindo:

- Cadastro, listagem e busca.
- Persistência entre execuções.
- Entradas inválidas e nomes muito longos.
- IDs duplicados e limite de cadastros.
- Arquivos ausentes, vazios ou com registros corrompidos.
- Falhas de acesso e gravação.

Após adicionar `system("cls")`, a versão foi recompilada sem erros ou avisos. Cadastro, listagem, busca e persistência também foram conferidos manualmente.

## Limitações

- A limpeza de tela com `cls` é específica do Windows.
- Não há edição ou exclusão de leads.
- A busca exige o nome exato.
- Não foi projetado para várias instâncias gravarem na mesma base simultaneamente.

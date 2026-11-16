# Gerador de Leads (CRM) em C

Programa de console para Windows com cadastro, listagem, busca por nome e persistência em arquivo texto.

## Abrir no Dev-C++

1. Baixe o repositório em **Code → Download ZIP** e extraia todos os arquivos.
2. Abra **CRM_pronto.dev** no Dev-C++.
3. Pressione **F11 — Compilar e Executar**.

## Compilar com GCC

```sh
gcc -std=c99 -Wall -Wextra -Wpedantic main.c leads.c -o crm.exe
```

Execute `crm.exe` na pasta do projeto. A limpeza de tela usa `system("cls")`, específico do Windows.

## Estrutura

- `main.c`: menu e seleção das operações.
- `leads.c`: cadastro, listagem, busca, validação e leitura/gravação.
- `leads.h`: estrutura `Lead`, constantes e declarações compartilhadas.

## Uso e regras

1. Cadastrar lead.
2. Listar leads.
3. Buscar pelo nome exato (distingue maiúsculas de minúsculas).
4. Encerrar.

ID positivo e único; origem e temperatura entre 1 e 3; até 50 leads. Nome obrigatório de até 49 bytes, sem ponto e vírgula ou caracteres de controle. Resultados permanecem visíveis até pressionar Enter.

Os dados são salvos em `dados_leads.txt` na pasta de execução, no formato `id;nome;origem;temperatura`. O arquivo é criado no primeiro cadastro. Faça backup da sua base. Registros inválidos são informados na leitura e bloqueiam novos cadastros até sua correção.

## Validação realizada

A lógica corrigida passou em 63 cenários automatizados no Windows, incluindo persistência entre execuções, entradas inválidas, registros corrompidos, duplicidade, limite de cadastros e falhas de acesso. Após adicionar a limpeza de tela, a versão foi recompilada sem erros ou avisos. Cadastro, listagem, busca e persistência também foram conferidos pelo usuário.

Não possui edição, exclusão ou suporte a gravações simultâneas por várias instâncias.


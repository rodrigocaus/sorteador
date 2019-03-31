# Sorteador

O código sorteador.cpp consiste em um atribuidor de candidatos a `n` avaliadores
em um processo seletivo genérico.

As listas de candidatos e avaliadores devem estar em arquivos de texto separado. 
A estrutura de cada um desses arquivos consiste em um nome por linha, finalizado em quebra 
de linha.

Execute `./sort` ou `./sort --help` para mais informações de como indicar os arquivos de 
entrada.

## Formato de processamento da entrada

Executando `./sort --help` temos a saida:

    usage:
    ./sort <--evaluators | -e> <file> <--competitors | -c> <file> [--ratio | -r <int>]

    Files must be one name per line, ended on \n
    Ratio must be #evaluators assigned to each competitor (default=1)


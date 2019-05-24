# Simulador do Jogo da Vida de Conway

Implementa um sistema que realiza a simulação do jogo da
vida de Conway, que é um exemplo bem conhecido de celullar
automaton, utilizando a estrutura de dados matriz dinâmica na
forma de uma classe em C++.

## Alunos

Camila Duarte e Leonandro Valério

## Compilação e execução do driver(com cmake):
1. `mkdir build`
2. `cd build`
3. `cmake -G "Unix Makefiles" ..`
4. `make`
5. `./glife <argumentos>`

## Observações:

1. Sempre especifique o arquivo fonte das gerações como último argumento
da linha de comando.

## Modos de saída(padrão):
1. Caso você não especifique nem o `--outfile` nem o `--imgdir`,
a simulação irá imprimir as gerações no terminal.

2. Caso você especifique somente o `--outfile`, a simulação
irá imprimir as gerações somente no arquivo especificado.

3. Caso você especifique somente o `--imgdir`, a simulação
irá somente gerar as imagens referentes às gerações no diretório especificado.

4. Caso você especifique tanto o `--outfile` quanto o `--imgdir`
a simulação irá gerar somente as imagens no diretório especificado.

## Help

 Em caso de dúvidas de qual comando usar, basta digitar `./glife --help` e 
a simulação irá exibir um painel de instruções e argumentos disponíveis,
e em seguida encerrará o código.


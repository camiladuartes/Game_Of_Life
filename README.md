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

## Sugestões

Por padrão já trouxemos algumas coisas para que o usuário possa rodar simulações.

Na pasta gens vem 4 arquivos base para gerações: `gen0.txt`, `gen1.txt`, `gen2.txt` e `virus_large2.dat`.

Pode notar que existem duas pastas: `output_files` e `output_images`, que foram colocadas por padrão 
para servir de diretório destino para arquivos e imagens, respectivamente gerados a partir de um arquivo.
Portanto, aqui vão algumas sugestões de execução:

1. `./glife --imgdir ../output_images/ ../gens/gen0.txt` Gera as imagens em output_images a partir de gen0.txt

2. `./glife --outfile ../output_files/out.dat ../gens/gen1.txt` Gera no arquivo out.dat a partir de gen1.txt

3. `./glife --alivecolor YELLOW --bkgcolor BLACK --imgdir ../output_images/ ../gens/gen2.txt` Gera as imagens
com fundo preto e celulas vivas na cor amarela, a partir de gen2.txt

4. `./glife --maxgen 300  --outfile ../output_files/out.dat ../gens/virus_large2.dat` Gera no máximo até 
a geração 300 arquivo out.dat a partir de virus_large2.dat

5. `./glife --maxgen 30 --alivecolor BLUE --bkgcolor YELLOW --imgdir ../output_images/ ../gens/virus_large2.dat`
Gera as imagens com fundo amarelo e células na cor azul de no máximo 30 gerações, a partir de virus_large2.dat
( **OBS** Esse arquivo é relativamente grande em relção aos outros, irá demorar um pouco mais para gerar as imagens ) 

<h1 align="center"> Top-K-Elementos </h1>
<div style="display: inline-block;">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Maintained%3F-yes-green.svg"/> 
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Contributions-welcome-brightgreen.svg?style=flat"/>
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Compilation-Make-orange.svg"/>
</div>
<br><div align=center>
<img src="https://github.com/Guiliard/Guiliard/assets/127882640/bd0cf6e2-5ab4-4f3c-a66a-d92e2cdf92c8.png" width="850px">
</div>

# Introdução

Foi proposto um problema de busca dos K itens mais valiosos de um conjunto de dados. Nessa situação, os conjuntos de dados são arquivos que contém textos sem formatação (Arquivos ASCII), e os itens são palavras. A partir disso, pressupoê-se que estruturas de dados complexas que organizam e avaliam a preciosidade dos K itens (palavras) sejam devidamente operadas, bem como as estruturas auxiliares e variáveis que contribuem para a resolução do problema.

# Descrição do Problema

Em um determinado número de arquivos ".data", encontram-se conjuntos de dados (textos), os quais devem ser lidos e tokenizados (separados em palavras). A partir disso, deve-se armazenar cada palavra em uma tabela hash (tabela de espalhamento), e, com ela, obter-se a frequência das palavras, ou seja, o número de vezes que ela aparece no texto. Depois disso, utilizando o conceito da estrutura heap (árvore de prioridades), deve-se selecionar as K palavras mais valiosas do texto, isto é, aquelas que mais se repetiram.
Para o processo de leitura, considera-se as seguintes limitações:

-  Cada sentença termina por um sinal de pontuação (".", "?", "!"").
-  Cada parágrafo é separado por, pelo menos, uma linha em branco.
-  Cada palavra é separada por espaços ou sinais de pontuação, sendo que os espaços devem estar tanto à direita quanta à esquerda.

# Solução Proposta

<p>Para esse tipo de problema, foi proposto um código que contém 3 arquivos: Methods.hpp, Methods.cpp e main.cpp.<br>

- ```Methods.hpp``` : Classe que possui a declaração dos atributos (características) e métodos (funções) envolvidas no processo de armazenamento e contagem de palavras. <br>
- ```Methods.cpp``` : Arquivo que contém a estruturação das funções envolvidas. <br>
- ```main.cpp``` : Arquivo mais importante, responsável por chamar as funções contidas nas classes e realizar o processo de seleção das K palavras mais valiosas.<br>

Em primeiro lugar, vale ressaltar que a estrutura utilizada para armazenar as palavras do texto (tabela hash) encontra-se como atributo da classe ```Methods.hpp```. Tal estrutura é pré-determinada, ou seja, não foi elaborada no código, mas sim utilizada a partir da inclusão de bibliotecas no programa. Já o heap foi contruído pelo próprio programador, utilizando a lógica original do método de busca do elemento de maior prioridade. 

<strong><h4>Hash :</h4></strong>

A tabela hash, ou tabela de dispersão, é uma estrutura de dados utilizada para armazenar grandes conjunto de dados associados a chaves de forma eficiente. Essas chaves, que são utilizadas como indexação da tabela, são criadas por meio de funções matemáticas aleatórias.<br>
Para toda hash, sua forma de armazenar está associado a um pair, ou seja, a duas inormações, sendo o ```pair.first``` o elemento que foi usado como idexação, e o ```pair.second``` o valor armazenado em si. <br>
A principal característica de tais estruturas é a sua capacidade de acessar valores rapidamente, com custo <i>O(n) = 1</i>. No programa em questão, foi-se utilizado a hash ```Unordered_Map```, a qual faz parte da biblioteca padrão da linguagem C++ e possui a não ordenação como principal característica, ou seja, para tal estrutura, a ordenação dos dados pouco importa. <br>
Em caso de armazenamento de elementos iguais, ocorre-se o fenômeno da colisão, ou seja, dois elementos possuem a mesma chave. Para que isso fosse evitado, e, também, com o intuito de realizar a contagem da frequência das palavras, desenvolveu-se a seguinte lócica: toda vez que ocorresse colisão, significaria que aquela palavra é repetida. Logo, a palavra mais repetida do conjunto de dados é aquela que mais gerou colisão na tabela hash. 

<strong><h4>Heap :</h4></strong>

O heap é uma estrura de dados utilizada para gerenciar e buscar o elemento de maior (Max Heap) ou menor (Min heap) importância, onde tal elemento, no final do processo, localiza-se na raíz da árvore. Para simular essa árvore, foi-se utilizado um vetor (<i>array</i>) para armazenar as K palavras, sendo certas posições desse vetor, escolhidos em base ao seu tamanho, possuem folhas, precisamente nas posições (2*i) e (2*i + 1). <br>
Nó código, foi-se utilizado o Min Heap com o seguinte objetivo: se o elemento da raíz dos K itens selecionados fosse menor do que algum elemento armazenado na hash, há-se uma substituição entre tais elementos até que os os itens contidos no heap são os mais valiosos, atingindo, com isso, o objetivo final do trabalho. 

Dado as estruturas principais do programa, evidencia-se as funções contidas na classe ```Methods.cpp``` que tornam todo o processo de leitura, armazenamento e classificação dos dados:

- ```Leitura```: Função responsável por realizar a leitura dos múltiplos arquivos contidos na pasta "dataset", os quais se tornarão o conjunto de dados. É importante ressaltar que nem todas as palavras contidas no texto serão armazenadas, já que, palavras muito repetidas, tais como artigos e advérbios (informados no arquivo "stopwords.txt"), são descartadas. 
- ```Tratamento_para_Hash```: Método que realiza um tratamento do texto lido, convertendo todas as letras maiúsculas para minúsculas e retirando os seguintes sinais de pontuação:

  * ','
  * ':'
  * ';'
  * '/'
  * '"'
  * '!'
  * '?'
  * '('
  * ')'
  * '--'
- ```Cria_Hash```: Função responsável por tokenizar o texto, remover as stopwords e adicionar as palavras obtidas na hash. 
- ```Cria_Heap```: Método que faz a administração e controle dos itens que estão no heap, substituindo a menor palavra contida no <i>array</i> por outra de maior frequência contida na hash até que as K palavras mais frequêntes estejam localizadas nesse vetor que simula uma árvore. 
- ```Opera_Heap```: Função responsável por administrar o próprio heap, realizando trocas (<i>swaps</i>) entre os elementos com a seguinte condição:
  * Caso o elemento filho (posição 2*i e 2*i + 1) seja menor do que a posição pai (i), é realizado um traca entre as posições. Com isso, após tal processo, o menor elemento se encontrará na posição 0 do <i>array</i>.
- ```Re_Heap```: Cópia da função ```Opera_Heap```, contudo, possuindo o objetivo de conferir se todo pai (raíz) é menor que seus filhos (folhas) e, caso não seja, realizando trocas até que tal situação se torne verdade. 

# Casos Especiais

# Casos Sem Tratamento e Possíveis Erros

# Implementação

# Conclusão

# Especificações do Dispositivo Utilizado

| Componentes            | Detalhes                                                                                         |
| -----------------------| -----------------------------------------------------------------------------------------------  |
|  `Processador`         | Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz   1.50 GHz                                             |
|  `RAM Instalada`       | 8.0 GB (Utilizável: 7.8 GB)                                                                      |
|  `Tipo de Sistema`     | Sistema Operacional de 64 bits, processador baseado em x64                                       |
|  `Sistema Operacional` | Edição Windows 11 Home Single Language, versão 22H2                                              |

# Compilação e Execução

Um arquivo Makefile que realiza todo o procedimento de compilação e execução está disponível no código. Para utilizá-lo, siga as diretrizes de execução no terminal:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

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

Foi proposto um problema de busca dos <i>K</i> itens mais valiosos de um conjunto de dados. Nessa situação, os grupos de dados são arquivos que contém textos sem formatação (Arquivos ASCII), e os itens são palavras. A partir disso, pressupoê-se que estruturas de dados complexas, as quais organizam e avaliam a preciosidade dos K itens (palavras), sejam devidamente operadas, bem como as estruturas auxiliares e variáveis que contribuem para a resolução do problema.

# Descrição do Problema

Em um determinado número de arquivos ".data", encontram-se conjuntos de dados (textos), os quais devem ser lidos e tokenizados (separados em palavras). A partir disso, deve-se armazenar cada palavra em uma tabela hash (tabela de espalhamento), e, com ela, obter-se a frequência das palavras, ou seja, o número de vezes que ela aparece no texto. Depois disso, utilizando o conceito da estrutura heap (árvore de prioridades), deve-se selecionar as <i>K</i> palavras mais valiosas do texto, isto é, aquelas que mais se repetiram.
Para o processo de leitura, considera-se as seguintes instruções:

-  Cada sentença termina por um sinal de pontuação (".", "?", "!").
-  Cada parágrafo é separado por, pelo menos, uma linha em branco.
-  Cada palavra é separada por espaços ou sinais de pontuação, sendo que os espaços devem estar tanto à direita quanta à esquerda.

Para o processo de saída, considera-se as seguintes regras:
- Output legível.
- Construção lógica do heap (processo esse que será explicado posteriormente).
- Deve-se desconsiderar da massa de dados as palavras definidas como "stopwords.txt".

# Solução Proposta

<p>Para esse tipo de problema, foi proposto um código que contém 3 arquivos principais: Methods.hpp, Methods.cpp e main.cpp.<br>

- ```Methods.hpp``` : Classe que possui a declaração dos atributos (características) e métodos (funções) envolvidas no processo de armazenamento e contagem de palavras. É importante ressaltar que é nesse arquivo que se encontra a declaração do valor assumido por <i>K</i>. <br>
- ```Methods.cpp``` : Arquivo que contém a estruturação das funções envolvidas. <br>
- ```main.cpp``` : Arquivo fonte, responsável por chamar as funções contidas nas classes e realizar o processo de seleção das <i>K</i> palavras mais valiosas.<br>

Em primeiro lugar, vale ressaltar que a estrutura utilizada para armazenar as palavras do texto (tabela hash) encontra-se como atributo da classe ```Methods.hpp```. Tal estrutura é pré-determinada, ou seja, não foi elaborada no código, mas sim utilizada a partir da inclusão de bibliotecas no programa. Já o heap foi contruído pelo próprio programador, utilizando a lógica original do método de busca do elemento de maior prioridade. 

<strong><h4>Hash :</h4></strong>

A tabela hash, ou tabela de dispersão, é uma estrutura de dados utilizada para armazenar grandes conjunto de informações associados a chaves de forma eficiente. Essas chaves, que são utilizadas como indexação da tabela, são criadas por meio de funções matemáticas aleatórias.<br>
Para toda hash, sua forma de armazenar está associado a um ```pair```, ou seja, a duas inormações, sendo o ```pair.first``` o elemento que foi usado como idexação, e o ```pair.second``` o valor armazenado em si. <br>
A principal característica de tais estruturas é a sua capacidade de acessar valores rapidamente, com custo <i>O(n) = 1</i>. No programa em questão, foi-se utilizado a hash ```unordered_map```, a qual faz parte da biblioteca padrão ```<map>``` da linguagem C++ e possui a não ordenação como principal característica, ou seja, para tal estrutura, a ordem dos dados pouco importa. <br>
Em caso de armazenamento de elementos iguais, ocorre-se o fenômeno da colisão, ou seja, dois elementos possuem a mesma chave. Para que isso fosse evitado, e, também, com o intuito de realizar a contagem da frequência das palavras, desenvolveu-se a seguinte lógica: toda vez que ocorresse colisão, significaria que aquela palavra é repetida. Logo, as K palavras mais repetidas do conjunto de dados são as <i>K</i> palavras que mais geraram colisão na tabela hash. <br>
- Sintaxe: ```unordered_map <tipo_chave, tipo_item> hash ```
- Custo: <i>O(1) * n</i>, onde <i>n</i> é o número de itens (palavras) inseridas, ou seja, custo <i>n</i>.

<strong><h4>Heap :</h4></strong>

O heap é uma estrura de dados utilizada para gerenciar e buscar o elemento de maior (Max Heap) ou menor (Min heap) importância, onde tal elemento, no final do processo, localiza-se na raíz da árvore (posição inicial). Para simular essa árvore, foi-se utilizado um vetor (<i>array</i>) para armazenar as <i>K</i> palavras, sendo que as posições i desse vetor possuem folhas, precisamente nas posições (2*i) e (2*i + 1). <br>
Nó código, foi-se utilizado o Min Heap com o seguinte objetivo: se o elemento da raíz dos <i>K</i> itens selecionados fosse menor do que algum elemento armazenado na hash, haveria-se uma substituição entre tais elementos até que os os itens contidos no heap são os mais valiosos, atingindo, com isso, o objetivo final do trabalho. 

Dado as estruturas principais do programa, evidencia-se as funções contidas na classe ```Methods.cpp``` que tornam possível todo o processo de leitura, armazenamento e classificação dos dados:

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
- ```Cria_Heap```: Método que faz a administração e controle dos itens que estão no heap, substituindo a menor palavra contida no <i>array</i> por outra de maior frequência contida na hash, até que as <i>K</i> palavras mais frequêntes estejam localizadas nesse vetor que simula uma árvore. 
- ```Opera_Heap```: Função responsável por administrar o próprio heap, realizando trocas (<i>swaps</i>) entre os elementos com a seguinte condição:
  * Caso o elemento filho (posição 2*i e 2*i + 1) seja menor do que a posição pai (i), é realizado um traca entre as posições. Com isso, após tal processo, o menor elemento se encontrará na posição inicial (0) do <i>array</i>.
- ```Re_Heap```: Cópia da função ```Opera_Heap```, contudo, possuindo o objetivo de conferir se todo pai (raíz) é menor que seus filhos (folhas) e, caso não seja, realizando trocas até que tal situação se torne verdade.

Com a interconexão de todas essas funções, a seleção dos <i>K</i> itens mais valiosos do conjunto de dados se torna possível.

<strong><h4>Arquivos :</h4></strong>

<div align=center>
<img src="https://github.com/Guiliard/Top-K-Elementos/assets/127882640/6f72300c-ee9a-4212-a8e8-65a8eb437a76.png" width="850px">
</div>

# Casos Especiais

<strong><h4>Hash_stop_words :</h4></strong>
Para que as palavras contidas no arquivo "stopwords.txt" fossem excluidas da massa de dados a ser trabalhada, foi-se criada uma tabela hash auxiliar, a qual contém todas as palavras que devem ser desconsideradas na prática em questão. Assim, comparava-se cada palavra a ser inserida da hash principal com os elementos da hash auxiliar, e apenas os diferentes eram inseridos. Com isso, obteve-se a exclusão ou o não armazenamento das palavras definidas como stopwords.

- Sintaxe: ```unordered_map <tipo_chave, tipo_item> hash_stop_words ```

<strong><h4>Re_Heap :</h4></strong>
Para pequenas massas de dados, não se garante que apenas a função ```Opera_Heap``` seja suficiente para garantir que todo pai (raíz) de posição i seja menor que seus filhos (folhas) de posições 2*i e 2*i + 1. Portanto, para esse caso, criou-se a função ```Re_Heap```, cujo objetivo maior é garantir que tal premissa seja verdadeira para qualquer massa de dados.

# Casos Sem Tratamento e Possíveis Erros

Os limites do programa elaborado se concentram em pontuações não tratadas. Evidenciando-se melhor, se, em um arquivo do tipo ".data", existir algum sinal de pontuação que não foi tratada na função ```Tratamento_para_Hash```, as palavras que estão junto àquele sinal não serão tokenizadas da forma esperada, resultando, dessa forma, em uma quebra de lógica do código.<br>
Exemplo da situação acima:
- Palavra "Casa&" -> '&' não foi um sinal tratado -> logo "Casa&" é diferente de "Casa" -> o que não condiz com a lógica do exercício.

# Implementação

# Conclusão

De forma geral, o programa, orientado à objeto, se mostra eficiente para encontrar os <i>K</i> itens mais valiosos de uma coleção de dados. Seu custo computacional geral é dado por <i> O(n * log k)</i>, onde <i>n</i> é o tamanho da coleção de dados e <i>K</i> é o número de itens mais valiosos. Além disso, vale ressaltar que quanto maior o arquivo "stopwords.txt" menor é o custo computacional associado, tendo em vista que tal operação minimiza o <i>n</i>. <br>
Em se tratando de estruturas, observa-se que a utilização de métodos diferentes dos aqui utilizados (Hash - linear & Heap - logarítmo) tornariam o custo computacional maior, o que resultaria, possivelmente, em um tempo de execução não viável. <br>
Por fim, afirma-se que o objetivo do trabalho foi cumprido com exelência, porém, o código é passivo de melhorias e otimizações, tais como aquelas discutidas na seção "Casos Sem Tratamento e Possíveis Erros".

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

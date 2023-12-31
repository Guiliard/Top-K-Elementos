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

Em primeiro lugar, vale ressaltar a classe utilizada para a construção do código em questão. 

```cpp
typedef struct word
{
    string palavra;
    short int contador;
}word;

class Leitor
{
    private:
    word palavra;
    unordered_map <string, word> hash;
    unordered_map <string, string> hash_stop_words;
    vector <word> heap;

    public:
    Leitor();

    void setPalavra (word palavra);
    word getPalavra ();

    void setHash (unordered_map <string, word> hash);
    unordered_map <string, word> geTHash();

    void setHash_Stop_Words (unordered_map <string, string> hash_stop_words);
    unordered_map <string, string> getHash_Stop_Words();

    void setVector (vector <word> ordenar);
    vector <word> getVector();

    string Leitura(ifstream &arq);
    string Tratamento_para_Hash(ifstream &arq);

    void Cria_Hash(ifstream &arq);
    void Cria_Heap();
    void Opera_Heap();
};
```

Ademais, evidencia-se que a estrutura utilizada para armazenar as palavras do texto (tabela hash) encontra-se como atributo da classe ```Leitor``` declarada no arquivo  ```Methods.hpp```. Tal estrutura é pré-determinada, ou seja, não foi elaborada no código, mas sim utilizada a partir da inclusão de bibliotecas no programa. Já o heap foi construído pelo próprio programador, utilizando a lógica original do método de busca do elemento de maior prioridade. 
<strong><h4>Hash :</h4></strong>

A tabela hash, ou tabela de dispersão, é uma estrutura de dados utilizada para armazenar grandes conjunto de informações associados a chaves de forma eficiente. Essas chaves, que são utilizadas como indexação da tabela, são criadas por meio de funções matemáticas aleatórias, as quais dependem da versão do compilador (g++) e do tipo da hash utilizada. No programa em questão, por se tratar de uma hash de words (palavras), as quais possuem strings em sua composição, a função matemática associada é a <i>MurMurHashUnaligned2</i>.<br>

```cpp
template<>
    struct hash<string>
    : public __hash_base<size_t, string>
    {
      size_t
      operator()(const string& __s) const noexcept
      { return std::_Hash_impl::hash(__s.data(), __s.length()); }
    };
```
- Especialização da hash definida para string (palavra).

```cpp
size_t _Hash_bytes(const void* ptr, size_t len, size_t seed)
{ const size_t m = 0x5bd1e995; size_t hash = seed ^ len;
  const char* buf = static_cast<const char*>(ptr);

  while (len >= 4)
  {
    size_t k = unaligned_load(buf);
    k *= m; k ^= k >> 24; k *= m; hash *= m; hash ^= k;
    buf += 4;
    len -= 4;
  }
  switch (len)
  {
    case 3:
      hash ^= static_cast<unsigned char>(buf[2]) << 16;
      [[gnu::fallthrough]];
    case 2:
      hash ^= static_cast<unsigned char>(buf[1]) << 8;
      [[gnu::fallthrough]];
    case 1:
      hash ^= static_cast<unsigned char>(buf[0]);
      hash *= m;
  };
  hash ^= hash >> 13; hash *= m;
  hash ^= hash >> 15; return hash;
}
```
- Implementação da hash.

Para toda hash, sua forma de armazenar está associado a um ```pair```, ou seja, a duas inormações, sendo o ```pair.first``` o elemento que foi usado como idexação, e o ```pair.second``` o valor armazenado em si. <br>
A principal característica de tais estruturas é a sua capacidade de acessar valores rapidamente, com custo <i>O(n) = 1</i>. Na solução apresentada, foi-se utilizado a hash ```unordered_map```, a qual faz parte da biblioteca padrão ```<map>``` da linguagem C++ e possui a não ordenação como principal característica, ou seja, para tal estrutura, a ordem dos dados pouco importa. <br>
Em caso de armazenamento de elementos iguais, ocorre-se o fenômeno da colisão, ou seja, dois elementos possuem a mesma chave. Para que isso fosse evitado, e, também, com o intuito de realizar a contagem da frequência das palavras, desenvolveu-se a seguinte lógica: toda vez que ocorresse colisão, significaria que aquela palavra é repetida. Logo, as K palavras mais repetidas do conjunto de dados são as <i>K</i> palavras que mais geraram colisão na tabela hash. <br>
- Sintaxe: ```unordered_map <tipo_chave, tipo_item> hash ```
- Custo: <i>O(1) * n</i>, onde <i>n</i> é o número de itens (palavras) inseridas, ou seja, custo <i>n</i>.

<strong><h4>Heap :</h4></strong>

O heap é uma estrura de dados utilizada para gerenciar e buscar o elemento de maior (Max Heap) ou menor (Min heap) importância, onde tal elemento, no final do processo, localiza-se na raíz da árvore (posição inicial). Para simular essa árvore, foi-se utilizado um vetor (<i>array</i>) para armazenar as <i>K</i> palavras, sendo que as posições i desse vetor possuem folhas, precisamente nas posições (2*i) e (2*i + 1) ou (2*i+1) e (2*i+2), dependendo se a raíz (início do vetor) é 1 ou 0.<br>
Nó código, foi-se utilizado o Min Heap com o seguinte objetivo: se o elemento da raíz dos <i>K</i> itens selecionados fosse menor do que algum elemento armazenado na hash, haveria-se uma substituição entre tais elementos até que os os itens contidos no heap são os mais valiosos, atingindo, com isso, o objetivo final do trabalho. 
- Custo: <i>O(log * n)</i>, onde <i>n</i> é o número de itens inseridos na estrutura em árvore, ou seja, <i>K</i>.

Dado as estruturas principais do programa, evidencia-se as funções contidas na classe ```Methods.cpp``` que tornam possível todo o processo de leitura, armazenamento e classificação dos dados:

- ```Leitura```: Função responsável por realizar a leitura dos múltiplos arquivos contidos na pasta "dataset", os quais se tornarão o conjunto de dados. É importante ressaltar que nem todas as palavras contidas no texto serão armazenadas, já que, palavras muito repetidas, tais como artigos e advérbios (informados no arquivo "stopwords.txt"), são descartadas.
  
  * Forma dos arquivos do tipo ".data": "input{x}.data", sendo x um número maior ou igual a 1.

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
  * Caso o elemento filho (posição 2*i e 2*i + 1) seja menor do que a posição pai (i), é realizado um troca entre as posições. Com isso, após tal processo, o menor elemento se encontrará na posição inicial (0) do <i>array</i>.

Com a interconexão de todas essas funções, a seleção dos <i>K</i> itens mais valiosos do conjunto de dados se torna possível.

<strong><h4>Arquivos separados em pastas:</h4></strong>


<div align=center>
<img src="https://github.com/Guiliard/Top-K-Elementos/assets/127882640/1b325d47-1b6f-44ef-b591-c94b62869e52.png" width="850px">
</div>


# Casos Especiais

<strong><h4>Hash_stop_words :</h4></strong>
Para que as palavras contidas no arquivo "stopwords.txt" fossem excluidas da massa de dados a ser trabalhada, foi-se criada uma tabela hash auxiliar, a qual contém todas as palavras que devem ser desconsideradas na prática em questão. Assim, comparava-se cada palavra a ser inserida da hash principal com os elementos da hash auxiliar, e apenas os diferentes eram inseridos. Com isso, obteve-se a exclusão ou o não armazenamento das palavras definidas como stopwords.

- Sintaxe: ```unordered_map <tipo_chave, tipo_item> hash_stop_words ```

# Casos Sem Tratamento e Possíveis Erros

Os limites do programa elaborado se concentram em pontuações não tratadas. Evidenciando-se melhor, se, em um arquivo do tipo ".data", existir algum sinal de pontuação que não foi tratada na função ```Tratamento_para_Hash```, as palavras que estão junto àquele sinal não serão tokenizadas da forma esperada, resultando, dessa forma, em uma quebra de lógica do código.<br>
Exemplo da situação acima:
- Palavra "Casa&" -> '&' não foi um sinal tratado -> logo "Casa&" é diferente de "Casa" -> o que não condiz com a lógica do exercício.

# Implementação

Considere os seguintes exemplos de entrada para o programa: 

|   Entrada     |    Conteúdo                      | Quantidade de linhas |
|---------------|----------------------------------|----------------------|
| input1.data   |         Dom_Casmurro.txt         | 6385                 |
| input2.data   | Semana_Machado_de_Assis.txt      | 27765                |
| stopwords.txt | Artigos_e_Adjuntos.txt           | 207                  |

<strong><h4>input1.data :</h4></strong>
```
Dom Casmurro

Machado de Assis

CAPÍTULO PRIMEIRO / DO TÍTULO

Uma noite destas, vindo da cidade para o Engenho Novo, encontrei num trem da Central um rapaz
aqui do bairro, que eu conheço de vista e de chapéu. Cumprimentou-me, sentou-se ao pé de mim,
falou da lua e dos ministros, e acabou recitando-me versos. A viagem era curta, e os versos pode ser
que não fossem inteiramente maus. Sucedeu, porém, que, como eu estava cansado, fechei os olhos
três ou quatro vezes; tanto bastou para que ele interrompesse a leitura e metesse os versos no bolso.

-- Continue, disse eu acordando.

-- Já acabei, murmurou ele.

-- São muito bonitos.

Vi-lhe fazer um gesto para tirá-los outra vez do bolso, mas não passou do gesto; estava amuado. No
dia seguinte entrou a dizer de mim nomes feios, e acabou alcunhando-me Dom Casmurro. Os
vizinhos, que não gostam dos meus hábitos reclusos e calados, deram curso à alcunha, que afinal
pegou. Nem por isso me zanguei. Contei a anedota aos amigos da cidade, e eles, por graça,
chamam-me assim, alguns em bilhetes: "Dom Casmurro, domingo vou jantar com você."--"Vou
para Petrópolis, Dom Casmurro; a casa é a mesma da Renania; vê se deixas essa caverna do
Engenho Novo, e vai lá passar uns quinze dias comigo."--"Meu caro Dom Casmurro, não cuide que
o dispenso do teatro amanhã; venha e dormirá aqui na cidade; dou-lhe camarote, dou-lhe chá, doulhe cama; só não lhe dou moça."
Não consultes dicionários. Casmurro não está aqui no sentido que eles lhe dão, mas no que lhe pôs
o vulgo de homem calado e metido consigo. Dom veio por ironia, para atribuir-me fumos de
fidalgo. Tudo por estar cochilando! Também não achei melhor título para a minha narração - se não
tiver outro daqui até ao fim do livro, vai este mesmo. O meu poeta do trem ficará sabendo que não
lhe guardo rancor. E com pequeno esforço, sendo o título seu, poderá cuidar que a obra é sua. Há
livros que apenas terão isso dos seus autores; alguns nem tanto.
```

<strong><h4>Resultado esperado :</h4></strong>
```
Arquivo 1: 
0 Palavra: escobar --> Frequência: 110
1 Palavra: agora --> Frequência: 146
2 Palavra: padre --> Frequência: 111
3 Palavra: mim --> Frequência: 162
4 Palavra: vez --> Frequência: 147
5 Palavra: nada --> Frequência: 133
6 Palavra: tempo --> Frequência: 120
7 Palavra: dias --> Frequência: 191
8 Palavra: olhos --> Frequência: 164
9 Palavra: assim --> Frequência: 156
10 Palavra: capÍtulo --> Frequência: 148
11 Palavra: ainda --> Frequência: 139
12 Palavra: outra --> Frequência: 138
13 Palavra: disse --> Frequência: 124
14 Palavra: tão --> Frequência: 121
15 Palavra: capitu --> Frequência: 338
16 Palavra: mãe --> Frequência: 228
17 Palavra: tudo --> Frequência: 189
18 Palavra: casa --> Frequência: 168
19 Palavra: josé --> Frequência: 160
```

<strong><h4>input2.data :</h4></strong>
```
A semana Texto-fonte: Obra Completa de Machado de Assis. 

Rio de Janeiro: Nova Aguilar, Vol. 

III, . 

Publicado originalmente na Gazeta de Notícias, Rio de Janeiro, de // a //.   

de abril Na segunda feira da semana que findou, acordei cedo, pouco depois das galinhas, e dei-me ao gosto de propor a mim mesmo um problema. 

Verdadeiramente era uma charada; mas o nome de problema dá dignidade, e excita para logo a atenção dos leitores austeros. 

Sou como as atrizes, que já não fazem benefício, mas festa artística. 

A coisa é a mesma, os bilhetes crescem de igual modo, seja em número, seja em preço; o resto, comédia, drama, opereta, uma polca entre dois atos, uma poesia, vários ramalhetes, lampiões fora, e os colegas em grande gala, oferecendo em cena o retrato à beneficiada. 

Tudo pede certa elevação. 

Conheci dois velhos estimáveis, vizinhos, que esses tinham todos os dias a sua festa artística. 

Um era Cavaleiro da Ordem da Rosa, por serviços em relação à guerra do Paraguai; o outro tinha o posto de tenente da guarda nacional da reserva, a que prestava bons serviços. 

Jogavam xadrez, e dormiam no intervalo das jogadas. 

Despertavam-se um ao outro desta maneira: “Caro major” -”Pronto, comendador” — Variavam às vezes: — “Caro comendador” -”Aí vou, major”. 

Tudo pede certa elevação. 

Para não ir mais longe, Tiradentes. 

Aqui está um exemplo. 
```

<strong><h4>Resultado esperado :</h4></strong>
```
Arquivo 2: 
0 Palavra: onde --> Frequência: 333
1 Palavra: dois --> Frequência: 384
2 Palavra: porque --> Frequência: 337
3 Palavra: todos --> Frequência: 454
4 Palavra: grande --> Frequência: 406
5 Palavra: dia --> Frequência: 366
6 Palavra: vez --> Frequência: 353
7 Palavra: pode --> Frequência: 524
8 Palavra: assim --> Frequência: 454
9 Palavra: aqui --> Frequência: 419
10 Palavra: outros --> Frequência: 417
11 Palavra: coisa --> Frequência: 383
12 Palavra: tempo --> Frequência: 373
13 Palavra: menos --> Frequência: 360
14 Palavra: bem --> Frequência: 359
15 Palavra: ainda --> Frequência: 629
16 Palavra: tudo --> Frequência: 560
17 Palavra: outro --> Frequência: 474
18 Palavra: homem --> Frequência: 471
19 Palavra: outra --> Frequência: 435
```

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


# Referências

[1] Stack Overflow - Discussion of C++. Disponível em: <https://stackoverflow.com/questions/19411742/what-is-the-default-hash-function-used-in-c-stdunordered-map>. Acesso em: 24/08/2023.

[2] CORMEN, T. H. et al. Introduction to Algorithms, third edition. [s.l.] MIT Press, 2012. Acessado em 01 de Março de 2023.

[3] PIRES, MICHEL - Repositório GitHub, @mpiress: HeapSort - Disponível em: https://github.com/mpiress/HeapSort. Acessado em 20 de Agosto de 2023.

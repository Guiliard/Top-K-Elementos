#ifndef __METHODS_HPP
#define __METHODS_HPP

#define K 20

#include <bits/stdc++.h>

using namespace std;

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
#endif

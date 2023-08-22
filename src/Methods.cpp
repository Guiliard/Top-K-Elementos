#include "Methods.hpp"

Leitor :: Leitor()
{
}

void Leitor :: setPalavra (word palavra) {this->palavra=palavra;}
word Leitor :: getPalavra () {return this->palavra;}
void Leitor :: setHash (unordered_map <string, word> hash) {this->hash=hash;}
unordered_map <string, word> Leitor :: geTHash() {return this->hash;}
void Leitor :: setHash_Stop_Words (unordered_map <string, string> hash_stop_words) {this->hash_stop_words=hash_stop_words;}
unordered_map <string, string> Leitor :: getHash_Stop_Words() {return this->hash_stop_words;}

string Leitor :: Leitura (ifstream &arq)
{
    string texto, linha;
    while (!arq.eof())
    {
        getline(arq, linha);
        if(!linha.empty())
            linha = linha + " ";
        texto = texto + linha;
    }
    arq.close();

    ifstream arq2; 
    arq2.open("dataset/stopwords.txt");
    string palavra;
    while (!arq2.eof())
    {
        getline(arq2, palavra);
        hash_stop_words[palavra] = palavra;
    }
    arq2.close(); return texto;
}

string Leitor :: Tratamento_para_Hash (ifstream &arq)
{
    string texto_para_tratar = Leitura (arq);
    
    for (char &letra : texto_para_tratar) 
    {
        letra = tolower(letra);
    }

    char ponto1 = '.', ponto2 = ',', ponto3 = ':', ponto4 = ';', ponto5 = '/', ponto6 = '"', ponto7 = '!', ponto8 = '?';
    char ponto9 = '(', ponto10 = ')';
    for (char &c : texto_para_tratar) 
    {
        if (c == ponto1 || c == ponto2 || c == ponto3 || c == ponto4 || c == ponto5 || c == ponto6 || c == ponto7 || c == ponto8 || c == ponto9 || c == ponto10) 
        {
            c = ' ';
        }
    }

    string travs = "--";
    size_t position;
    while(1)
    {
        position = texto_para_tratar.find(travs);
        if (position != std::string::npos) 
        {
            texto_para_tratar[position] = ' '; texto_para_tratar[position+1] = ' ';
        }
        else
            break;
    }
    return texto_para_tratar;
}

void Leitor :: Cria_Hash(ifstream &arq)
{
    string texto = Tratamento_para_Hash (arq);
    istringstream tok(texto);
    string palavra_separada;

    while (tok >> palavra_separada) 
    {
        auto stop = hash_stop_words.find(palavra_separada);
        if(palavra_separada != "-" && stop == hash_stop_words.end() && palavra_separada != "—")
        {
            auto verifica = hash.find(palavra_separada);
            if (verifica != hash.end()) 
                hash [palavra_separada].contador++;
            else
            {
                hash [palavra_separada].palavra = palavra_separada;
                hash [palavra_separada].contador = 1;
            }
        }
    }
    Cria_Heap();
}

void Leitor :: Cria_Heap ()
{
    short int j = 0;
	for (const auto& pair : hash) 
    {
        if(j < K) { heap.push_back(pair.second); j++; }
        else { Opera_Heap(); if(heap[0].contador < pair.second.contador){ heap[0]=pair.second;}}
    }
    for(short int i = 0; i < K; i++)
        cout << i << " Palavra: " << heap[i].palavra << " --> " << "Frequência: " << heap[i].contador << "\n";
    hash.clear();
    hash_stop_words.clear();
    heap.clear();
}

void Leitor :: Opera_Heap()
{
    short int inicio = (K/2)-1;
    for(short int i = inicio; i > -1 ; i--)
    {
        if(heap[i].contador > heap[i+i].contador)
        {
            word aux;
            aux = heap [i];
            heap[i] = heap [i+i];
            heap[i+i] = aux;
        }
        if(heap[i].contador > heap[i+i+1].contador)
        {
            word aux;
            aux = heap [i];
            heap[i] = heap [i+i+1];
            heap[i+i+1] = aux;
        }
    }
}
#include "Methods.hpp"

bool existe(string nomeArquivo) 
{
    ifstream arquivo(nomeArquivo);
    return arquivo.good();
}

int main()
{
    Leitor *texto = new Leitor();
    string nomearq = "dataset/input";
    ifstream arq;
    for(short int i = 1 ; i < 100; i++)
    {
        string nomearq = "dataset/input" + to_string(i) + ".data";
        if (existe(nomearq))
        {
            if(i > 1) {cout << "\n";}
            cout << "Arquivo " << i << ": " << "\n";
            arq.open(nomearq);
            texto->Cria_Hash(arq); 
        }
        else
            break;
    } 
    return 0;  
}
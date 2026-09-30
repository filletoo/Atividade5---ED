#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

extern "C"{

    vector<string> ler_texto(char arquivo[]){
        ifstream texto_processado(arquivo);
        vector<string> texto_vetor;

        int i = 0;
        string linha;
        while (getline(texto_processado, linha))
        {
            texto_vetor.push_back(linha);
        }

        return texto_vetor;
    }

    void salvar_palavras(char arquivo_ordenadas[], vector<string> &palavras){
        ofstream palavras_ordenadas(arquivo_ordenadas);

        for (int i = 0; i < palavras.size(); i++)
        {
            palavras_ordenadas << palavras[i] << '\n';
        }
    }

    double bubble_sort(char arquivo[]){
        vector<string> palavras = ler_texto(arquivo);

        auto inicio = clock();
        bool ordenado = false;
        string temp;
        int ultimo = palavras.size() - 1;

        while (!ordenado)
        {
            ordenado = true;
            for (int i = 0; i < ultimo; i++)
            {
                if (palavras[i] > palavras[i + 1])
                {
                    temp = palavras[i + 1];
                    palavras[i + 1] = palavras[i];
                    palavras[i] = temp;
                    ordenado = false;
                }
            }
            ultimo--;
        }
        double tempo_de_execucao = double(clock() - inicio) / CLOCKS_PER_SEC;
        return tempo_de_execucao;
    }

    double selection_sort(char arquivo[])
    {
        vector<string> palavras = ler_texto(arquivo);
        auto comeco = clock();
        string temp;
        int inicio = 0;
        int pos_menor;

        while (inicio != palavras.size() - 1)
        {
            pos_menor = inicio;
            for (int i = inicio; i < palavras.size(); i++)
            {
                if (palavras[i] < palavras[pos_menor])
                    pos_menor = i;
            }
            temp = palavras[inicio];
            palavras[inicio] = palavras[pos_menor];
            palavras[pos_menor] = temp;
            inicio++;
        }

        double tempo_de_execucao = double(clock() - comeco) / CLOCKS_PER_SEC;
        return tempo_de_execucao;
    }

    double insertion_sort(char arquivo[])
    {
        vector<string> palavras = ler_texto(arquivo);
        auto inicio = clock();
        vector<string> copia(palavras.size());
        string item;
        int quant_copia = 0;

        for (int i = 0; i < palavras.size(); i++){
            if (quant_copia == 0)
            {
                copia[quant_copia++] = palavras[i];
            }
            else
            {
                for (int j = quant_copia - 1; j >= 0; j--)
                {
                    // adicionar no final
                    // cout << quant_copia << '\n';
                    if (j == quant_copia - 1 && palavras[i] >= copia[j])
                    {
                        copia[j + 1] = palavras[i];
                        quant_copia++;
                        break;
                    }

                    // movimentar o item para trás
                    copia[j + 1] = copia[j];

                    // adicionar no inicio
                    if (j == 0)
                    {
                        copia[j] = palavras[i];
                        quant_copia++;
                        break;
                    }

                    // adicionar no meio entre dois
                    if (palavras[i] <= copia[j] && palavras[i] >= copia[j - 1])
                    {
                        copia[j] = palavras[i];
                        quant_copia++;
                        break;
                    }
                }
            }
        }
        double tempo_de_execucao = double(clock() - inicio) / CLOCKS_PER_SEC;
        return tempo_de_execucao;
    }
}

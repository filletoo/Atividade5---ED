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
        double tempo_de_execucao = (double(clock() - inicio) / CLOCKS_PER_SEC);
        return tempo_de_execucao;
    }
    
    double shell_sort(char arquivo[])
    {
        vector<string> palavras = ler_texto(arquivo);
        auto inicio = clock();
        int n = palavras.size();
        vector<int> gaps = {1, 4, 10, 23, 57, 132, 301, 701, 1577, 3548, 7983, 17961, 40412, 90927, 204586, 460318};
        // Começa com metade do tamanho do vetor
        for (int j = gaps.size() - 1; j >= 0; j--)
        {   
            int gap = gaps[j];
            for (int i = gap; i < n; i++)
            {
                string temp = palavras[i];
                int j = i;
                // Desloca os elementos maiores para a direita
                while (j >= gap && palavras[j - gap] > temp)
                {
                    palavras[j] = palavras[j - gap];
                    j -= gap;
                }
                palavras[j] = temp;
            }
        }
        double tempo_de_execucao = (double(clock() - inicio) / CLOCKS_PER_SEC)*1000;
        return tempo_de_execucao;
    }

    double heap_sort(char arquivo[])
    {
        vector<string> palavras = ler_texto(arquivo);
        auto inicio = clock();
        int n = palavras.size();
        // Organiza o vetor em um Max-Heap
        auto heapify = [&](int tamanho, int raiz)
        {
            while (true)
            {
                int maior = raiz;
                int esquerda = 2 * raiz + 1;
                int direita = 2 * raiz + 2;
                // Verifica se o filho esquerdo é maior
                if (esquerda < tamanho && palavras[esquerda] > palavras[maior])
                {
                    maior = esquerda;
                }
                // Verifica se o filho direito é maior
                if (direita < tamanho && palavras[direita] > palavras[maior])
                {
                    maior = direita;
                }
                // Se a raiz já for o maior, encerra
                if (maior == raiz)
                    break;
                swap(palavras[raiz], palavras[maior]);
                // Continua ajustando a subárvore
                raiz = maior;
            }
        };
        // Constrói o Max-Heap
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(n, i);
        }
        // Extrai o maior elemento e reorganiza o Heap
        for (int i = n - 1; i > 0; i--)
        {
            swap(palavras[0], palavras[i]);
            heapify(i, 0);
        }
        double tempo_de_execucao = (double(clock() - inicio) / CLOCKS_PER_SEC)*1000;
        return tempo_de_execucao;
    }

    void merge(vector<string> &palavras,
               int inicio,
               int meio,
               int fim)
    {

        int tamanho_esquerda = meio - inicio + 1;
        int tamanho_direita = fim - meio;

        vector<string> esquerda(tamanho_esquerda);
        vector<string> direita(tamanho_direita);

        // Copia os elementos da metade esquerda
        for (int i = 0; i < tamanho_esquerda; i++)
        {
            esquerda[i] = palavras[inicio + i];
        }

        // Copia os elementos da metade direita
        for (int i = 0; i < tamanho_direita; i++)
        {
            direita[i] = palavras[meio + 1 + i];
        }

        int i = 0;
        int j = 0;
        int k = inicio;

        // Compara os elementos dos dois vetores
        // e os coloca em ordem no vetor original
        while (i < tamanho_esquerda &&
               j < tamanho_direita)
        {

            if (esquerda[i] <= direita[j])
            {

                palavras[k] = esquerda[i];
                i++;
            }
            else
            {

                palavras[k] = direita[j];
                j++;
            }

            k++;
        }

        // Copia os elementos restantes da esquerda
        while (i < tamanho_esquerda)
        {

            palavras[k] = esquerda[i];

            i++;
            k++;
        }

        // Copia os elementos restantes da direita
        while (j < tamanho_direita)
        {

            palavras[k] = direita[j];

            j++;
            k++;
        }
    }

    void merge_sort_recursivo(vector<string> &palavras,
                              int inicio,
                              int fim)
    {

        if (inicio < fim)
        {

            int meio = inicio + (fim - inicio) / 2;

            // Ordena a metade esquerda
            merge_sort_recursivo(
                palavras,
                inicio,
                meio);

            // Ordena a metade direita
            merge_sort_recursivo(
                palavras,
                meio + 1,
                fim);

            // Junta as duas metades
            merge(
                palavras,
                inicio,
                meio,
                fim);
        }
    }

    double merge_sort(char arquivo[])
    {

        vector<string> palavras = ler_texto(arquivo);

        auto inicio = clock();

        int n = palavras.size();

        if (n > 1)
        {
            merge_sort_recursivo(
                palavras,
                0,
                n - 1);
        }

        double tempo_de_execucao =
            (double(clock() - inicio) / CLOCKS_PER_SEC) * 1000;

        return tempo_de_execucao;
    }

    // QUICK SORT

    int mediana_de_tres(vector<string> &palavras,
                        int inicio,
                        int fim)
    {

        int meio = inicio + (fim - inicio) / 2;

        if (palavras[inicio] > palavras[meio])
        {
            swap(palavras[inicio], palavras[meio]);
        }

        if (palavras[inicio] > palavras[fim])
        {
            swap(palavras[inicio], palavras[fim]);
        }

        if (palavras[meio] > palavras[fim])
        {
            swap(palavras[meio], palavras[fim]);
        }

        // A mediana está agora na posição "meio"
        return meio;
    }

    int particionar(vector<string> &palavras,
                    int inicio,
                    int fim)
    {

        // Encontra a mediana entre
        // primeiro, meio e último
        int indice_pivo =
            mediana_de_tres(palavras, inicio, fim);

        swap(palavras[indice_pivo], palavras[fim]);

        string pivo = palavras[fim];

        int i = inicio - 1;

        for (int j = inicio; j < fim; j++)
        {

            if (palavras[j] <= pivo)
            {

                i++;

                swap(
                    palavras[i],
                    palavras[j]);
            }
        }

        // Coloca o pivô em sua posição definitiva.
        swap(
            palavras[i + 1],
            palavras[fim]);

        return i + 1;
    }

    void quick_sort_recursivo(vector<string> &palavras,
                              int inicio,
                              int fim)
    {

        if (inicio < fim)
        {

            int posicao_pivo =
                particionar(
                    palavras,
                    inicio,
                    fim);

            // Ordena os elementos menores que o pivô
            quick_sort_recursivo(
                palavras,
                inicio,
                posicao_pivo - 1);

            // Ordena os elementos maiores que o pivô
            quick_sort_recursivo(
                palavras,
                posicao_pivo + 1,
                fim);
        }
    }

    double quick_sort(char arquivo[])
    {

        vector<string> palavras = ler_texto(arquivo);

        auto inicio = clock();

        int n = palavras.size();

        if (n > 1)
        {

            quick_sort_recursivo(
                palavras,
                0,
                n - 1);
        }

        double tempo_de_execucao =
            (double(clock() - inicio) / CLOCKS_PER_SEC) * 1000;

        return tempo_de_execucao;
    }
}

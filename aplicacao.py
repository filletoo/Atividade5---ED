import re
from ctypes import *
import matplotlib.pyplot as plt
import numpy as np

#funcoes em c++
algoritmos = CDLL("algoritmos.dll", winmode=0)

algoritmos.bubble_sort.argtypes = [c_char_p]
algoritmos.bubble_sort.restype = c_double

algoritmos.selection_sort.argtypes = [c_char_p]
algoritmos.selection_sort.restype = c_double

algoritmos.insertion_sort.argtypes = [c_char_p]
algoritmos.insertion_sort.restype = c_double

algoritmos.shell_sort.argtypes = [c_char_p]
algoritmos.shell_sort.restype = c_double

algoritmos.heap_sort.argtypes = [c_char_p]
algoritmos.heap_sort.restype = c_double

algoritmos.merge_sort.argtypes = [c_char_p]
algoritmos.merge_sort.restype = c_double

algoritmos.quick_sort.argtypes = [c_char_p]
algoritmos.quick_sort.restype = c_double

###############################

def pre_processamento(texto):
    texto = texto.lower()
    texto = re.split(r"[,.;:/*&#@$!()%0123456789\n\- ]+", texto)

    return texto

def ler_palavras(arquivo):
    with open(arquivo, mode="r", encoding="utf-8") as f:
        texto = f.read()

    return texto

def executar_ordenacoes_1_grupo(arquivo, tempos):
    pre_processado = arquivo[:-4] + "_pre_processados.txt"
    tempo_medio = 0
    arq = c_char_p(pre_processado.encode())

    for _ in range(5):
        tempo_medio += algoritmos.insertion_sort(arq)
        #print(tempo_medio)
    tempos[arquivo]['insertion_sort'] = tempo_medio/5
    
    tempo_medio = 0
    for _ in range(5):
        tempo_medio += algoritmos.selection_sort(arq)
    tempos[arquivo]['selection_sort'] = tempo_medio/5
    
    tempo_medio = 0
    for _ in range(5):
        tempo_medio += algoritmos.bubble_sort(arq)
    tempos[arquivo]['bubble_sort'] = tempo_medio/5
    
def executar_ordenacoes_2_grupo(arquivo, tempos):
    pre_processado = arquivo[:-4] + "_pre_processados.txt"
    arq = c_char_p(pre_processado.encode())

    tempo_medio = 0
    for _ in range(5):
        tempo_medio += algoritmos.shell_sort(arq)
    tempos[arquivo]['shell_sort'] = tempo_medio/5

    tempo_medio = 0
    for _ in range(5):
        tempo_medio += algoritmos.heap_sort(arq)
    tempos[arquivo]['heap_sort'] = tempo_medio/5

    tempo_medio = 0
    for _ in range(5):
        tempo_medio += algoritmos.merge_sort(arq)
    tempos[arquivo]['merge_sort'] = tempo_medio/5

    tempo_medio = 0
    for _ in range(5):
        tempo_medio += algoritmos.quick_sort(arq)
    tempos[arquivo]['quick_sort'] = tempo_medio/5

def gerar_grafico(arquivos, tempos, nomes_funcoes):
    texto_250k = []
    texto_500k = []
    texto_1m = []

    for i in range(len(nomes_funcoes)):
        texto_250k.append(tempos[arquivos[0]][nomes_funcoes[i]])

        texto_500k.append(tempos[arquivos[1]][nomes_funcoes[i]])

        texto_1m.append(tempos[arquivos[2]][nomes_funcoes[i]])

    barWidth = 0.25
    plt.figure(figsize=(10,5))

    # Definindo a posição das barras
    r1 = np.arange(len(texto_250k))
    r2 = [x + barWidth for x in r1]
    r3 = [x + barWidth for x in r2]
    
    barras_250k = plt.bar(r1, texto_250k, color='#6A5ACD', width=barWidth, edgecolor='black',label=arquivos[0])
    barras_500k = plt.bar(r2, texto_500k, color='#6495ED', width=barWidth, edgecolor='black',label=arquivos[1])
    barras_1m = plt.bar(r3, texto_1m, color='#00BFFF', width=barWidth, edgecolor='black',label=arquivos[2])

    plt.bar_label(barras_250k, padding=3, fontsize=10)
    plt.bar_label(barras_500k, padding=3, fontsize=10)
    plt.bar_label(barras_1m, padding=3, fontsize=10)

    plt.xlim(-0.5)

    plt.tick_params(axis='y', labelsize=7)

    plt.xlabel('Algoritmos')
    plt.xticks([r + barWidth for r in range(len(texto_250k))], nomes_funcoes)
    plt.grid(axis='y', linestyle=':', alpha=0.6, color='gray')

def gerar_grafico_1_grupo(arquivos, tempos, nomes_funcoes):
    gerar_grafico(arquivos, tempos, nomes_funcoes)
    plt.ylabel('Tempo (s)')
    plt.title('Algoritmos de complexidade do tipo O(n^2)')
    plt.legend()
    plt.show()

'''
def gerar_grafico_2_grupo(arquivos, tempos, nomes_funcoes):
    plt.figure(2)
    gerar_grafico(arquivos, tempos, nomes_funcoes)
    plt.ylabel('Tempo (ms)')
    plt.title('Algoritmos de complexidade do tipo O(n*logn)')
    plt.legend()
    plt.show()
'''

if __name__ == '__main__':

    menu = '''\n----------------------------------------------
1 - Pré-processar textos
2 - Executar algoritmos de ordenação
3 - Gerar gráificos
4 - Sair
----------------------------------------------
Opção: '''

    arquivos = ["nomes250k.txt", "nomes500.txt", "nomes1m.txt"]
    #pra poder fazer o exemplo
    #arquivos = ["nomes5k.txt", "nomes10k.txt", "nomes20k.txt"]
    
    tempos = {}
    for i in range(3):
        tempos[arquivos[i]] = {}
    
    ordenacao_feita = False
    pre_processamento_feito = False

    while True:
        opcao = input(menu)

        if opcao == '1':
            for i in range(3):
                print(f"\n{arquivos[i]}:")

                texto = ler_palavras(arquivos[i])
                print(f"Quantidade de palavras antes de pré-processar: {len(texto.split('\n')) - 1}")
                
                texto_pre_processado = pre_processamento(texto)
                print(f"Quantidade de palavras depois de pré-processar: {len(texto_pre_processado) - 1}")
                
                with open(arquivos[i][:-4] + "_pre_processados.txt", mode="w", encoding="utf-8") as f:
                    for p in texto_pre_processado:
                        f.write(p + '\n')

            pre_processamento_feito = True
        
        elif opcao == '2' and pre_processamento_feito:
            for i in range(3):
                executar_ordenacoes_1_grupo(arquivos[i], tempos)
                #executar_ordenacoes_2_grupo(arquivos[i], tempos)
            print("Algoritmos executados.")
            ordenacao_feita = True

        elif opcao == '2': 
            print("Execute o pré-processamento primeiro")

        elif opcao == '3' and ordenacao_feita:
            gerar_grafico_1_grupo(arquivos, tempos, ['selection_sort', 'insertion_sort', 'bubble_sort'])
            #gerar_grafico_2_grupo(arquivos, tempos, ['shell_sort', 'heap_sort', 'merge_sort', 'quick_sort'])

        elif opcao == '3':
            print("Ordene os arquivos primeiros")

        elif opcao == '4':
            break

        else:
            print("Opção inválida")
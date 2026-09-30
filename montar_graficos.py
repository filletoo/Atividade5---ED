import numpy as np
import matplotlib.pyplot as plt

# Um gráfico com a renda média por faixa etária será nosso Hello World, vamos definir alguns valores fictícios

texto_250k = [1450.45, 2561.75, 4389.9]
texto_500k  = [6275.4, 10195.2, 23314.4]
texto_1m = [25919, 41994.9, 97733.7]

barWidth = 0.25
# Aumentando o gráfico
fig, ax = plt.subplots()
plt.figure(figsize=(10,5))

# Definindo a posição das barras
r1 = np.arange(len(texto_250k))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]
 
# Criando as barras
barras_250k = plt.bar(r1, texto_250k, color='#6A5ACD', width=barWidth, edgecolor='black',label='250k')
barras_500k = plt.bar(r2, texto_500k, color='#6495ED', width=barWidth, edgecolor='black',label='500k')
barras_1m = plt.bar(r3, texto_1m, color='#00BFFF', width=barWidth, edgecolor='black',label='1m')

plt.bar_label(barras_250k, padding=3, fontsize=10)
plt.bar_label(barras_500k, padding=3, fontsize=10)
plt.bar_label(barras_1m, padding=3, fontsize=10)

plt.xlim(-0.5)

plt.tick_params(axis='y', labelsize=7)
# Adiciando legendas as barras
plt.xlabel('Algoritmos')
plt.xticks([r + barWidth for r in range(len(texto_250k))], ['selection_sort', 'insertion_sort', 'bubble_sort'])
plt.ylabel('Tempo (s)')
plt.title('Algoritmos de complexidade do tipo O(n^2)')

# Criando a legenda e exibindo o gráfico
plt.legend()
plt.grid(axis='y', linestyle=':', alpha=0.6, color='gray')
plt.show()

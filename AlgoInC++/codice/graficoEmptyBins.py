import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Imposta le dimensioni generali del testo
plt.rcParams.update({'font.size': 14})  # Aumenta la dimensione generale del font

# Verifica che ci siano 2 argomenti (k e n)
if len(sys.argv) != 3:
    print("ERRORE Usa: python3 graficoTempo.py k n")
    sys.exit(1)

param_1 = sys.argv[1] # valore di k fissato
param_2 = sys.argv[2] # valore di n fissato

# file da leggere

filename = 'emptyBins_results_k='+param_1+'_n='+param_2+'.csv'
x_label = 'Numero di elementi nel Set'
dim_column = 'Numero di elementi nel Set'
output_image = 'grafico_emptyBins_k='+param_1+'_n='+param_2+'.png'  # Nome del file di output per n

# Leggi il file CSV
df = pd.read_csv(filename, sep=';')

# Calcola la media dei tempi per ogni combinazione di algoritmo e dimensione
mean_times = df.groupby(['Algoritmo', dim_column])['Numero di Bins'].mean().reset_index()

# Crea il grafico 12x8 pollici
plt.figure(figsize=(12, 8))

# Definisce i colori per algoritmo
colors = {'OPH_SENZA_ROT': 'green'}

for algo in mean_times['Algoritmo'].unique():
    # Filtra i dati per l'algoritmo corrente
    algo_data = mean_times[mean_times['Algoritmo'] == algo]
    algo_data = algo_data.sort_values(dim_column)

    # Usa l'indice come x (0, 1, 2, ...) per spacing lineare
    x = range(len(algo_data))
    y = algo_data['Numero di Bins']
    
    # Plotta i punti e la linea che li collega
    plt.scatter(x, y, color=colors[algo], label=f'{algo}', alpha=0.6)
    plt.plot(x, y, color=colors[algo], alpha=0.8)

# # Imposta scala logaritmica per l'asse y
# plt.yscale('log')

# # Personalizza l'asse x per mostrare le potenze di 2
# plt.xticks(range(len(mean_times[dim_column].unique())),
#            [f'2^{int(np.log2(x))}' for x in sorted(mean_times[dim_column].unique())],
#            rotation=45)

plt.xlabel(x_label)
plt.ylabel('Numero di Bins')
plt.title(f'Variazione degli Empty-Bin rispetto agli elementi inseriti, con k= '+param_1+' e |Set|='+param_2)
plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()

plt.savefig(output_image)
plt.close()

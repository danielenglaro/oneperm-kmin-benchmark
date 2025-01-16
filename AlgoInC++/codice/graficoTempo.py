import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Verifica che sia stato fornito un parametro
if len(sys.argv) != 2 or sys.argv[1] not in ['n', 'k']:
    print("Uso: python3 graficoTempo.py [n|k]")
    sys.exit(1)

# Ottieni il parametro
param = sys.argv[1]

# Determina il file da leggere e le etichette appropriate
if param == 'n':
    filename = 'time_results_n.csv'
    x_label = 'Dimensione (n)'
    dim_column = 'Dimensione (n)'
    output_image = 'grafico_tempo_n.png'  # Nome del file di output per n
else:  # param == 'k'
    filename = 'time_results_k.csv'
    x_label = 'Numero di funzioni hash (k)'
    dim_column = 'Dimensione (k)'
    output_image = 'grafico_tempo_k.png'  # Nome del file di output per k

# Leggi il file CSV
df = pd.read_csv(filename, sep=';')

# Calcola la media dei tempi per ogni combinazione di algoritmo e dimensione
mean_times = df.groupby(['Algoritmo', dim_column])['Tempo di esecuzione'].mean().reset_index()

# Crea il grafico
plt.figure(figsize=(12, 8))

# Colori per ogni algoritmo
colors = {'KMH': 'blue', 'OPH': 'red', 'FSS': 'green'}

# Per ogni algoritmo
for algo in mean_times['Algoritmo'].unique():
    # Filtra i dati per l'algoritmo corrente
    algo_data = mean_times[mean_times['Algoritmo'] == algo]

    # Ordina i dati per dimensione
    algo_data = algo_data.sort_values(dim_column)

    # Usa l'indice come x (0, 1, 2, ...) per spacing lineare
    x = range(len(algo_data))
    y = algo_data['Tempo di esecuzione']

    # Plotta i punti e la linea che li collega
    plt.scatter(x, y, color=colors[algo], label=f'{algo}', alpha=0.6)
    plt.plot(x, y, color=colors[algo], alpha=0.8)

# Imposta scala logaritmica per l'asse y
plt.yscale('log')

# Personalizza l'asse x per mostrare le potenze di 2
plt.xticks(range(len(mean_times[dim_column].unique())),
           [f'2^{int(np.log2(x))}' for x in sorted(mean_times[dim_column].unique())],
           rotation=45)

# Personalizza il grafico
plt.xlabel(x_label)
plt.ylabel('Tempo di esecuzione (microsecondi)')
plt.title(f'Confronto delle prestazioni degli algoritmi in funzione di {param}')
plt.grid(True, alpha=0.3)
plt.legend()

# Aggiusta i margini per evitare il taglio delle etichette
plt.tight_layout()

# Salva il grafico come file immagine invece di mostrarlo
plt.savefig(output_image)
plt.close()  # Chiude la figura per liberare memoria
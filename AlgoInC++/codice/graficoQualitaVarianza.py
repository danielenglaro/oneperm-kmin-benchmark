import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Leggi il file CSV
df = pd.read_csv('quality_results.csv', sep=';')

# Calcola la media e la varianza (RMSE) per ogni combinazione di algoritmo e Jaccard_reale
rmse_data = df.groupby(['Algoritmo', 'Jaccard_reale', 'K'])['Jaccard_stimata'].agg(
    mean='mean',
    std='std'
).reset_index()

# Crea il grafico
plt.figure(figsize=(10, 6))

# Definisce i colori e gli stili per ogni algoritmo
styles = {
    'KMH': {'color': 'blue', 'marker': 'o', 'label': 'KMH'},
    'OPH': {'color': 'red', 'marker': 'x', 'label': 'OPH'},
    'FSS': {'color': 'black', 'marker': 's', 'label': 'FSS'}
}

# Plotta i dati per ogni algoritmo
for algo in rmse_data['Algoritmo'].unique():
    algo_data = rmse_data[rmse_data['Algoritmo'] == algo]
    x = algo_data['Jaccard_reale']
    y = algo_data['mean']
    yerr = algo_data['std']

    # Linea con barra di errore
    plt.errorbar(x, y, yerr=yerr, fmt=styles[algo]['marker'], color=styles[algo]['color'],
                 label=styles[algo]['label'], capsize=3, alpha=0.8)

# Personalizza il grafico
plt.xlabel('Jaccard Similarity', fontsize=12)
plt.ylabel('RMSE', fontsize=12)
plt.title('RMSE con Varianza per Algoritmo', fontsize=14)
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

# Salva il grafico
plt.savefig('rmse_variance_plot.png')
plt.show()
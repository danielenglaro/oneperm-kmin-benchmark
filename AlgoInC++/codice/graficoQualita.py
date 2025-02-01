import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Verifica che ci sia un argomento e che sia valido (k)
if len(sys.argv) != 2:
    print("Uso: python3 graficoQualita.py [k]")
    sys.exit(1)

k_value = int(sys.argv[1])  # Valore di k fissato

# Determina il file da leggere
filename = 'quality_results.csv'
output_image = f'grafico_qualita_k={k_value}.png'  # Nome del file di output

# Leggi il file CSV
df = pd.read_csv(filename, sep=';')

# Filtra i dati per il valore di k specificato
df_k = df[df['K'] == k_value]

# Calcola la media degli errori RMSE per ogni valore di Jaccard
mean_rmse = df_k.groupby('Jaccard_reale')['Jaccard_stimata'].apply(lambda x: np.sqrt(np.mean((x - df_k['Jaccard_reale'])**2))).reset_index()
mean_rmse.columns = ['Jaccard_reale', 'RMSE']

# Crea il grafico 12x8 pollici
plt.figure(figsize=(12, 8))

# Definisce i colori per ogni algoritmo
colors = {'KMH': 'blue', 'OPH': 'red', 'FSS': 'green'}

# Plotta i dati per ogni algoritmo
for algoritmo in df_k['Algoritmo'].unique():
    algo_data = df_k[df_k['Algoritmo'] == algoritmo]
    mean_rmse_algo = algo_data.groupby('Jaccard_reale')['Jaccard_stimata'].apply(lambda x: np.sqrt(np.mean((x - algo_data['Jaccard_reale'])**2))).reset_index()
    plt.plot(mean_rmse_algo['Jaccard_reale'], mean_rmse_algo['RMSE'], label=algoritmo, color=colors[algoritmo])

# Personalizza il grafico
plt.xlabel('Jaccard Similarity Reale')
plt.ylabel('RMSE')
plt.title(f'Errore RMSE rispetto alla Jaccard Similarity per k={k_value}')
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

# Salva il grafico
plt.savefig(output_image)
plt.close()
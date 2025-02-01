import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# Leggi il file CSV
df = pd.read_csv('quality_results.csv', sep=';')

# Calcola RMSE per ogni combinazione di K, Jaccard_reale e Algoritmo
def calculate_rmse(group):
    return np.sqrt(np.mean((group['Jaccard_stimata'] - group['Jaccard_reale'])**2))

# Per ogni algoritmo, crea una heatmap separata
for algoritmo in df['Algoritmo'].unique():
    # Filtra i dati per l'algoritmo corrente
    algo_data = df[df['Algoritmo'] == algoritmo]

    # Calcola RMSE per ogni combinazione di K e Jaccard_reale
    rmse_data = algo_data.groupby(['Jaccard_reale', 'K'])['Jaccard_stimata'].apply(
        lambda x: np.sqrt(np.mean((x - x.name[0])**2))
    ).reset_index()

    # Crea una matrice pivot per la heatmap
    pivot_table = rmse_data.pivot(index='Jaccard_reale', columns='K', values='Jaccard_stimata')

    # Crea la figura
    plt.figure(figsize=(16, 12))  # Aumenta la dimensione della figura

    # Crea la heatmap
    sns.heatmap(pivot_table,
                cmap='RdYlGn_r',
                annot=True,
                fmt='.3f',
                cbar_kws={'label': 'RMSE'},
                yticklabels=[f'{x:.2f}' for x in pivot_table.index])  # Mostra i valori reali di Jaccard_reale

    # Personalizza il grafico
    plt.title(f'RMSE per {algoritmo}', pad=20)
    plt.ylabel('Jaccard Similarity Reale', labelpad=10)
    plt.xlabel('K (numero di hash)', labelpad=10)

    # Aumenta la dimensione dei font
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12, rotation=0)  # Mantieni le etichette y dritte

    # Aggiusta il layout
    plt.tight_layout()

    # Salva il grafico
    plt.savefig(f'heatmap_quality_{algoritmo}.png', bbox_inches='tight', dpi=300)
    plt.close()

print("Grafici generati con successo!")
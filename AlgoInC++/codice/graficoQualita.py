import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Imposta le dimensioni generali del testo
plt.rcParams.update({'font.size': 14})  # Aumenta la dimensione generale del font

# Verifica che ci sia un argomento e che sia valido (k)
if len(sys.argv) != 3:
    print("ERRORE USA: python3 graficoQualita.py [k] [n]")
    sys.exit(1)

# Estrai il valore di k dalla riga di comando
k_value = int(sys.argv[1])  # Valore di k fissato
n_value = int(sys.argv[2]) # Valore di n fissato

# Determina il file da leggere
filename = 'quality_results_k=' + str(k_value) +'_n=' + str(n_value) + '.csv'  # Modificato per includere k nel nome del file
output_image = f'grafico_qualita_k={k_value}_n={n_value}.png'  # Nome del file di output

# Leggi il file CSV
df = pd.read_csv(filename, sep=';')

# Verifica se ci sono dati per il valore di k specificato
if df.empty:
    print(f"Nessun dato trovato per k={k_value}.")
    sys.exit(1)

# Definisce i colori per ogni algoritmo
colors = {'KMH': 'red', 'OPH': 'green', 'OPH_ROT': 'blue'}

# Crea il grafico 12x8 pollici
plt.figure(figsize=(12, 8))

# Plotta i dati per ogni algoritmo
for algoritmo in df['Algoritmo'].unique():
    algo_data = df[df['Algoritmo'] == algoritmo]

    # Calcola la media degli errori RMSE per ogni valore di Jaccard
    mean_rmse = (algo_data.groupby('Jaccard_reale')
                .agg(RMSE=('Jaccard_stimata', lambda x: np.sqrt(np.mean((algo_data.loc[x.index, 'Jaccard_reale'] - x)**2))))
                .reset_index())

    variance_rmse = (algo_data.groupby('Jaccard_reale')
                    .agg(Variance=('Jaccard_stimata', lambda x: np.var(np.sqrt((algo_data.loc[x.index, 'Jaccard_reale'] - x)**2))))
                    .reset_index())

    # Plotta la curva per l'algoritmo corrente
    plt.plot(mean_rmse['Jaccard_reale'], mean_rmse['RMSE'], label=algoritmo, color=colors[algoritmo])

    # Aggiungi l'area sfumata per la varianza
    plt.fill_between(mean_rmse['Jaccard_reale'],
                     mean_rmse['RMSE'] - np.sqrt(variance_rmse['Variance']),
                     mean_rmse['RMSE'] + np.sqrt(variance_rmse['Variance']),
                     color=colors[algoritmo], alpha=0.2)

# Personalizza il grafico
plt.xlabel('Jaccard Similarity Reale')
plt.ylabel('RMSE')
plt.title(f'RMSE rispetto alla Jaccard Similarity Reale per k= {k_value} e |S1 U S2|= {n_value}')
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

# Salva il grafico
plt.savefig(output_image)
plt.close()

print(f"Grafico salvato come {output_image}.")
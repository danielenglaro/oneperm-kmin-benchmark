# READ ME
Questo repository contiene l'implementazione degli algoritmi K-MinHash e One-Permutation Hashing, utilizzati per la stima della similarità di Jaccard. Include anche test sulle prestazioni relative al tempo di esecuzione e alla qualità degli algoritmi.

## Struttura del repository
- `src/`: contiene tutto il codice sorgente del progetto.
- `src/KMinHash.h` e `src/KMinHash.cpp`: implementazione dell'algoritmo K-MinHash.
- `src/OnePermutation.h` e `src/OnePermutation.cpp`: implementazione dell'algoritmo One-Permutation Hashing.
- `src/HashFunction.h` e `src/HashFunction.cpp`: implementazione delle funzioni hash utilizzate.
- `src/Prime.h` e `src/Prime.cpp`: metodi per la generazione di numeri primi utili nell'hashing.
- `src/JS.h` e `src/JS.cpp`: calcolo della similarità di Jaccard, sia esatta che approssimata.
- `src/Test.h` e `src/Test.cpp`: test sulle prestazioni e sulla qualità degli algoritmi.
- `src/LettoreFile.h` e `src/LettoreFile.cpp`: lettura di insiemi da file per testare gli algoritmi.
- `src/StampaVettore.h` e `src/StampaVettore.cpp`: funzioni di utility per la stampa dei vettori.
- `main.cpp`: permette di eseguire i test e gli esperimenti sugli algoritmi implementati.

## Compilazione
Per compilare il progetto, eseguire il seguente comando:
```bash
 g++ -Wall -Wextra -std=c++23 -O2 *.cpp
```

Esecuzione dei test
Dopo la compilazione, è possibile eseguire i test utilizzando:
```bash
 ./a.out <modalità>
```

Dove <modalità> può assumere i seguenti valori:
- 0: Testa il tempo di esecuzione con k fissato.
- 1: Testa il tempo di esecuzione con n fissato.
- 2: Esegue tutti i test sul tempo.
- 3: Testa la qualità della stima della similarità di Jaccard.
- 4: Testa il numero di bin vuoti nell'algoritmo One-Permutation Hashing.
- 5: Esegue tutti i test.
- 6: Genera solo i grafici senza eseguire i test.

### Dataset
Il progetto utilizza dataset generati tramite script Python per testare la qualità delle stime. I file vengono letti e analizzati per confrontare la similarità esatta con quella stimata dagli algoritmi implementati.

### Risultati
I risultati dei test vengono salvati in file CSV e possono essere visualizzati tramite script Python dedicati per la generazione dei grafici.


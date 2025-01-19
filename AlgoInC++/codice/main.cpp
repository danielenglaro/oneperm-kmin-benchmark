#include <iostream>
// #include "KMinHash.h"
// #include "OnePermutation.h"
// #include "FastSimilaritySketching.h"
#include "Test.h"
#include "Prime.h"

int main()
{
    // Imposta il modulo dell'universo come il primo numero primo maggiore o uguale a 2^30
    size_t m = Prime::nextPrime(1073741824);

    // Vettore per memorizzare le potenze di 2 per la dimensione n
    std::vector<int> n_range;

    // Ciclo per generare le potenze di 2 fino a 2^17
    for (int i = 1; i <= 131072; i *= 2)
    {
        n_range.push_back(i);
    }

    // Vettore per memorizzare le potenze di 2 per il numero di funzioni hash k
    std::vector<int> k_range;

    // Ciclo per generare le potenze di 2 fino a 2^11
    for (int i = 1; i <= 1024; i *= 2)
    {
        k_range.push_back(i);
    }

    // // Esegui il test per analizzare il tempo in funzione di n
    // Test::test_time_vs_n(1000, n_range, 100, m);

    // // Esegui lo script Python per generare il grafico dei tempi in funzione di n
    // system("./venv/bin/python3 graficoTempo.py n");

    // system("open grafico_tempo_n.png");

    // // Esegui il test per analizzare il tempo in funzione di k
    // Test::test_time_vs_k(k_range, 50000, 100, m);

    // // Esegui lo script Python per generare il grafico dei tempi in funzione di k
    // system("./venv/bin/python3 graficoTempo.py k");

    // system("open grafico_tempo_k.png");

    //prossimi test k 1024 n rep 100
    Test::test_quality(k_range, 50000, 100, m);
    system("./venv/bin/python3 graficoQualita.py n");

    system("open heatmap_quality_KMH.png");
    system("open heatmap_quality_OPH.png");
    system("open heatmap_quality_FSS.png");
}
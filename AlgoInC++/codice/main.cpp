#include <iostream>
// #include "KMinHash.h"
// #include "OnePermutation.h"
// #include "FastSimilaritySketching.h"
#include "Test.h"


int main()
{
    // Imposta il modulo dell'universo come il primo numero primo maggiore o uguale a 2^30
    size_t m = 1073741824;

    //imposta ripetizioni esperimenti
    int rep = 100;


    // ---- TEST per analizzare il tempo al variare di n ----
    std::vector<int> n_range;
    for (int i = 1; i <= 131072; i *= 2) n_range.push_back(i); // n range || Ciclo per generare le potenze di 2 fino a 2^17

    std::vector<int> vettore_k_fissato = {16, 256, 4096, 65536}; // k fissato a salti di 2^4
    for(int k_fissato : vettore_k_fissato){
        Test::test_time_vs_n(k_fissato, n_range, rep, m);

        // Esegui lo script Python per generare il grafico dei tempi in funzione di n
        system( ("./venv/bin/python3 graficoTempo.py n " + std::to_string(k_fissato)).c_str() );

        // system( ("open grafico_tempo_k=" + std::to_string(k_fissato) + ".png").c_str() );
    }


    // ---- TEST per analizzare il tempo in funzione di k ----
    std::vector<int> k_range;
    for (int i = 1; i <= 4096; i *= 2) k_range.push_back(i); // k range || Ciclo per generare le potenze di 2 fino a 2^12

    std::vector<int> vettore_n_fissato = {100, 1000, 10000, 100000}; // n fissato potenze di 10 da 10^2
    for(int n_fissato : vettore_n_fissato){
        Test::test_time_vs_k(k_range, n_fissato, rep, m);

        // // Esegui lo script Python per generare il grafico dei tempi in funzione di k
        system( ("./venv/bin/python3 graficoTempo.py k " + std::to_string(n_fissato)).c_str() );

        // system( ("open grafico_tempo_n=" + std::to_string(n_fissato) + ".png").c_str() );
    }


    //prossimi test k 1024 n rep 100
    Test::test_quality(vettore_k_fissato, 50000, rep, m);
    system("./venv/bin/python3 graficoQualita.py n");

    // system("open heatmap_quality_KMH.png");
    // system("open heatmap_quality_OPH.png");
    // system("open heatmap_quality_FSS.png");

}
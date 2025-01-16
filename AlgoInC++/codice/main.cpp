#include <iostream>
#include "LettoreFile.h"
#include "StampaVettore.h"
#include "JS.h"
// #include "KMinHash.h"
// #include "OnePermutation.h"
// #include "FastSimilaritySketching.h"
#include "Test.h"
#include "Prime.h"
#include <ctime>


int main()
{
    // size_t k = 1000;         // Numero di funzioni hash
    size_t m = Prime::nextPrime(  1073741824  );         // Modulo dell'universo (2^32 = 4294967296) ()
    // std::string filename = argv[4];        // Nome del file passato come argomento
    

    // std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> coppie;
    // LettoreFile::read(filename, coppie);

    std::vector<int> n_range, k_range; // potenze di 2, partendo da 2^10 
    for(int i = 1; i <= 512; i *= 2) { // 131072 potenza di 2 maggiore di 100 000
        n_range.push_back(i);
        k_range.push_back(i);
    }

    Test::test_time_vs_n(500, n_range, 10, m); //ripetizioni anche 100 o 1000
    system("./venv/bin/python3 graficoTempo.py n"); // Esegui lo script Python per generare il grafico in funzione di n
    system("open grafico_tempo_n.png");  // Per macOS
    // system("start grafico_n.png");     // Per Windows
    
    Test::test_time_vs_k(k_range, 10000, 10, m);
    system("./venv/bin/python3 graficoTempo.py k"); // Esegui lo script Python per generare il grafico in funzione di k
    system("open grafico_tempo_k.png");  // Per macOS
    
    
}
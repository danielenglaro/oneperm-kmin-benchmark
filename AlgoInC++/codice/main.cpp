#include <iostream>
// #include "KMinHash.h"
// #include "OnePermutation.h"
// #include "FastSimilaritySketching.h"
#include "Test.h"


int main()
{
    // Inizio del conteggio del tempo
    auto start = std::chrono::high_resolution_clock::now();
    //----------------------------------------------CRONOMETRO----------------------------------------------

    
    // Imposta il modulo dell'universo come il primo numero primo maggiore o uguale a 2^30
    size_t m = 1073741824;

    //imposta ripetizioni esperimenti
    int rep = 100;




    // ---- TEST per analizzare il tempo al variare di n ----
    std::vector<int> n_range;
    for (int i = (1 << 10); i <= (1 << 20); i *= 2) {
        n_range.push_back(i); // n range || Ciclo per generare le potenze da 2^10 fino a 2^20

    std::vector<int> vettore_k_fissato = { 16,256,4096};// k fissato a salti di 2^4
    for(int k_fissato : vettore_k_fissato){
        Test::test_time_vs_n(k_fissato, n_range, rep, m);

        // Esegui lo script Python per generare il grafico dei tempi in funzione di n
        system( ("python3 graficoTempo.py n " + std::to_string(k_fissato)).c_str() );

        // system( ("open grafico_tempo_k=" + std::to_string(k_fissato) + ".png").c_str() );
    }




    // ---- TEST per analizzare il tempo in funzione di k ----
    std::vector<int> k_range;
    for (int i = 1; i <= 8192; i *= 2) k_range.push_back(i); // k range || Ciclo per generare le potenze di 2 fino a 2^16

    std::vector<int> vettore_n_fissato = {10000, 100000, 1000000 }; // n fissato potenze di 10 da 10^2
    for(int n_fissato : vettore_n_fissato){
        Test::test_time_vs_k(k_range, n_fissato, rep, m);

        // // Esegui lo script Python per generare il grafico dei tempi in funzione di k
        system( ("python3 graficoTempo.py k " + std::to_string(n_fissato)).c_str() );

        // system( ("open grafico_tempo_n=" + std::to_string(n_fissato) + ".png").c_str() );
    }


    
    // ---- TEST per analizzare la qualità ----
    // int n = 50000;
    // for(int k_fissato : vettore_k_fissato){
    //         Test::test_quality(k_fissato, n, rep, m);

    //         // Esegui lo script Python per generare il grafico dei tempi in funzione di n
    //         system(("python3 graficoQualita.py " + std::to_string(k_fissato)).c_str());
    //     }




// ---- Esempio di utilizzo dell'algoritmo di separazione ----
    // size_t t =  ; // Dimensione dello sketch
    // size_t r = ;  // Numero minimo di iterazioni
    // double gamma = 0.5; // Soglia di similarità

    // // Crea un'istanza di FastSimilaritySketching
    // FastSimilaritySketching fss(t, 4);

    // // Definisci due insiemi di esempio
    // std::vector<uint64_t> setA = {1, 2, 3, 4, 5, 6}; // Insieme A
    // std::vector<uint64_t> setB = {4, 5, 6};    // Insieme B

    // // Calcola le firme per gli insiemi A e B
    // std::vector<double> S_A = fss.computeSignature(setA);
    // std::vector<double> S_B = fss.computeSignature(setB);

    // // Esegui l'algoritmo di separazione
    // bool result = fss.separationProcedure(r, gamma, S_A, S_B);
    
    // // Stampa il risultato
    // std::cout << "Risultato della separazione per gli insiemi A e B: " 
    //           << (result ? "true" : "false") << std::endl;




//----------------------------------------------CRONOMETRO----------------------------------------------
    // Fine del conteggio del tempo
    auto end = std::chrono::high_resolution_clock::now();

    // Calcolo della durata
    std::chrono::duration<double> duration = end - start;

    // Stampa del tempo impiegato
    std::cout << "\nTempo impiegato: " << duration.count() << " secondi\n" << std::endl;



}
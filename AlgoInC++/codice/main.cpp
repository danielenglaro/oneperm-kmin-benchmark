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


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Utilizzo: " << argv[0] << " <k> <dimensione_m>\n";
        return 1;
    }
    size_t k = Prime::nextPrime(  std::stoi(argv[1])  );         // Numero di funzioni hash
    size_t m = Prime::nextPrime(  std::stoi(argv[2])  );         // Modulo dell'universo
    // std::string filename = argv[4];        // Nome del file passato come argomento
    

    // std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> coppie;
    // LettoreFile::read(filename, coppie);

    std::vector<int> n_range = {1000, 5000, 10000, 50000, 100000}; // potenze di 2, partendo da 2^10 
    Test::test_time_vs_n(k, n_range, 10, m); //ripetizioni anche 100 o 1000

    // std::vector<int> k_range = {7, 101, 503};
    // Test::test_time_vs_k(k_range, 100000, 10, m);
    
}
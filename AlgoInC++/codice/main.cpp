#include <iostream>
#include "LettoreFile.h"
#include "StampaVettore.h"
#include "JS.h"
#include "KMinHash.h"
#include "OnePermutation.h"
#include "FastSimilaritySketching.h"
#include <ctime>


int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        std::cerr << "Utilizzo: " << argv[0] << " <k> <dimensione_m>\n";
        return 1;
    }
    size_t k = std::stoi(argv[1]);         // Numero di funzioni hash
    size_t m = std::stoi(argv[2]);         // Modulo dell'universo
    size_t algoritmo = std::stoi(argv[3]); // Selezione algoritmo
    std::string filename = argv[4];        // Nome del file passato come argomento
    size_t seed;
    int seed_input = std::stoi(argv[5]);
    if (seed_input == -1)
    {
        seed = time(NULL); // Seed random
    }
    else
    {
        seed = seed_input;
    }

    std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> coppie;
    LettoreFile::read(filename, coppie);
    // for (auto &coppia : coppie)
    // {

    std::vector<uint64_t> set1;
    // set1 = coppia.first;
    for (size_t i = 0; i < 100; i++)
    {
        set1.push_back(i);
    }

    std::vector<uint64_t> set2; // = coppia.second;
    for (size_t i = 50; i < 150; i++)
    {
        set2.push_back(i);
    }

    // std::cout << "Set_1: ";
    // // StampaVettore::printVector(set1);
    // std::cout << "Set_2:";
    // StampaVettore::printVector(set2);
    std::vector<double> firma1, firma2;

    if (algoritmo == 0) // Calcolo k-minHash
    {
        KMinHash kMinHash(k, m, seed);
        firma1 = kMinHash.computeSignature(set1);
        firma2 = kMinHash.computeSignature(set2);
    }

    else if (algoritmo == 1) // Calcolo One Perm
    {
        OnePermutation oph(k, m, seed);
        firma1 = oph.computeSignature(set1);
        firma2 = oph.computeSignature(set2);
    }

    else if (algoritmo >= 2) // Calcolo FastSimilaritySketching
    {
        FastSimilaritySketching fss(k, m, seed);
        firma1 = fss.computeSignature(set1);
        firma2 = fss.computeSignature(set2);
    }

    // Stampa Firme
    // std::cout << "Firma Set_1: ";
    // // StampaVettore::printVector(firma1);
    // std::cout << "Firma Set_2: ";
    // StampaVettore::printVector(firma2);

    // Calcolo della Jaccard Similarity approssimata
    float approxJaccard = JS::approx(firma1, firma2, k);
    std::cout << "Approximate Jaccard Similarity: " << approxJaccard << "\n";

    // Calcolo della Jaccard Similarity esatta
    float exactJaccard = JS::esatta(set1, set2);
    std::cout << "Exact Jaccard Similarity: " << exactJaccard << "\n";
    std::cout << "\n";
    // }

    return 0;
}
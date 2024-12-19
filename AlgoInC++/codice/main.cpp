#include <iostream>
#include <vector>
#include <algorithm>
//#include "KMinHash.h"
//#include "OnePermutation.h"
#include "FastSimilaritySketching.h"
#include <fstream>
#include <sstream>
#include "StampaVettore.h"
#include "JS.h"

void leggiFile(std::string &filename, std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> &coppie)
{
    std::ifstream inFile(filename); // per aprire il file
    std::string line;               // per memorizzare ogni riga del file durante la lettura
    while (std::getline(inFile, line))
    {
        std::vector<uint64_t> set1, set2;
        std::istringstream s1(line); // inizializza un flusso di input dalla stringa line
        size_t num;
        while (s1 >> num)
        {
            set1.push_back(num);
        }
        if (!std::getline(inFile, line))
            break;
        std::istringstream s2(line);
        while (s2 >> num)
        {
            set2.push_back(num);
        }
        std::getline(inFile, line);

        coppie.push_back({set1, set2});

        std::getline(inFile, line);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Utilizzo: " << argv[0] << " <k> <dimensione_m>\n";
        return 1;
    }
    size_t k = std::stoi(argv[1]); // Numero di funzioni hash
    size_t m = std::stoi(argv[2]); // Modulo dell'universo
    size_t seed = 2;               // Seed fisso per test ripetibili

    std::string filename = "due_elementini.txt";
    std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> coppie;
    leggiFile(filename, coppie);
    for (auto &coppia : coppie)
    {
        std::vector<uint64_t> set1 = coppia.first;
        std::vector<uint64_t> set2 = coppia.second;

        std::cout << "Set_1: ";
        StampaVettore::printVector(set1);
        std::cout << "Set_2:";
        StampaVettore::printVector(set2);

        // Calcolo k-minHash
        // KMinHash kMinHash(k, m, seed);
        // std::vector<uint64_t> firma1 = kMinHash.computeSignature(set1);
        // std::vector<uint64_t> firma2 = kMinHash.computeSignature(set2);

        // Calcolo OnePerm
        //   OnePermutation oph(k,m,seed);
        //  std::vector<uint64_t> firma1 = oph.computeSignature(set1);
        //  std::vector<uint64_t> firma2 = oph.computeSignature(set2);

        // Calcolo FastSimilaritySketching
        FastSimilaritySketching fss(k, m, seed);
        std::vector<double> firma1 = fss.computeSignature(set1);
        std::vector<double> firma2 = fss.computeSignature(set2);

        // Stampa Firme
        std::cout << "Firma Set_1: ";
        StampaVettore::printVector(firma1);
        std::cout << "Firma Set_2: ";
        StampaVettore::printVector(firma2);

        // Calcolo della Jaccard Similarity approssimata
        float approxJaccard = JS::approx(firma1, firma2, k);
        std::cout << "Approximate Jaccard Similarity: " << approxJaccard << "\n";

        // Calcolo della Jaccard Similarity esatta
        float exactJaccard = JS::esatta(set1, set2);
        std::cout << "Exact Jaccard Similarity: " << exactJaccard << "\n";
        std::cout << "\n";
    }

    return 0;
}
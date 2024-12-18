#include <iostream>
#include <vector>
#include <algorithm>
// #include "KMinHash.h"
#include "OnePermutation.h"
// #include "FastSimilaritySketching.h"
#include <fstream>
#include <sstream>
#include "StampaVettore.h"

/**
 * Calcola la Jaccard Similarity esatta tra due insiemi (Algoritmo Naive).
 * @param set1: Primo insieme.
 * @param set2: Secondo insieme.
 * @return Similarità di Jaccard.
 */
float jsEsatta(std::vector<uint64_t> set1, std::vector<uint64_t> set2) {
    std::vector<uint64_t> unione, intersezione;
    size_t lenS1 = set1.size(), lenS2 = set2.size();
    unione = set1;
    for (size_t i = 0; i < lenS2; i++){
        if (std::find(unione.begin(), unione.end(), set2[i]) == unione.end()){
            unione.push_back(set2[i]);
        }
    }
    for (size_t i = 0; i < lenS1; i++){
        if (std::find(set2.begin(), set2.end(), set1[i]) != set2.end()){
            intersezione.push_back(set1[i]);
        }
    }
    float js = static_cast<float>(intersezione.size()) / unione.size();
    return js;
}

/**
 * Funzione per il calcolo della Jaccard Similarity Approssimata
 * @param s1: firme del prima insieme 
 * @param s2: firme del secondo insieme
 * @param k: lunghezza dei vettori delle firme (numero delle funzioni hash utilizzate)
 * @return Similarità di Jaccard Aprrossimata.
 */
float jsApprossimata(std::vector<uint64_t> s1, std::vector<uint64_t> s2, int k){
    size_t count = 0;
    for (size_t i = 0; i < k; i++){
        if (s1[i] == s2[i]){
            count++;
        }
    }
    return static_cast<float>(count)/k;
}

void leggiFile(std::string&filename,std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>>& coppie){
    std::ifstream inFile(filename); // per aprire il file
    std::string line; // per memorizzare ogni riga del file durante la lettura
    while (std::getline(inFile, line)) {  
        std::vector<uint64_t> set1, set2;
        std::istringstream s1(line); // inizializza un flusso di input dalla stringa line
        size_t num;
        while (s1>>num){
            set1.push_back(num);
        }
        if (!std::getline(inFile, line)) break;
        std::istringstream s2(line);
        while (s2 >> num) {
            set2.push_back(num); 
        }
        std::getline(inFile, line);
        
        coppie.push_back({set1, set2});

        std::getline(inFile, line);
        }
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Utilizzo: " << argv[0] << " <k> <dimensione_m>\n";
        return 1;
    }
    size_t k = std::stoi(argv[1]); // Numero di funzioni hash
    size_t m = std::stoi(argv[2]); // Modulo dell'universo
    size_t seed = 2; // Seed fisso per test ripetibili

    std::string filename ="dataset_0.47.txt";
    std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> coppie;
    leggiFile(filename, coppie);
    for (auto& coppia:coppie){
        std::vector<uint64_t> set1 = coppia.first;
        std::vector<uint64_t> set2 = coppia.second;
        
        // Vettori di input
        // std::vector<uint64_t> set1 = {1, 6, 7, 14, 3, 10, 11};
        //std::vector<uint64_t> set2 = {1, 2, 6, 7, 16, 11, 4, 9, 3};

        StampaVettore stampa;

        std::cout << "Set_1: ";
        stampa.printVector(set1);
        std::cout << "Set_2:";
        stampa.printVector(set2);
    /*
        // Calcolo k-minHash
        KMinHash kMinHash(k, m, seed);
        std::vector<uint64_t> firma1 = kMinHash.computeSignature(set1);
        std::vector<uint64_t> firma2 = kMinHash.computeSignature(set2);
    */ 
    
      // Calcolo OnePerm
        OnePermutation oph(k,m,seed);
        std::vector<uint64_t> firma1 = oph.computeSignature(set1);
        std::vector<uint64_t> firma2 = oph.computeSignature(set2);

        // Calcolo FastSimilaritySketching
        //FastSimilaritySketching fss(k, m, seed);
        //std::vector<double> firma1 = fss.computeSignature(set1);
        //std::vector<double> firma2 = fss.computeSignature(set2);

        // std::cout << "Firma Set_1: ";
        // stampa.printVector(firma1);
        // std::cout << "Firma Set_2: ";
        // stampa.printVector(firma2);

        // Calcolo della Jaccard Similarity approssimata
        float approxJaccard = jsApprossimata(firma1, firma2, k);
        std::cout << "Approximate Jaccard Similarity: " << approxJaccard << "\n";

        // Calcolo della Jaccard Similarity esatta
        float exactJaccard = jsEsatta(set1, set2);
        std::cout << "Exact Jaccard Similarity: " << exactJaccard << "\n";

        std::cout << "\n";
    
    }

    return 0;
}
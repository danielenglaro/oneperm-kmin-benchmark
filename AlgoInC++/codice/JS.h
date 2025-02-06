#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class JS
{
private:
public:
    /**
     * Funzione per il calcolo della Jaccard Similarity Approssimata
     * @param s1: firme del prima insieme
     * @param s2: firme del secondo insieme
     * @param k: lunghezza dei vettori delle firme (numero delle funzioni hash utilizzate)
     * @return Similarità di Jaccard Aprrossimata.
     */
    static float approx(std::vector<uint64_t> s1, std::vector<uint64_t> s2, int k);

    /**
     * Calcola la Jaccard Similarity esatta tra due insiemi (Algoritmo Naive).
     * @param set1: Primo insieme.
     * @param set2: Secondo insieme.
     * @return Similarità di Jaccard.
     */
    static float esatta(std::vector<uint64_t> set1, std::vector<uint64_t> set2);
};
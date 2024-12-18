#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

/**
 * Classe HashFunction
 * Rappresenta una funzione hash della forma h(x) = (a * x + b) % m.
 */
class HashFunction {
private:
    int a;  ///< Coefficiente moltiplicativo
    int b;  ///< Coefficiente additivo
    int m;  ///< Modulo
public:
    /**
     * Costruttore.
     * @param m: Modulo per la funzione hash.
     * @param seed: Semina per il generatore casuale.
     */
    HashFunction(int m, int seed) {
        this->m = m;
        std::mt19937 gen(seed); // Generatore deterministico
        std::uniform_int_distribution<> distribA(1, m - 1);
        std::uniform_int_distribution<> distribB(0, m - 1);
        this->a = distribA(gen);
        this->b = distribB(gen);
    }

    /**
     * Mappa un elemento `x` utilizzando la funzione hash.
     * @param x: Valore da mappare.
     * @return Valore hashato.
     */
    size_t map(int x) const {
        return (static_cast<size_t>(a) * x + b) % m;
    }
};

/**
 * Classe KMinHash
 * Implementa l'algoritmo di k-minHashing.
 */
class KMinHash {
private:
    int k;  ///< Numero di funzioni hash.
    int m;  ///< Modulo per le funzioni hash.
    std::vector<HashFunction*> vettoreFirme; ///< Funzioni hash.

public:
    /**
     * Costruttore.
     * @param k: Numero di funzioni hash.
     * @param m: Modulo per le funzioni hash.
     * @param seed: Semina per il generatore casuale.
     */
    KMinHash(int k, int m, int seed){
        this->k = k;
        this->m = m;
        vettoreFirme = std::vector<HashFunction*>(k, nullptr);
        for (int i = 0; i < k; ++i) {
            vettoreFirme[i] = new HashFunction(m, seed + i); // Semi diversi per ogni funzione hash
        }
    }

    /**
     * Calcola la firma k-minHash di un vettore.
     * @param s: Vettore di input.
     * @return Firma k-minHash come vettore di interi.
     */
    std::vector<int> computeSignature(std::vector<int> s) {
        std::vector<int> signature(k, INT32_MAX);
        int lung = s.size();
        for (int i = 0; i < k; i++){
            for (int j = 0; j < lung; j++){
                if (vettoreFirme[i]->map(s[j]) < signature[i]){
                signature[i] = vettoreFirme[i]->map(s[j]);
                }
            }   
        }
    return signature;
    }
};

/**
 * Calcola la Jaccard Similarity esatta tra due insiemi (Algoritmo Naive).
 * @param set1: Primo insieme.
 * @param set2: Secondo insieme.
 * @return Similarità di Jaccard.
 */
float jsEsatta(std::vector<int> set1, std::vector<int> set2) {
    std::vector<int> unione, intersezione;
    int lenS1 = set1.size(), lenS2 = set2.size();
    unione = set1;
    for (int i = 0; i < lenS2; i++){
        if (std::find(unione.begin(), unione.end(), set2[i]) == unione.end()){
            unione.push_back(set2[i]);
        }
    }
    for (int i = 0; i < lenS1; i++){
        if (std::find(set2.begin(), set2.end(), set1[i]) != set2.end()){
            intersezione.push_back(set1[i]);
        }
    }
    float js = static_cast<float>(intersezione.size()) / unione.size();
    return js;
}

/**
 * Funzione di utilità per stampare un vettore.
 * @param array: Vettore da stampare.
 */
void printVector(const std::vector<int>& vettore) {
    std::cout << "[ ";
    for (int val : vettore) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}

/**
 * Funzione per il calcolo della Jaccard Similarity Approssimata
 * @param s1: firme del prima insieme 
 * @param s2: firme del secondo insieme
 * @param k: lunghezza dei vettori delle firme (numero delle funzioni hash utilizzate)
 * @return Similarità di Jaccard Aprrossimata.
 */
float jsApprossimata(std::vector<int> s1, std::vector<int> s2, int k){
    int count = 0;
    for (int i = 0; i < k; i++){
        if (s1[i] == s2[i]){
            count++;
        }
    }
    return static_cast<float>(count)/k;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Utilizzo: " << argv[0] << " <k> <dimensione_m>\n";
        return 1;
    }
    int k = std::stoi(argv[1]); // Numero di funzioni hash
    int m = std::stoi(argv[2]); // Modulo dell'universo
    int seed = 1; // Seed fisso per test ripetibili

    // Vettori di input
    std::vector<int> set1 = {1, 6, 7, 14, 3, 10, 11};
    std::vector<int> set2 = {1, 2, 6, 7, 16, 11, 4, 9, 3};

    std::cout << "Set_1: ";
    printVector(set1);
    std::cout << "Set_2: ";
    printVector(set2);

    // Calcolo k-minHash
    KMinHash kMinHash(k, m, seed);
    std::vector<int> firma1 = kMinHash.computeSignature(set1);
    std::vector<int> firma2 = kMinHash.computeSignature(set2);

    std::cout << "Firma Set_1: ";
    printVector(firma1);
    std::cout << "Firma Set_2: ";
    printVector(firma2);

    // Calcolo della Jaccard Similarity approssimata
    float approxJaccard = jsApprossimata(firma1, firma2, k);
    std::cout << "Approximate Jaccard Similarity: " << approxJaccard << "\n";

    // Calcolo della Jaccard Similarity esatta
    float exactJaccard = jsEsatta(set1, set2);
    std::cout << "Exact Jaccard Similarity: " << exactJaccard << "\n";

    return 0;
}

#include "HashFunction.h"
#include <vector>
#include <random>
#include <limits>

class OnePermutation
{
private:
    size_t k;               ///< Numero di bins.
    size_t m;               ///< Modulo per le funzioni hash.
    HashFunction *funzHash; ///< Funzione hash.
    std::vector<bool> bit_vector;
public:
    /**
     * Costruttore.
     * @param k: Numero di funzioni hash.
     * @param m: Modulo per le funzioni hash.
     * @param seed: Semina per il generatore casuale.
     */
    OnePermutation(size_t k, size_t m, size_t seed);

    /**
     * Calcola la firma k-minHash di un vettore.
     * @param s: Vettore di input.
     * @return Firma k-minHash come vettore di interi.
     */
    std::vector<double> computeSignature(std::vector<uint64_t> s);
};
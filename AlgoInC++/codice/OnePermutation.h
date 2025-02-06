#include "HashFunction.h"
#include <vector>
#include <random>
#include <limits>

class OnePermutation
{
private:
    size_t k;                     ///< Numero di bin dello sketch (dimensione dello sketch).
    size_t m;                     ///< Modulo per le funzioni hash (dimensione dell'universo U).
    HashFunction *funzHash;       ///< Puntatore alla funzione hash (estratta casualmente).
    std::vector<bool> bit_vector; ///< Vettore binario (random) usato per la densificazione delle firme.
public:
    /**
     * Costruttore della classe OnePermutation.
     * @param k: Numero di bin dello sketch (dimensione dello sketch).
     * @param m: Modulo per le funzioni hash (dimensione dell'universo U).
     * @param seed: Seme per il generatore di numeri casuali utilizzato per la funzione hash.
     */
    OnePermutation(size_t k, size_t m, size_t seed);

    /**
     * Calcola la firma OH di un vettore.
     * @param s: Vettore del set di input.
     * @return Firma OPH come vettore di interi.
     */
    std::vector<uint64_t> computeSignature(std::vector<uint64_t> s);
};
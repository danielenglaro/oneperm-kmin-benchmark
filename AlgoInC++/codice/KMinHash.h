#include "HashFunction.h"
#include <vector>

class KMinHash
{
private:
    size_t k;                                 ///< Numero di funzioni hash.
    size_t m;                                 ///< Modulo per le funzioni hash.
    std::vector<HashFunction *> vettoreFirme; ///< Funzioni hash.

public:
    /**
     * Costruttore.
     * @param k: Numero di funzioni hash.
     * @param m: Modulo per le funzioni hash.
     * @param seed: Semina per il generatore casuale.
     */
    KMinHash(size_t k, size_t m, size_t seed);

    /**
     * Calcola la firma k-minHash di un vettore.
     * @param s: Vettore di input.
     * @return Firma k-minHash come vettore di interi.
     */
    std::vector<uint64_t> computeSignature(std::vector<uint64_t> s);
};
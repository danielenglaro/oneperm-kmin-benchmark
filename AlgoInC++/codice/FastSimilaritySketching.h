#include <vector>
#include "FSHashFunction.h"
#include <iostream>

class FastSimilaritySketching
{
private:
    size_t t;                     ///< Numero di bin.
    size_t m;                     ///< Modulo per le funzioni hash.
    FSHashFunction *funzioniHash; ///< Funzioni hash.

public:
    /**
     * Costruttore.
     * @param t: Numero di bin.
     * @param m: Modulo per le funzioni hash.
     * @param seed: Semina per il generatore casuale.
     */
    FastSimilaritySketching(size_t t, size_t m, size_t seed);

    /**
     * Calcola la firma di un vettore.
     * @param s: Vettore di input.
     * @return Firma come vettore di reali (double).
     */
    std::vector<double> computeSignature(std::vector<uint64_t> s);
};
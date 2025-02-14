#ifndef HASHFUNCTION_H // Controlla se la macro non è già definita
#define HASHFUNCTION_H // Definisci la macro per evitare inclusioni successive

#include "Prime.h"
#include <random>

class HashFunction
{
private:
    size_t a; ///< Coefficiente moltiplicativo
    size_t b; ///< Coefficiente additivo
    size_t m; ///< Modulo Universo
    size_t p; ///< Numero primo maggiore di m
public:
    /**
     * Costruttore.
     * @param m: Modulo per la funzione hash.
     * @param seed: Seme per il generatore casuale.
     */
    HashFunction(size_t m, size_t seed);

    /**
     * Calcola l'hash value dell'elemento `x`.
     * @param x: Valore da mappare.
     * @return Hash Value.
     */
    size_t map(size_t x);
};

#endif // Fine della protezione contro l'inclusione multipla
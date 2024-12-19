#ifndef HASHFUNCTION_H // Controlla se la macro non è già definita
#define HASHFUNCTION_H // Definisci la macro per evitare inclusioni successive

#include <cstddef>
#include <iostream>

class HashFunction
{
private:
    size_t a; ///< Coefficiente moltiplicativo
    size_t b; ///< Coefficiente additivo
    size_t m; ///< Modulo
public:
    /**
     * Costruttore.
     * @param m: Modulo per la funzione hash.
     * @param seed: Semina per il generatore casuale.
     */
    HashFunction(size_t m, size_t seed);

    /**
     * Mappa un elemento `x` utilizzando la funzione hash.
     * @param x: Valore da mappare.
     * @return Valore hashato.
     */
    size_t map(size_t x);
};

#endif // Fine della protezione contro l'inclusione multipla
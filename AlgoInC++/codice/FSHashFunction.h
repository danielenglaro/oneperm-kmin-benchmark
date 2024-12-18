#ifndef HASHFUNCTION_H  // Controlla se la macro non è già definita
#define HASHFUNCTION_H  // Definisci la macro per evitare inclusioni successive

#include <cstddef>
#include <iostream>
#include <vector>

class FSHashFunction {
private:
    size_t a;  ///< Coefficiente moltiplicativo
    size_t b;  ///< Coefficiente additivo
    size_t t;  ///< Modulo
    size_t m;
    std::vector<double> vettoreV;
public:
    /**
     * Costruttore.
     * @param m: Modulo per la funzione hash.
     * @param seed: Semina per il generatore casuale.
     */
    FSHashFunction(size_t seed, size_t m, size_t t);

    /**
     * Mappa un elemento `x` utilizzando la funzione hash.
     * @param x: Valore da mappare.
     * @return Valore hashato.
     */
    std::pair<size_t, double> map(size_t x, size_t i);
};

#endif // Fine della protezione contro l'inclusione multipla
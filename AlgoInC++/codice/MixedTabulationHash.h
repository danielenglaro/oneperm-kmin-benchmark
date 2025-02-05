#include <vector>
#include <random>
#include <utility>
#include "Prime.h"
class MixedTabulationHash {
private:
    size_t m; // Dimensione dell'universo
    size_t t; // Dimensione dello sketch
    size_t p; // Numero primo > m
    size_t p_t; // Numero primo > t
    std::vector<std::vector<size_t>> tab; // Tabella di tabulazione
    const size_t c = 4; // Numero di caratteri (da adattare)
    const size_t u = 256; // Dimensione dell'alfabeto

public:
    MixedTabulationHash(size_t m, size_t seed, size_t t, const std::vector<std::vector<size_t>>& tab);
    std::pair<size_t, double> map(size_t x, size_t i);
};
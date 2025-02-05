
#include "MixedTabulationHash.h"

MixedTabulationHash::MixedTabulationHash(size_t m, size_t seed, size_t t, const std::vector<std::vector<size_t>>& tab) {
    this->m = m;
    this->t = t;
    this->p = Prime::nextPrime(m);
    this->p_t = Prime::nextPrime(t);
    this->tab = tab; // Usa la tabella passata
}

std::pair<size_t, double> MixedTabulationHash::map(size_t x, size_t i) {
    std::vector<size_t> chars(c);
    size_t temp_x = x;
    for (size_t j = 0; j < c; ++j) {
        chars[j] = temp_x % u;
        temp_x /= u;
    }

    size_t hash_val = 0;
    for (size_t j = 0; j < c; ++j) {
        hash_val ^= tab[i][j] * chars[j];
    }

    size_t bin;
    double val = i + (static_cast<double>(hash_val % p_t) / p_t);

    if (i < t) {
        bin = hash_val % t;
    } else {
        bin = i - t;
    }
    return {bin, val};
}
#ifndef PRIME_H
#define PRIME_H

#include <cmath>

class Prime {
public:
    // Verifica se un numero è primo
    static bool isPrime(size_t n);
    
    // Trova il primo numero primo maggiore di num
    static size_t nextPrime(size_t num);
};

#endif // PRIME_H
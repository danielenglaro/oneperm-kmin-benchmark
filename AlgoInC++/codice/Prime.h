#ifndef PRIME_H
#define PRIME_H

#include <cmath>

class Prime {
public:
    // Verifica se un numero è primo
    static bool isPrime(int n);
    
    // Trova il primo numero primo maggiore di num
    static int nextPrime(int num);
};

#endif // PRIME_H
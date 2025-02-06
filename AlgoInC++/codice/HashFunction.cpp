#include "HashFunction.h"

HashFunction::HashFunction(size_t m, size_t seed)
{
    this->m = m;
    this->p = Prime::nextPrime(m);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> distribA(1, p - 1);
    std::uniform_int_distribution<> distribB(0, p - 1);
    this->a = distribA(gen);
    this->b = distribB(gen);
}

size_t HashFunction::map(size_t x)
{
    return ((static_cast<size_t>(a) * x + b) % p) % m;
}
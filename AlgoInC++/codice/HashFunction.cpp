#include "HashFunction.h"
#include <random>

HashFunction::HashFunction(size_t m, size_t seed)
{
    this->m = m;
    p = Prime::nextPrime(m);
    std::mt19937 gen(seed); // Generatore deterministico
    std::uniform_int_distribution<> distribA(1, p - 1);
    std::uniform_int_distribution<> distribB(0, p - 1);
    this->a = distribA(gen);
    this->b = distribB(gen);
}
size_t HashFunction::map(size_t x)
{
    return ((static_cast<size_t>(a) * x + b)% p ) % m;
}

std::pair<size_t, double> HashFunction::map(size_t x, size_t i)
{
    size_t bin;
    double val = i + (static_cast<double>((static_cast<size_t>(a) * x + b) % p) / p);
    if (i < m)
    {
        bin = ( (static_cast<size_t>(a) * x + b)% p )% m;
        return {bin, val};
    }
    bin = i - m;
    return {bin, val};
}
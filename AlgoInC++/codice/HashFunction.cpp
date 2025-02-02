#include "HashFunction.h"
#include <random>

HashFunction::HashFunction(size_t m, size_t seed, size_t t)
{
    this->m = m;
    this->t = t;
    this-> p = Prime::nextPrime(m);
    this->p_t = Prime::nextPrime(t);
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
    if (i < t)
    {
        bin = ( (static_cast<size_t>(a) * x + b) % p_t ) % t;
        // std::cout << "\n i:  "<< i << " bin: "<< bin << " val: "<< val << " a: " << a << "  b:"<< b << "  x:" << x <<"  p: "<<p<<"  p_t: "<<p_t;
        return {bin, val};
    }
    bin = i - t;
    // std::cout << "\n i:  "<< i << " bin: "<< bin << " val: "<< val << " a: " << a << "  b:"<< b << "  x:" << x <<"  p: "<<p<<"  p_t: "<<p_t;
    return {bin, val};

}
#include "HashFunction.h"
#include <random>

HashFunction::HashFunction(size_t m, size_t seed) {
    this->m = m;
    std::mt19937 gen(seed); // Generatore deterministico
    std::uniform_int_distribution<> distribA(1, m - 1);
    std::uniform_int_distribution<> distribB(0, m - 1);
    this->a = distribA(gen);
    this->b = distribB(gen);
    //std::cout << "MyHash: a=" << a << ", b=" << b << ", m=" << m << std::endl;
}
size_t HashFunction::map(size_t x) {
    return (static_cast<size_t>(a) * x + b) % m;
}
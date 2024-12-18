#include "FSHashFunction.h"
#include <random>
#include <vector>

FSHashFunction::FSHashFunction(size_t seed, size_t m, size_t t){
    this->t = t;
    this->m = m;
    std::mt19937 gen(seed); // Generatore deterministico
    std::uniform_int_distribution<> distribA(1, m - 1);
    std::uniform_int_distribution<> distribB(0, m - 1);
    this->a = distribA(gen);
    this->b = distribB(gen);
    for (size_t i = 0; i < 2*t; i++){
        std::uniform_real_distribution<> distribI(i, i + 1); // [i,i+1)
        vettoreV.push_back( distribI(gen) );
    }
    //std::cout << "MyHash: a=" << a << ", b=" << b << ", m=" << m << std::endl;
}

std::pair<size_t, double> FSHashFunction::map(size_t x, size_t i)  {
    size_t b;
    double v = vettoreV[i];
    if (i<t){
        b = (static_cast<size_t>(a) * x + b) % t;
        return {b,v};
    }
    b = i-t;
    return {b,v};
}
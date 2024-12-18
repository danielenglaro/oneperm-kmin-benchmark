#include "FastSimilaritySketching.h"
#include <limits>
#include <vector>


FastSimilaritySketching::FastSimilaritySketching(size_t t, size_t m, size_t seed) {
    this->t = t;
    this->m = m;
    funzioniHash = new FSHashFunction(seed, m, t);
}

std::vector<double> FastSimilaritySketching::computeSignature(std::vector<uint64_t> s) {
    std::vector<double> signature(t, std::numeric_limits<double>::max());
    size_t lung = s.size();
    size_t c = 0;
    for (size_t i = 0; i < 2*t; i++) {
        for (size_t j = 0; j < lung; j++) {
            size_t b = (funzioniHash->map(s[j], i) ).first;
            double v = (funzioniHash->map(s[j], i) ).second;
            if (signature[b] == std::numeric_limits<double>::max() ) c++;
            if (v < signature[b]) signature[b] = v;
        }   
        if (c == t) return signature;
    }
    return signature;
}

//prova di modificwa
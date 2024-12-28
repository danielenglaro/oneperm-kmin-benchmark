#include "KMinHash.h"



KMinHash::KMinHash(size_t k, size_t m, size_t seed)
{
    this->k = k;
    this->m = m;
    vettoreFirme = std::vector<HashFunction *>(k, nullptr);
    for (size_t i = 0; i < k; ++i)
    {
        vettoreFirme[i] = new HashFunction(m, seed + i); // Semi diversi per ogni funzione hash
    }
}

std::vector<double> KMinHash::computeSignature(std::vector<uint64_t> s)
{
    std::vector<double> signature(k, std::numeric_limits<double>::max() );
    size_t lung = s.size();
    for (size_t i = 0; i < k; i++)
    {
        for (size_t j = 0; j < lung; j++)
        {
            if (vettoreFirme[i]->map(s[j]) < signature[i])
            {
                signature[i] = vettoreFirme[i]->map(s[j]);
            }
        }
    }
    return signature;
}

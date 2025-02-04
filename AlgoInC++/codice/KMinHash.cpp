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
    
    for (uint64_t elem : s)
    {
        for (size_t i = 0; i < k; i++)
        {   
            size_t hash_value = vettoreFirme[i]->map(elem);
            if ( hash_value < signature[i]) signature[i] = hash_value;
        }
    }
    return signature;
}

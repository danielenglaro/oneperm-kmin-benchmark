#include "OnePermutation.h"

OnePermutation::OnePermutation(size_t k, size_t m, size_t seed)
{
    this->k = k;
    this->m = m;
    funzHash = new HashFunction(m, seed);
    // std::cout << "DEBUG - OnePermutation: k=" << k << ", m=" << m << ", seed=" << seed << std::endl;
}

std::vector<double> OnePermutation::computeSignature(std::vector<uint64_t> s)
{
    std::vector<double> signature(k,  std::numeric_limits<double>::max() );
    size_t range = m / k;

    for (size_t i = 0; i < s.size(); i++)
    {
        size_t v = funzHash->map(s[i]);
        if ( v < signature[v/range] ) signature[v/range] = v;
    }
    return signature;
}

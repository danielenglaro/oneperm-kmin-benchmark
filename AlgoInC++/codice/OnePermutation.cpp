#include "OnePermutation.h"
#include <limits>
OnePermutation::OnePermutation(size_t k, size_t m, size_t seed)
{
    this->k = k;
    this->m = m;
    if (m % k != 0) this->m = m + k - (m % k); // impostare m multiplo multiplo successivo di k per eseguire la divisione in bucket
    funzHash = new HashFunction(m, seed);
    // std::cout << "DEBUG - OnePermutation: k=" << k << ", m=" << m << ", seed=" << seed << std::endl;
}

std::vector<double> OnePermutation::computeSignature(std::vector<uint64_t> s)
{   
    // Costruzione Firma
    std::vector<double> signature(k,  std::numeric_limits<double>::max() );
    size_t range = m / k;

    for (size_t i = 0; i < s.size(); i++)
    {
        size_t v = funzHash->map(s[i]);
        if ( (v%range) < signature[v/range] ) signature[v/range] = (v%range);
    }

    // Densificazione Per Rotazione
    size_t C = range +1;
    for (size_t j = 0; j < k; j++)
    {     
        
        if (signature[j] == std::numeric_limits<double>::max())
        {
            size_t start = j, add = 0, jump = 0;
            while ( signature[start + add] == std::numeric_limits<double>::max() )
            {   
                add++, jump++;
                if(start + add > k-1) start = 0, add = 0;   
            }
            signature[j] = signature[start + add] + ( jump*C );
        }
    }
    return signature;
}
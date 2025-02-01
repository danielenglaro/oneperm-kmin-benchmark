#include "FastSimilaritySketching.h"
#include <limits>
#include <vector>
#include "StampaVettore.h"

FastSimilaritySketching::FastSimilaritySketching(size_t t, size_t seed)
{
    this->t = t;
    funzioniHash = new HashFunction(t, seed);
}

std::vector<double> FastSimilaritySketching::computeSignature(std::vector<uint64_t> s)
{
    std::vector<double> signature(t, (std::numeric_limits<double>::max()));
    size_t lung = s.size();
    size_t c = 0;
    // std::cout << "[DEBUG] Inizio calcolo signature per vettore di lunghezza " << lung << std::endl;

    for (size_t i = 0; i < 2 * t; i++)
    {
        for (size_t j = 0; j < lung; j++)
        {
            size_t b = (funzioniHash->map(s[j], i)).first;
            double v = (funzioniHash->map(s[j], i)).second;
            // std::cout << "Elemento s[" << j << "]=" << s[j] << ", bin=" << b << ", valore=" << v << std::endl;

            if (signature[b] == std::numeric_limits<double>::max())
            {
                c++;
                // std::cout << "Primo valore nel bin " << b << ", incremento c a " << c << std::endl;
            }
            // std::cout << "\nb: " << b << "\nv: " << v; //qui v è un valore con la virgola
            if (v < signature[b])
            {
                // std::cout << "Aggiornamento signature[" << b << "] da " << signature[b] << " a " << v << std::endl;
                signature[b] = v;
                // std::cout << "\naggiornamento firma: "; //qui non lo è piu
            }
        }
        if (c == t){
            // std::cout << "[C HA RAGGIUNTO T]" << std::endl;
        break;
        }
    }
    // StampaVettore::printVector(signature);
    return signature;
}
#include "FastSimilaritySketching.h"
#include <limits>
#include <vector>
#include "StampaVettore.h"

FastSimilaritySketching::FastSimilaritySketching(size_t t, size_t seed)
{
    this->t = t;
    vettoreFirme = std::vector<HashFunction *>(2*t, nullptr);
    for (size_t i = 0; i < 2*t; ++i)
    {
        vettoreFirme[i] = new HashFunction(t, seed + i); // Semi diversi per ogni funzione hash
    }
    // funzioniHash = new HashFunction(t, seed);
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
            std::pair<size_t, double> hashvalue = vettoreFirme[i]->map(s[j], i);
            size_t b = hashvalue.first;
            double v = hashvalue.second;
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
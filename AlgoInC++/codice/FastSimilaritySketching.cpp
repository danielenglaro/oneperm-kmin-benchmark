#include "FastSimilaritySketching.h"
#include <limits>
#include <vector>
#include "StampaVettore.h"

FastSimilaritySketching::FastSimilaritySketching(size_t t, size_t m, size_t seed)
{
    this->t = t;
    this->m = m;
    funzioniHash = new FSHashFunction(seed, m, t);
}

std::vector<double> FastSimilaritySketching::computeSignature(std::vector<uint64_t> s)
{
    std::vector<double> signature(t, (std::numeric_limits<double>::max()));
    size_t lung = s.size();
    size_t c = 0;
    std::cout << "[DEBUG] Inizio calcolo signature per vettore di lunghezza " << lung << std::endl;

    for (size_t i = 0; i < 2 * t; i++)
    { std::cout << "[DEBUG] Iterazione i=" << i << std::endl;
        for (size_t j = 0; j < lung; j++)
        {
            size_t b = (funzioniHash->map(s[j], i)).first;
            double v = (funzioniHash->map(s[j], i)).second;
            std::cout << "  [DEBUG] Elemento s[" << j << "]=" << s[j]
                      << ", bin=" << b << ", valore=" << v << std::endl;

            if (signature[b] == std::numeric_limits<double>::max())
                c++;
                 std::cout << "  [DEBUG] Primo valore nel bin " << b << ", incremento c a " << c << std::endl;
            // std::cout << "\nb: " << b << "\nv: " << v; //qui v è un valore con la virgola
            if (v < signature[b])
             std::cout << "  [DEBUG] Aggiornamento signature[" << b << "] da " << signature[b] << " a " << v << std::endl;
                signature[b] = v;
            // std::cout << "\naggiornamento firma: "; //qui non lo è piu
            StampaVettore::printVector(signature);
        }
        if (c == t)
         std::cout << "[DEBUG] Tutti i bin riempiti. Firma calcolata." << std::endl;
            return signature;
    }
     std::cout << "[DEBUG] Firma completa calcolata dopo tutte le iterazioni." << std::endl;
    return signature;

}
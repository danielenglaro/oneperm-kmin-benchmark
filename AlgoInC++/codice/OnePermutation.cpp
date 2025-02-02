#include "OnePermutation.h"

OnePermutation::OnePermutation(size_t k, size_t m, size_t seed)
{
    this->k = k;
    this->m = m;
    if (m % k != 0) this->m = m + k - (m % k); // impostare m multiplo multiplo successivo di k per eseguire la divisione in bucket
    funzHash = new HashFunction(m, seed);
    
    //modifica serale direzione:
    bit_vector.resize(k); // Inizializza il vettore di bit con k valori
    
    // Inizializza il generatore di numeri casuali
    std::random_device rd;  // Ottieni un seme casuale
    std::mt19937 gen(rd());  // Inizializza il generatore
    std::uniform_int_distribution<> dis(0, 1);  // Distribuzione uniforme tra 0 e 1

    // Popola il vettore con valori casuali
    for (size_t j = 0; j < k; ++j) {
        bit_vector[j] = dis(gen);  // Assegna 0 o 1 casualmente
    }
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
            size_t start = j, step = 1, currentIndex;
            while (true)
            {   
                currentIndex = (bit_vector[j]) ? (start + step) % k : (start - step + k) % k;

                if (signature[currentIndex] != std::numeric_limits<double>::max() && signature[currentIndex] < range) break; // Esci se trovi un valore valido

                step++;
            }
            signature[j] = signature[currentIndex] + ( step*C );
        }
    }
    return signature;
}
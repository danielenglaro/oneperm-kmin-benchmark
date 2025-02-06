#include "OnePermutation.h"

OnePermutation::OnePermutation(size_t k, size_t m, size_t seed)
{
    this->k = k;
    this->m = m;
    if (m % k != 0)
        this->m = m + k - (m % k); // imposto m divisibile per k bucket
    funzHash = new HashFunction(m, seed);

    bit_vector.resize(k); // Inizializza il vettore di bit con k valori
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); // Distrib. uniforme tra 0 e 1
    for (size_t j = 0; j < k; j++)
        bit_vector[j] = dis(gen); // Assegna 0 o 1 casualmente
}

std::vector<uint64_t> OnePermutation::computeSignature(std::vector<uint64_t> set, bool rotazione)
{
    // Inizializzazione
    std::vector<uint64_t> signature(k, UINT64_MAX);
    size_t range = m / k;
    size_t C = range + 1;

    // Costruzione Firma
    for (uint64_t e : set)
    {
        size_t v = funzHash->map(e);
        size_t i = v / range;
        if ((v % range) < signature[i])
            signature[i] = (v % range);
    }

    // Densificazione Per Rotazione
    if (rotazione)
    {
        for (size_t j = 0; j < k; j++)
        {
            if (signature[j] == std::numeric_limits<double>::max())
            {
                size_t start = j, step = 1, currentIndex;
                while (true)
                {
                    currentIndex = (bit_vector[j]) ? (start + step) % k : (start - step + k) % k;

                    if (signature[currentIndex] != UINT64_MAX && signature[currentIndex] < range)
                        break;

                    step++;
                }
                signature[j] = signature[currentIndex] + (step * C);
            }
        }
    }
    return signature;
}
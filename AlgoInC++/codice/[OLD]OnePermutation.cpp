// #include "OnePermutation.h"
// #include <limits>
// OnePermutation::OnePermutation(size_t k, size_t m, size_t seed)
// {
//     this->k = k;
//     this->m = m;
//     if (m % k != 0) this->m = m + k - (m % k); // impostare m multiplo multiplo successivo di k per eseguire la divisione in bucket
//     funzHash = new HashFunction(m, seed);
//     // std::cout << "DEBUG - OnePermutation: k=" << k << ", m=" << m << ", seed=" << seed << std::endl;

//     //modifica serale direzione:
//     bit_vector.resize(k); // Inizializza il vettore di bit con k valori
    
//     // Inizializza il generatore di numeri casuali
//     std::random_device rd;  // Ottieni un seme casuale
//     std::mt19937 gen(rd());  // Inizializza il generatore
//     std::uniform_int_distribution<> dis(0, 1);  // Distribuzione uniforme tra 0 e 1

//     // Popola il vettore con valori casuali
//     for (int j = 0; j < k; ++j) {
//         bit_vector[j] = dis(gen);  // Assegna 0 o 1 casualmente
//     }
// }

// std::vector<double> OnePermutation::computeSignature(std::vector<uint64_t> s)
// {   
//     // Costruzione Firma
//     std::vector<double> signature(k,  std::numeric_limits<double>::max() );
//     size_t range = m / k;

//     for (size_t i = 0; i < s.size(); i++)
//     {
//         size_t v = funzHash->map(s[i]);
//         if ( (v%range) < signature[v/range] ) signature[v/range] = (v%range);
//     }

//     // Densificazione Per Rotazione
//     size_t C = range +1;
//     for (size_t j = 0; j < k; j++)
//     {     

//         if (signature[j] == std::numeric_limits<double>::max())
//         {   
//             size_t start = j, step = 0, count = 0;
//             while ( signature[start + step] == std::numeric_limits<double>::max() )
//             {   
//                 step++, count++;
//                 if(start + step > k-1) start = 0, step = 0;   
//             }
//             signature[j] = signature[start + step] + ( count*C );
//         }
//     }
//     return signature;
// }
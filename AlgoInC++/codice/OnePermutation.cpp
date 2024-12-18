#include "OnePermutation.h"

OnePermutation::OnePermutation(size_t k, size_t m, size_t seed){
    this->k = k;
    this->m = m;
    funzHash = new HashFunction(m, seed);
   // std::cout << "DEBUG - OnePermutation: k=" << k << ", m=" << m << ", seed=" << seed << std::endl;
}

std::vector<uint64_t> OnePermutation::computeSignature(std::vector<uint64_t> s) {
    std::vector<uint64_t> signature(k, UINT64_MAX), sPerm;
    size_t numElemBin = m/k;
    
    for (size_t i = 0; i < s.size(); i++) {
        sPerm.push_back( funzHash->map(s[i]) );
        //std::cout << "DEBUG - Elemento: " << s[i] << ", HashValue: " << funzHash->map(s[i]) << std::endl;
    }
    
    for (size_t j = 0; j < k; j++){
        for (size_t i = 0; i < sPerm.size(); i++) {
            if ( sPerm[i] >= j*numElemBin && sPerm[i] < ((j+1)*numElemBin) ){
                if (sPerm[i]%numElemBin < signature[j]) signature[j] = sPerm[i]%numElemBin;
                /*std::cout << "DEBUG - Bin " << j 
                              << ": elemento=" << sPerm[i] 
                              << ", modValue=" << signature[j] 
                              << ", nuovo valore signature[" << j << "]=" << signature[j] << std::endl;*/
                              
            }
        }
    }
    return signature;
}

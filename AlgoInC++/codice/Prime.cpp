#include "Prime.h"

bool Prime::isPrime(size_t n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    // Controlliamo solo i numeri dispari fino alla radice quadrata di n
    size_t sqrtN = sqrt(n);
    for (size_t i = 3; i <= sqrtN; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

size_t Prime::nextPrime(size_t num) {
    // Se il numero è pari, partiamo dal successivo dispari
    if (num % 2 == 0) num++;
    else num += 2;
    
    // Continuiamo a cercare finché non troviamo un primo
    while (!isPrime(num)) {
        num += 2;  // Controlliamo solo i numeri dispari
    }
    return num;
}
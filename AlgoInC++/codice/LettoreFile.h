
#ifndef LETTOREFILE_H
#define LETTOREFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <cstdint>

class LettoreFile {
public:
    // La funzione ora restituisce il vettore di coppie invece di prenderlo come parametro
    static std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> read(std::string &filename);
};

#endif // LETTOREFILE_H
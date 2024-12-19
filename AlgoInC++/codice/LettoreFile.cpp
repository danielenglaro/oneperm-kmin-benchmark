#include "LettoreFile.h"
#include <fstream>
#include <iostream>

void LettoreFile::read(std::string &filename, std::vector<std::pair<std::vector<uint64_t>, std::vector<uint64_t>>> &coppie)
{
    std::ifstream inFile(filename); // per aprire il file
    std::string line;               // per memorizzare ogni riga del file durante la lettura
    while (std::getline(inFile, line))
    {
        std::vector<uint64_t> set1, set2;
        std::istringstream s1(line); // inizializza un flusso di input dalla stringa line
        size_t num;
        while (s1 >> num)
        {
            set1.push_back(num);
        }
        if (!std::getline(inFile, line))
            break;
        std::istringstream s2(line);
        while (s2 >> num)
        {
            set2.push_back(num);
        }
        std::getline(inFile, line);

        coppie.push_back({set1, set2});

        std::getline(inFile, line);
    }
}
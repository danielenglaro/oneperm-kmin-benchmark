#include "StampaVettore.h"

void StampaVettore::printVector(const std::vector<uint64_t>& vettore) {
        std::cout << "[ ";
        for (size_t val : vettore) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }

void StampaVettore::printVector(const std::vector<double>& vettore) {
        std::cout << "[ ";
        for (double val : vettore) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
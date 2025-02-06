#include "StampaVettore.h"

void StampaVettore::printVector(const std::vector<uint64_t> &vettore)
{
    std::cout << "[ ";
    for (size_t val : vettore)
    {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}
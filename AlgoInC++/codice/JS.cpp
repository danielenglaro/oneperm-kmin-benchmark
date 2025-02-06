#include "JS.h"

float JS::approx(std::vector<uint64_t> s1, std::vector<uint64_t> s2, int k)
{
    size_t count = 0;
    for (int i = 0; i < k; i++)
    {
        if (s1[i] == s2[i])
        {
            count++;
        }
    }
    return static_cast<float>(count) / k;
}

float JS::esatta(std::vector<uint64_t> set1, std::vector<uint64_t> set2)
{
    std::vector<uint64_t> unione, intersezione;
    size_t lenS1 = set1.size(), lenS2 = set2.size();
    unione = set1;
    for (size_t i = 0; i < lenS2; i++)
    {
        if (std::find(unione.begin(), unione.end(), set2[i]) == unione.end())
        {
            unione.push_back(set2[i]);
        }
    }
    for (size_t i = 0; i < lenS1; i++)
    {
        if (std::find(set2.begin(), set2.end(), set1[i]) != set2.end())
        {
            intersezione.push_back(set1[i]);
        }
    }
    float js = static_cast<float>(intersezione.size()) / unione.size();
    return js;
}
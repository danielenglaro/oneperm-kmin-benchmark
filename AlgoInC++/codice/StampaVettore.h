#include <iostream>
#include <vector>
/**
 * Classe di utilità per stampare un vettore.
 * @param array: Vettore da stampare.
 */
class StampaVettore
{
private:
public:
    static void printVector(const std::vector<uint64_t> &vettore);

    static void printVector(const std::vector<double> &vettore);
};
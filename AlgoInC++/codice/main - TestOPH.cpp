// #include <iostream>
// #include <sstream>
// #include <iomanip>
// #include "KMinHash.h"
// #include "OnePermutation.h"
// #include "StampaVettore.h"
// #include "LettoreFile.h"
// #include "JS.h"

// int main()
// {      

//     // std::vector<uint64_t> s = {1};
//     // OnePermutation oph(6, 24, 1);
//     // oph.computeSignature(s, true);

//     size_t m = 100;
//     size_t k = 20;
//     size_t seed = 1;
//     size_t cardinalitaUnione = 5;
//     double jaccard_target = 0.1;

//     std::string esegui = "python3 script.py 1 "+ std::to_string(cardinalitaUnione) + " " + std::to_string(jaccard_target) + " " + std::to_string(m);
//     system(esegui.c_str());
//     std::ostringstream ss;
//     ss << std::fixed << std::setprecision(1) << jaccard_target;
//     std::string filename = "dataset_" + ss.str() + ".txt";

//     std::cout<<"\n\nVETTORI IN INPUT\n";
//     std::pair<std::vector<uint64_t>, std::vector<uint64_t>> coppia = LettoreFile::read(filename)[0];
//     StampaVettore::printVector(coppia.first);
//     StampaVettore::printVector(coppia.second);
//     std::cout<<"JACCARD ESATTA: " << JS::esatta(coppia.first, coppia.second)<<"\n";

//     std::cout<<"\n\nFIRME SENZA ROTAZIONE\n";
//     OnePermutation oph( k , m , seed);
//     std::vector<uint64_t> signature1 = oph.computeSignature(coppia.first, false);
//     std::vector<uint64_t> signature2 = oph.computeSignature(coppia.second, false);
//     StampaVettore::printVector(signature1);
//     StampaVettore::printVector(signature2);
//     std::cout<<"STIMA: " << JS::approxEB(signature1, signature2, k)<<"\n";

//     std::cout<<"\n\nFIRME CON ROTAZIONE\n";
//     signature1 = oph.computeSignature(coppia.first, true);
//     signature2 = oph.computeSignature(coppia.second, true);
//     StampaVettore::printVector(signature1);
//     StampaVettore::printVector(signature2);
//     std::cout<<"STIMA: " << JS::approx(signature1, signature2, k) <<"\n";
// }
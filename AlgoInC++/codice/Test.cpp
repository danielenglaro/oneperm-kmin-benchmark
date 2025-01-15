#include "Test.h"

// Implementazione dei metodi privati
std::vector<uint64_t> Test::generate_random_set(int n, int m) {
    std::vector<uint64_t> set;
    set.reserve(n);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, m);
    
    while (set.size() < n) {
        int num = dis(gen);
        if (std::find(set.begin(), set.end(), num) == set.end()) {
            set.push_back(num);
        }
    }
    return set;
}

// void Test::compute_signature(const std::vector<int>& set, int k) {
//     // Implementa qui la logica per calcolare la signature
//     // Questo è solo un placeholder
// }

void Test::save_result(const std::string& filename, int param, double time) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << param << "," << time << "\n";
        file.close();
    }
}

// Implementazione dei metodi pubblici
void Test::test_time_vs_n(int k_fixed, std::vector<int> n_values, int repetitions, int m) {
    std::vector<std::string> algoritmi = {"kMinHash", "OPH", "FSS"};
    for (std::string algoritmo : algoritmi)
    {
        for(int n : n_values) {
            std::vector<double> times;        // Crea un vector vuoto per memorizzare i tempi
            times.reserve(repetitions);       // Riserva spazio in memoria per 'repetitions' elementi
            std::vector<uint64_t> set = generate_random_set(n, m);
            for(int rep = 0; rep < repetitions; rep++) {
                size_t seed = time(NULL);
                auto start = std::chrono::high_resolution_clock::now();
                if (algoritmo == "kMinHash"){
                    KMinHash kMinHash(k_fixed, m, seed);
                    kMinHash.computeSignature(set);
                }
                else if (algoritmo == "OPH"){
                    OnePermutation oph(k_fixed, m, seed);
                    oph.computeSignature(set);
                }
                else if (algoritmo == "FSS"){
                    FastSimilaritySketching fss(k_fixed, m, seed);
                    fss.computeSignature(set);
                }
                
                auto end = std::chrono::high_resolution_clock::now();
                
                double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                times.push_back(duration); 
            }
            
            double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / repetitions;
            save_result("time_vs_n_" + algoritmo + ".csv", n, avg_time);
        }
    }
}

void Test::test_time_vs_k(std::vector<int> k_values, int n_fixed, int repetitions, int m) {
    std::vector<std::string> algoritmi = {"kMinHash", "OPH", "FSS"};
    for (std::string algoritmo : algoritmi)
    {
        for(int k : k_values) {
            std::vector<double> times;        // Crea un vector vuoto per memorizzare i tempi
            times.reserve(repetitions);       // Riserva spazio in memoria per 'repetitions' elementi
            std::vector<uint64_t> set = generate_random_set(n_fixed, m);
            for(int rep = 0; rep < repetitions; rep++) {
                size_t seed = time(NULL);
                auto start = std::chrono::high_resolution_clock::now();
                if (algoritmo == "kMinHash"){
                    KMinHash kMinHash(k, m, seed);
                    kMinHash.computeSignature(set);
                }
                else if (algoritmo == "OPH"){
                    OnePermutation oph(k, m, seed);
                    oph.computeSignature(set);
                }
                else if (algoritmo == "FSS"){
                    FastSimilaritySketching fss(k, m, seed);
                    fss.computeSignature(set);
                }
                
                auto end = std::chrono::high_resolution_clock::now();
                
                double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                times.push_back(duration); 
            }
            
            double avg_time = std::accumulate(times.begin(), times.end(), 0.0) / repetitions;
            save_result("time_vs_k_" + algoritmo + ".csv", k, avg_time);
        }
    }
}
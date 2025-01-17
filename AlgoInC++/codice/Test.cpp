#include "Test.h"

// Funzione per generare un set di numeri casuali unici
// Input:
// - n: dimensione del set da generare
// - m: modulo dell'universo, il massimo valore che un numero casuale può assumere (compreso tra 1 e m)
// Output:
// - Restituisce un vettore lungo n di numeri casuali unici tra 1 e m
std::vector<uint64_t> Test::generate_random_set(int n, int m)
{
    std::vector<uint64_t> set;
    set.reserve(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, m);

    while (static_cast<int>(set.size()) < n)
    {
        int num = dis(gen);
        if (std::find(set.begin(), set.end(), num) == set.end())
        {
            set.push_back(num);
        }
    }
    return set;
}

// Funzione per testare il tempo di esecuzione in funzione di n (dimensione del set)
// Input:
// - k_fixed: un valore fisso per k, lunghezza dello sketch
// - n_values: un vettore che contiene i diversi valori di n per i quali eseguire il test
// - repetitions: il numero di volte che il test deve essere ripetuto per ogni dimensione n
// - m: modulo dell'universo
// Output:
// - Scrive i risultati dei test in un file CSV chiamato "time_results_n.csv"
void Test::test_time_vs_n(int k_fixed, std::vector<int> n_values, int repetitions, int m)
{
    std::string output_file = "time_results_n.csv";

    // Apri il file e scrivi l'header
    std::ofstream file;
    file.open(output_file);
    file << "Algoritmo;Dimensione (n);Funzione hash;Tempo di esecuzione\n";
    file.close();

    std::vector<std::string> algoritmi = {"KMH", "OPH", "FSS"};

    // Inizializza il generatore di numeri casuali
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::numeric_limits<size_t>::max());

    for (std::string algoritmo : algoritmi)
    {
        for (int n : n_values)
        {
            std::vector<double> times;  // Crea un vector vuoto per memorizzare i tempi
            times.reserve(repetitions); // Riserva spazio in memoria per 'repetitions' elementi
            std::vector<uint64_t> set = generate_random_set(n, m);
            for (int rep = 0; rep < repetitions; rep++)
            {
                file.open(output_file, std::ios::app);

                size_t seed = dis(gen);

                auto start = std::chrono::high_resolution_clock::now();
                if (algoritmo == "KMH")
                {
                    KMinHash kMinHash(k_fixed, m, seed);
                    kMinHash.computeSignature(set);
                }
                else if (algoritmo == "OPH")
                {
                    OnePermutation oph(k_fixed, m, seed);
                    oph.computeSignature(set);
                }
                else if (algoritmo == "FSS")
                {
                    FastSimilaritySketching fss(k_fixed, m, seed);
                    fss.computeSignature(set);
                }
                auto end = std::chrono::high_resolution_clock::now();

                double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                times.push_back(duration);

                file << algoritmo << ";" << n << ";" << rep + 1 << ";" << duration << "\n";
                file.close();
            }
        }
    }
}

// Funzione per testare il tempo di esecuzione in funzione di k (size dello sketch)
// Input:
// - k_values: un vettore contenente i diversi valori di k per i quali eseguire il test
// - n_fixed: il valore fisso per n (dimensione del set)
// - repetitions: il numero di volte che il test deve essere ripetuto per ogni valore k
// - m: modulo dell'universo
// Output:
// - Scrive i risultati dei test in un file CSV chiamato "time_results_k.csv"
void Test::test_time_vs_k(std::vector<int> k_values, int n_fixed, int repetitions, int m)
{
    std::string output_file = "time_results_k.csv";

    std::ofstream file;
    file.open(output_file);
    file << "Algoritmo;Dimensione (k);Funzione hash;Tempo di esecuzione\n";
    file.close();

    std::vector<std::string> algoritmi = {"KMH", "OPH", "FSS"};

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::numeric_limits<size_t>::max());

    for (std::string algoritmo : algoritmi)
    {
        for (int k : k_values)
        {
            std::vector<double> times;
            times.reserve(repetitions);
            std::vector<uint64_t> set = generate_random_set(n_fixed, m);
            for (int rep = 0; rep < repetitions; rep++)
            {
                file.open(output_file, std::ios::app);

                size_t seed = dis(gen);
                auto start = std::chrono::high_resolution_clock::now();
                if (algoritmo == "KMH")
                {
                    KMinHash kMinHash(k, m, seed);
                    kMinHash.computeSignature(set);
                }
                else if (algoritmo == "OPH")
                {
                    OnePermutation oph(k, m, seed);
                    oph.computeSignature(set);
                }
                else if (algoritmo == "FSS")
                {
                    FastSimilaritySketching fss(k, m, seed);
                    fss.computeSignature(set);
                }

                auto end = std::chrono::high_resolution_clock::now();

                double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                times.push_back(duration);

                file << algoritmo << ";" << k << ";" << rep + 1 << ";" << duration << "\n";
                file.close();
            }
        }
    }
}
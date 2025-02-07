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

//metodo per contare empty bin
size_t Test::countEmptyBins(std::vector<uint64_t> s, size_t k){
    size_t empty = 0;
    for (size_t i = 0; i < k; i++)
        if (s[i] == UINT64_MAX) empty++;
    return empty;
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
    std::string output_file = "time_results_k=" + std::to_string(k_fixed) + ".csv";

    // Apri il file e scrivi l'header
    std::ofstream file;
    file.open(output_file);
    file << "Algoritmo;Dimensione (n);Funzione hash;Tempo di esecuzione\n";
    file.close();

    std::vector<std::string> algoritmi = {"KMH", "OPH", "OPH_ROT"};

    // Inizializza il generatore di numeri casuali
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::numeric_limits<size_t>::max());

    // Inizializza barra di loading
    int total_iterations = algoritmi.size() * n_values.size() * repetitions;
    int current_iteration = 0;
    std::cout << "\n\n-- Test Tempo con k=" + std::to_string(k_fixed)+" --\n";

    for (int n : n_values)
    {   
        std::vector<uint64_t> set = generate_random_set(n, m);

        for (std::string algoritmo : algoritmi)
        {
            std::vector<double> times;  // Crea un vector vuoto per memorizzare i tempi
            times.reserve(repetitions); // Riserva spazio in memoria per 'repetitions' elementi
            
            for (int rep = 0; rep < repetitions; rep++)
            {

                size_t seed = dis(gen);

                std::unique_ptr<KMinHash> kMinHash;
                std::unique_ptr<OnePermutation> oph;

                if (algoritmo == "KMH") kMinHash = std::make_unique<KMinHash>(k_fixed, m, seed);
                else oph = std::make_unique<OnePermutation>(k_fixed, m, seed);

                auto start = std::chrono::high_resolution_clock::now();
                if (algoritmo == "KMH") kMinHash->computeSignature(set);
                else if (algoritmo == "OPH") oph->computeSignature(set,false);
                else if (algoritmo == "OPH_ROT") oph->computeSignature(set,true);
                auto end = std::chrono::high_resolution_clock::now();

                double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                times.push_back(duration);

                file.open(output_file, std::ios::app);
                file << algoritmo << ";" << n << ";" << rep + 1 << ";" << duration << "\n";
                file.close();

                // Aggiorna progresso barra di caricamento
                current_iteration++;
            }
            // Aggiorna la barra di caricamento
            int progress = static_cast<int>((static_cast<double>(current_iteration) / total_iterations) * 100);
            std::cout << "\r    Progresso: " << progress << "%" << std::flush;
        }
    }
    std::cout << "\nCompletato!" << std::endl;
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
    std::string output_file = "time_results_n=" + std::to_string(n_fixed) + ".csv";

    std::ofstream file;
    file.open(output_file);
    file << "Algoritmo;Dimensione (k);Funzione hash;Tempo di esecuzione\n";
    file.close();

    std::vector<std::string> algoritmi = {"KMH", "OPH", "OPH_ROT"};

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::numeric_limits<size_t>::max());

    std::vector<uint64_t> set = generate_random_set(n_fixed, m);

    // Inizializza barra di loading
    int total_iterations = algoritmi.size() * k_values.size() * repetitions;
    int current_iteration = 0;
    std::cout << "\n\n-- Test Tempo con n=" + std::to_string(n_fixed)+" --\n";

    for (std::string algoritmo : algoritmi)
    {
        for (int k : k_values)
        {
            std::vector<double> times;
            times.reserve(repetitions);
            
            for (int rep = 0; rep < repetitions; rep++)
            {

                size_t seed = dis(gen);

                std::unique_ptr<KMinHash> kMinHash;
                std::unique_ptr<OnePermutation> oph;

                if (algoritmo == "KMH") kMinHash = std::make_unique<KMinHash>(k, m, seed);
                else oph = std::make_unique<OnePermutation>(k, m, seed);

                auto start = std::chrono::high_resolution_clock::now();
                if (algoritmo == "KMH") kMinHash->computeSignature(set);
                else if (algoritmo == "OPH") oph->computeSignature(set, false);
                else if (algoritmo == "OPH_ROT") oph->computeSignature(set, true);
                auto end = std::chrono::high_resolution_clock::now();

                double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                times.push_back(duration);

                file.open(output_file, std::ios::app);
                file << algoritmo << ";" << k << ";" << rep + 1 << ";" << duration << "\n";
                file.close();

                // Aggiorna progresso barra di caricamento
                current_iteration++;
            }
            // Aggiorna barra di loading
            int progress = static_cast<int>((static_cast<double>(current_iteration) / total_iterations) * 100);
            std::cout << "\r    Progresso: " << progress << "%" << std::flush;
        }
    }
    std::cout << "\nCompletato!" << std::endl;
}

void Test::test_quality(int k, int n, int repetitions, int m) {
    std::string output_file = "quality_results_k=" + std::to_string(k) + "_n=" + std::to_string(n) + ".csv";

    // Apri il file e scrivi l'header
    std::ofstream file;
    file.open(output_file);
    file << "Algoritmo;Jaccard_reale;Ripetizione;Jaccard_stimata\n";
    file.close();

    std::vector<double> jaccard_values = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};

    std::vector<std::string> algoritmi = {"KMH", "OPH", "OPH_ROT"};

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::numeric_limits<size_t>::max());

    // Inizializza barra di loading
    int total_iterations = algoritmi.size() * jaccard_values.size() * repetitions;
    int current_iteration = 0;
    std::cout << "\n\n-- Test Qualità con k=" + std::to_string(k)+" --\n";


    for (double jaccard_target : jaccard_values) {
                std::string esegui = "python3 script.py 1 "+ std::to_string(n) + " " + std::to_string(jaccard_target) + " " + std::to_string(m);
                system(esegui.c_str());

                std::ostringstream ss;
                ss << std::fixed << std::setprecision(1) << jaccard_target;
                std::string filename = "dataset_" + ss.str() + ".txt";

                // Aspetta che il file esista e sia accessibile
                int tentativi = 0;
                const int max_tentativi = 10;
                bool file_pronto = false;

                while (tentativi < max_tentativi && !file_pronto) {
                    std::ifstream check_file(filename);
                    if (check_file.good()) {
                        // Verifica che il file sia completo
                        check_file.seekg(0, std::ios::end);
                        if (check_file.tellg() > 0) {
                            file_pronto = true;
                            check_file.close();
                            break;
                        }
                    }
                    check_file.close();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Aspetta 100ms
                    tentativi++;
                }

                if (!file_pronto) {
                    // std::cerr << "Timeout: il file non è stato creato correttamente" << std::endl;
                    continue;
                    }

                std::pair<std::vector<uint64_t>, std::vector<uint64_t>> coppia = LettoreFile::read(filename)[0];
                float jaccard_exact = JS::esatta(coppia.first, coppia.second);

            for (std::string algoritmo : algoritmi) {

                for (int rep = 0; rep < repetitions; rep++) {
                    
                    size_t seed = dis(gen);
                    float jaccard_estimated = -1; //iniziallizato a -1 per verificare errori

                    if (algoritmo == "KMH") {
                        KMinHash kMinHash(k, m, seed);
                        auto signature1 = kMinHash.computeSignature(coppia.first);
                        auto signature2 = kMinHash.computeSignature(coppia.second);
                        jaccard_estimated = JS::approx(signature1, signature2, k);
                    }
                    else if (algoritmo == "OPH") {
                        OnePermutation oph(k, m, seed);
                        auto signature1 = oph.computeSignature(coppia.first, false);
                        auto signature2 = oph.computeSignature(coppia.second, false);
                        jaccard_estimated = JS::approxEB(signature1, signature2, k);
                    }
                    else if (algoritmo == "OPH_ROT") {
                        OnePermutation oph(k, m, seed);
                        auto signature1 = oph.computeSignature(coppia.first, true);
                        auto signature2 = oph.computeSignature(coppia.second, true);
                        jaccard_estimated = JS::approx(signature1, signature2, k);
                    }

                    file.open(output_file, std::ios::app);
                    file << algoritmo << ";" << jaccard_exact << ";" 
                         << rep + 1 << ";" << jaccard_estimated << "\n";
                    file.close();


                    // Aggiorna progresso barra di caricamento
                    current_iteration++;
                }

                // Aggiorna barra di loading
                int progress = static_cast<int>((static_cast<double>(current_iteration) / total_iterations) * 100);
                std::cout << "\r    Progresso: " << progress << "%" << std::flush;
            }
    }
}

void Test::test_emptyBins(int k_fixed, std::vector<int> n_values, int repetitions, int m)
{
    std::string output_file = "emptyBins_results_k=" + std::to_string(k_fixed) + ".csv";

    // Apri il file e scrivi l'header
    std::ofstream file;
    file.open(output_file);
    file << "Algoritmo;Dimensione (n);Funzione hash;Numero di Bins\n";
    file.close();

    // Inizializza il generatore di numeri casuali
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::numeric_limits<size_t>::max());

    // Inizializza barra di loading
    int total_iterations = n_values.size() * repetitions;
    int current_iteration = 0;
    std::cout << "\n\n-- Test Empty Bin con k=" + std::to_string(k_fixed)+" --\n";

    for (int n : n_values)
    {   
        std::vector<uint64_t> set = generate_random_set(n, m);
        for (int rep = 0; rep < repetitions; rep++)
        {
            size_t seed = dis(gen);

            OnePermutation oph(k_fixed, m, seed);
            std::vector<uint64_t> signature = oph.computeSignature(set,false);
            size_t emptyBins = countEmptyBins(signature, k_fixed);
    
            file.open(output_file, std::ios::app);
            file << "OPH_SENZA_ROT" << ";" << n << ";" << rep + 1 << ";" << emptyBins << "\n";
            file.close();

            // Aggiorna progresso barra di caricamento
            current_iteration++;
        }
        // Aggiorna la barra di caricamento
        int progress = static_cast<int>((static_cast<double>(current_iteration) / total_iterations) * 100);
        std::cout << "\r    Progresso: " << progress << "%" << std::flush;
    }
    std::cout << "\nCompletato!" << std::endl;
}
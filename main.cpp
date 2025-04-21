#include "inc/algorithms.h"
#include "inc/test.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class Algorithm {
    double (*f)(std::vector<Point>);    /* algorithm to test */
public:
    std::string name;                   /* algorith name */

    Algorithm(double (*dist_func)(std::vector<Point>), std::string func_name)
        : f(dist_func),  name(func_name) {}
    double call(std::vector<Point> points) {
        return f(points);
    }
};

std::string CSV_FORMAT = "NAME;EXPONENT;SIZE;TIME";
std::string CSV_LOCATION = "result.csv";

void test(std::vector<Algorithm> algorithms, std::vector<double>size_exps, long long repetitions) {

    std::ofstream file(CSV_LOCATION);
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return;
    }
    file << CSV_FORMAT << std::endl;
    
    Clock clock;
    clock.start();
    RealRandom random(0, 100);
    long long mismatch_count = 0;

    /* por cada tamaño de entrada */
    for (double exp: size_exps) {
        long long size = round(pow(2, exp));

        std::vector<long long> total_time(algorithms.size()); /* tiempo total (para sacar promedio) */
        for (unsigned long long i = 0; i < algorithms.size(); i++) {
            total_time[i] = 0;
        }

        /* por cada repetición */
        for (long long i = 0; i < repetitions; i++) {
            auto points = random.randomPointVector(size); /* entrada aleatoria */
            std::vector<double> output(algorithms.size()); /* output (para comparar) */

            for (unsigned long long j = 0; j < algorithms.size(); j++) { /* medimos el tiempo de cada algoritmo*/
                clock.lap();
                output[j] = algorithms[j].call(points);
                total_time[j] += clock.lap();
            }

            bool mismatch = false; /* comparamos mismatches */
            for (unsigned long long j = 0; j < algorithms.size(); j++) {
                for (unsigned long long k = 0; k < algorithms.size(); k++) {
                    if (output[j] != output[k]) mismatch = true;
                }
            }
            if (mismatch) mismatch_count++;
        }

        /* imprimimos resultados en el .csv */
        for (unsigned long long i = 0; i < algorithms.size(); i++) {
            file << algorithms[i].name << ";";
            file << exp << ";";
            file << size << ";";
            file << total_time[i]/repetitions << std::endl;
        }

        double progress_ratio = (exp - size_exps.front())/(size_exps.back() - size_exps.front());
        std::cout << "  " << round(1000*progress_ratio)/10 << "\t%" << std::endl;
    }

    std::cout << "mismatch counter: " << mismatch_count << std::endl;
}

int main() {
    Algorithm algo1(brute_force, "brute_force");
    Algorithm algo2(divide_and_conquer, "divide_and_conquer");
    Algorithm algo3(brute_force_upgrade, "better_brute_force");
    Algorithm algo4(divide_and_conquer_upgrade, "better_divide_and_conquer");

    std::vector<double> size_exps;
    for (double i = 3; i <= 15 + 0.1; i += 0.25) {
        size_exps.push_back(i);
    }

    long long repetitions = 30;

    test({algo1, algo3, algo2, algo4}, size_exps, repetitions);

    return 0;
}
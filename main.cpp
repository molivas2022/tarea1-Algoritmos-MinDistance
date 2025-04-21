#include "inc/algorithms.h"
#include "inc/test.h"

#include <stdio.h>
#include <iostream>
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

std::string CSV_FORMAT = "NAME;SIZE;TIME";

void test(std::vector<Algorithm> algorithms, std::vector<long long>sizes, long long repetitions) {

    std::cout << CSV_FORMAT << std::endl;
    
    Clock clock;
    clock.start();
    RealRandom random(0, 100);
    long long mismatch_count = 0;

    /* por cada tamaño de entrada */
    for (long long size: sizes) {

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
            std::cout << algorithms[i].name << ";";
            std::cout << size << ";";
            std::cout << total_time[i]/repetitions << std::endl;
        }
    }

    std::cout << "mismatch counter: " << mismatch_count << std::endl;
}

int main() {
    Algorithm algo1(brute_force, "Brute force");
    Algorithm algo2(divide_and_conquer, "Divide and conquer");

    std::vector<long long > sizes;
    for (int i = 3; i <= 12; i++) {
        sizes.push_back(1 << i);
    }

    long long repetitions = 30;

    test({algo1, algo2}, sizes, repetitions);

    return 0;
}
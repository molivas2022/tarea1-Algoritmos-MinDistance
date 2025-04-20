#include "inc/algorithms.h"
#include "inc/test.h"

#include <stdio.h>
#include <cmath>

int main() {
    Clock clock;
    RealRandom random(0, 100);

    long long size = 1 << 12;
    auto set = random.randomPointVector(size);

    clock.start();
    auto time = clock.lap();
    double value;
    
    time = clock.lap();
    value = brute_force(set);
    time = clock.lap();
    printf("Brute force             Return value: %.15f     Elapsed time: %.0f\n", value, time);

    time = clock.lap();
    value = divide_and_conquer(set);
    time = clock.lap();
    printf("Divide and conquer      Return value: %.15f     Elapsed time: %.0f\n", value, time);
}
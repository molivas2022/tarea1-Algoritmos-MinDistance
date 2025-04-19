#include "inc/algorithms.h"

#include <stdio.h>

int main() {
    std::vector<Point> space;

    Point p1 = Point(1, 2);
    Point p2 = Point(4, 1);
    Point p3 = Point(-6, 1);
    Point p4 = Point(-3, -3);
    Point p5 = Point(-3, -9);


    space.push_back(p1);
    space.push_back(p2);
    space.push_back(p3);
    space.push_back(p4);
    space.push_back(p5);

    double min_bruteforce = brute_force(space);
    double min_divideandconquer = divide_and_conquer(space);
    printf("Brute force: %.15f\nDivide and Conquer: %.15f\n", min_bruteforce, min_divideandconquer);
}
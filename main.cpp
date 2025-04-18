#include "inc/algorithms.h"

#include <iostream>

int main() {
    std::vector<Point> space = std::vector<Point>();

    Point p1 = Point(1, 2);
    Point p2 = Point(4, 1);
    Point p3 = Point(-6, 1);
    Point p4 = Point(-3, -3);
    Point p5 = Point(-3, -2);


    space.push_back(p1);
    space.push_back(p2);
    space.push_back(p3);
    space.push_back(p4);
    space.push_back(p5);

    double min_dist = brute_force(space);
    std::cout << min_dist << "\n";
}
#include "../inc/algorithms.h"

#include <iostream>
#include <math.h>

double brute_force(std::vector<Point> points) {
    double min_dist = __DBL_MAX__;

    for (int i = 0; i < (int) points.size(); i++) {
        for (int j = 0; j < (int) points.size(); j++) {
            if (i == j) continue;
            
            Point p1 = points.at(i);
            Point p2 = points.at(j);
            
            double dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
            if (dist < min_dist) min_dist = dist;
        }
    }

    return min_dist;
}
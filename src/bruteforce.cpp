#include "../inc/algorithms.h"

#include <iostream>
#include <cmath>

double brute_force(std::vector<Point> points) {
    double min_dist = __DBL_MAX__;

    for (int i = 0; i < (int) points.size(); i++) {
        for (int j = 0; j < (int) points.size(); j++) {
            if (i == j) continue;
            
            Point p1 = points.at(i);
            Point p2 = points.at(j);
            
            double dist = p1.distance_with(p2);
            if (dist < min_dist) min_dist = dist;
        }
    }

    return min_dist;
}

double brute_force_squared(std::vector<Point> points) {
    double min_dist = __DBL_MAX__;

    for (int i = 0; i < (int) points.size(); i++) {
        for (int j = i+1; j < (int) points.size(); j++) {
            
            Point p1 = points.at(i);
            Point p2 = points.at(j);
            
            double dist = p1.square_dist_with(p2);
            if (dist < min_dist) min_dist = dist;
        }
    }

    return min_dist;
}

double brute_force_upgrade(std::vector<Point> points) {
    double min_dist = __DBL_MAX__;

    for (int i = 0; i < (int) points.size(); i++) {
        for (int j = i+1; j < (int) points.size(); j++) {
            
            Point p1 = points.at(i);
            Point p2 = points.at(j);
            
            double dist = p1.square_dist_with(p2);
            if (dist < min_dist) min_dist = dist;
        }
    }

    return sqrt(min_dist);
}
#pragma once

#include <math.h>

struct Point {
    double x;
    double y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    double distance_with(Point point2) {
        return sqrt( pow(this->x - point2.x, 2) + pow(this->y - point2.y, 2) );
    }
    double square_dist_with(Point point2) {
        return (pow(this->x - point2.x, 2) + pow(this->y - point2.y, 2));
    }
};
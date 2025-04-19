#pragma once

#include "point.h"

#include <vector>

enum component {X, Y};

double brute_force(std::vector<Point> points);
double divide_and_conquer(std::vector<Point> points);
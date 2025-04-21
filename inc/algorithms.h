#pragma once

#include "point.h"

#include <vector>

enum component {X, Y};

double brute_force(std::vector<Point> points);
double divide_and_conquer(std::vector<Point> points);
double divide_and_conquer_upgrade(std::vector<Point> points);
double brute_force_squared(std::vector<Point> points);
double brute_force_upgrade(std::vector<Point> points);
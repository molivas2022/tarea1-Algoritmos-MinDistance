#include "../inc/test.h"

Clock::Clock() {
    start();
}

void Clock::start() {
    using namespace std::chrono;
    _start = high_resolution_clock::now(); /* inicializa el cronometro */
    _lap = high_resolution_clock::now();
}

double Clock::lap() {
    using namespace std::chrono;
    high_resolution_clock::time_point _lastlap = _lap; /* llamado anterior a lap */
    _lap = high_resolution_clock::now(); /* nuevo llamado a lap */
    return duration_cast<nanoseconds>(_lap - _lastlap).count(); /* diferencia en nanosegundos */
}

double Clock::now() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now() - _start).count(); /* diferencia en nanosegundos */
}

RealRandom::RealRandom(double low, double high)
    : mt(std::random_device{}()), dist(low, high) {}

double RealRandom::randomDouble() {
    return dist(mt);
}

Point RealRandom::randomPoint() {
    return Point(randomDouble(), randomDouble());
}

std::vector<Point> RealRandom::randomPointVector(long long n) {
    std::vector<Point> vec;
    vec.reserve(n);
    for (int i = 0; i < n; ++i)
        vec.emplace_back(randomPoint());
    return vec;
}

IntegerRandom::IntegerRandom(long long low, long long high)
    : mt(std::random_device{}()), dist(low, high) {}

long long IntegerRandom::randomInteger() {
    return dist(mt);
}

Point IntegerRandom::randomPoint() {
    return Point(static_cast<double>(randomInteger()), static_cast<double>(randomInteger()));
}

std::vector<Point> IntegerRandom::randomPointVector(long long n) {
    std::vector<Point> vec;
    vec.reserve(n);
    for (int i = 0; i < n; ++i)
        vec.emplace_back(randomPoint());
    return vec;
}
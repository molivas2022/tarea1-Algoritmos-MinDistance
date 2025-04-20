#pragma once

#include <chrono>
#include <random>
#include <vector>
#include "point.h"

/* Clase auxiliar que proporciona métodos para medir tiempo (en milisegundos) */
class Clock {
    std::chrono::high_resolution_clock::time_point _start;
    std::chrono::high_resolution_clock::time_point _lap;
public:
    Clock();
    /* Inicia el cronometro */
    void start();
    /* Devuelve el tiempo (en nanosegundos) desde el último llamado a lap() */
    /* Si no se ha llamado previamente a lap(), devuelve el tiempo desde el llamado a start() */
    double lap();
    /* Devuelve el tiempo (en nanosegundos) desde el llamado a start() */
    double now();
};

/* Clase auxiliar que proporciona métodos para generar valores reales aleatorios */
class RealRandom {
    std::mt19937_64 mt;
    std::uniform_real_distribution<> dist;
public:
    RealRandom(double low, double high);
    /* Número real aleatorio */
    double randomDouble();
    /* Punto aleatorio */
    Point randomPoint();
    /* Vector de puntos aleatorios */
    std::vector<Point> randomPointVector(long long n);
};

/* Clase auxiliar que proporciona métodos para generar valores enteros aleatorios */
class IntegerRandom {
    std::mt19937_64 mt;
    std::uniform_int_distribution<> dist;
public:
    IntegerRandom(long long low, long long high);
    /* Número entero aleatorio */
    long long randomInteger();
    /* Punto aleatorio */
    Point randomPoint();
    /* Vector de puntos aleatorios */
    std::vector<Point> randomPointVector(long long n);
};

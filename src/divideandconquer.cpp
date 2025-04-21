#include "../inc/algorithms.h"

#include <stdio.h>
#include <algorithm>
#include <math.h>

/* FUNCIONES DEL HEAP */

// Obtiene el indice en el arreglo del nodo superior
int get_parent(int pos) {
    return ceil( (float) pos / 2.0f ) - 1;
}

// Obtiene el índice del nodo a la izquierda
int first_child(int pos) {
    return 2*pos + 1;
}

// Obtiene el índice del nodo a la derecha
int second_child(int pos) {
    return 2*pos + 2;
}

/* HEAPSORT */

// Ordenarlos con heapsort implementado con un arreglo por X o Y
std::vector<Point> orderByAscendant(std::vector<Point> points, component comp) {
    int heap_size = points.size(); 
    int heap_height = ceil( log2(heap_size + 1) );

    // Tamaño para evitar acceder a memoria no asignada
    int arr_size = (pow(2, heap_height) - 1);
    Point heap[arr_size];

    // Inserción
    for (int i = 0; i < heap_size; i++) {
        heap[i] = points.at(i);
        for (int pos = i; pos > 0; pos = get_parent(pos)) {
            int parent_pos = get_parent(pos);
            double pos_value = comp == X ? heap[pos].x : heap[pos].y;
            double parent_value = comp == X ? heap[parent_pos].x : heap[parent_pos].y;
            if (pos_value < parent_value) {
                Point temp = heap[parent_pos];
                heap[parent_pos] = heap[pos];
                heap[pos] = temp;
            } 
            else break;
        }
    }

    // Ordenamiento
    std::vector<Point> ordered;
    std::vector<bool> is_heap;
    is_heap.resize(arr_size);

    for (int i = 0; i < heap_size; i++) {
        is_heap[i] = true;
    }

    for (int i = 0; i < heap_size; i++) {
        ordered.push_back(heap[0]);
        int pos = 0;
        for (int i = 0; i < heap_height; i++) {
            int first_pos = first_child(pos);
            int second_pos = second_child(pos);
            
            if (first_pos >= arr_size && second_pos >= arr_size) break;
            if (!is_heap[first_pos] && !is_heap[second_pos]) break;
            
            double first_pos_value = is_heap[first_pos] ? ( comp == X ? heap[first_pos].x : heap[first_pos].y ) : __DBL_MAX__;
            double second_pos_value = is_heap[second_pos] ? ( comp == X ? heap[second_pos].x : heap[second_pos].y) : __DBL_MAX__;

            if (first_pos_value <= second_pos_value) {
                heap[pos] = heap[first_pos];
                heap[first_pos] = Point();
                pos = first_pos;
            }
            else {
                heap[pos] = heap[second_pos];
                heap[second_pos] = Point();
                pos = second_pos;
            }
        }
        is_heap[pos] = false;
    }
    
    return ordered;
}

/* DIVIDE AND CONQUER */

// Función recursiva con la implementación de divide and conquer
double div_and_conq_recursive(std::vector<Point> Xordered, std::vector<Point> Yordered) {
    int X_size = Xordered.size();
    
    // Casos base
    if (X_size == 2) {
        return Xordered[0].distance_with(Xordered[1]);
    }
    if (X_size == 3) {
        double d1 = Xordered[0].distance_with(Xordered[1]);
        double d2 = Xordered[1].distance_with(Xordered[2]);
        double d3 = Xordered[2].distance_with(Xordered[0]);
        double min12 = d1 < d2 ? d1 : d2;
        double min = min12 < d3 ? min12 : d3;
        return min; 
    }

    // Dividir
    int half = ceil( (double) X_size / 2.0 );
    double axis = (Xordered[half-1].x + Xordered[half].x) / 2.0;

    std::vector<Point> X_l;
    std::vector<Point> X_r;

    for (int i = 0; i < X_size; i++) {
        if (i < half) X_l.push_back(Xordered[i]);
        else X_r.push_back(Xordered[i]);
    }

    std::vector<Point> Y_l;
    std::vector<Point> Y_r;

    for (Point point : Yordered) {
        if (point.x < axis) Y_l.push_back(point);
        else Y_r.push_back(point);
    }

    // Conquistar

    double d_l = div_and_conq_recursive(X_l, Y_l);
    double d_r = div_and_conq_recursive(X_r, Y_r);

    // Combinar

    double d = d_l < d_r ? d_l : d_r;

    std::vector<Point> Y2;

    for (Point point : Yordered) {
        if (abs(axis - point.x) <= d) {
            Y2.push_back(point);
        }
    }

    for (int i = 0; i < (int) Y2.size(); i++) {
        int limit = i+7 < (int) Y2.size()-1 ? i+7 : Y2.size()-1;
        for (int j = i+1; j <= limit; j++) {
            if (Y2[i].distance_with(Y2[j]) < d) d = Y2[i].distance_with(Y2[j]);
        }
    }

    return d;
}

// Función que inicializa los dos arreglos ordenados por coordenada
double divide_and_conquer(std::vector<Point> points) {

    std::vector<Point> orderedX = orderByAscendant(points, X);
    std::vector<Point> orderedY = orderByAscendant(points, Y);

    return div_and_conq_recursive(orderedX, orderedY);
}

/* DIVIDE AND CONQUER MEJORADO */

double div_and_conq_recursive_upgrade(std::vector<Point> Xordered, std::vector<Point> Yordered) {
    int X_size = Xordered.size();
    
    // Se implementa brute force desde 2^5 = 32 hacia abajo
    if (X_size <= 32) {
        return brute_force_squared(Xordered);
    }

    // Dividir
    int half = ceil( (double) X_size / 2.0 );
    double axis = (Xordered[half-1].x + Xordered[half].x) / 2.0;

    std::vector<Point> X_l;
    std::vector<Point> X_r;

    for (int i = 0; i < X_size; i++) {
        if (i < half) X_l.push_back(Xordered[i]);
        else X_r.push_back(Xordered[i]);
    }

    std::vector<Point> Y_l;
    std::vector<Point> Y_r;

    for (Point point : Yordered) {
        if (point.x < axis) Y_l.push_back(point);
        else Y_r.push_back(point);
    }

    // Conquistar

    double d_l = div_and_conq_recursive_upgrade(X_l, Y_l);
    double d_r = div_and_conq_recursive_upgrade(X_r, Y_r);

    // Combinar

    double d = d_l < d_r ? d_l : d_r;

    std::vector<Point> Y2;

    for (Point point : Yordered) {
        if (abs(axis - point.x) <= d) {
            Y2.push_back(point);
        }
    }

    for (int i = 0; i < (int) Y2.size(); i++) {
        int limit = i+7 < (int) Y2.size()-1 ? i+7 : Y2.size()-1;
        for (int j = i+1; j <= limit; j++) {
            if (Y2[i].square_dist_with(Y2[j]) < d) d = Y2[i].square_dist_with(Y2[j]);
        }
    }

    return d;
}

double divide_and_conquer_upgrade(std::vector<Point> points) {

    std::vector<Point> orderedX = orderByAscendant(points, X);
    std::vector<Point> orderedY = orderByAscendant(points, Y);

    return div_and_conq_recursive_upgrade(orderedX, orderedY);
}
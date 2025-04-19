#include "../inc/algorithms.h"

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>

int get_parent(int pos) {
    return ceil( (float) pos / 2.0f ) - 1;
}

int first_child(int pos) {
    return 2*pos + 1;
}

int second_child(int pos) {
    return 2*pos + 2;
}

// Ordenarlos con heapsort por X o Y
std::vector<Point> orderByAscendant(std::vector<Point> points, component comp) {
    int heap_size = points.size(); 
    int heap_height = ceil( log2(heap_size + 1) );

    // tamaño para evitar acceder a memoria no asignada
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

double divide_and_conquer(std::vector<Point> points) {

    std::vector<Point> orderedX = orderByAscendant(points, X);
    std::vector<Point> orderedY = orderByAscendant(points, Y);

    return 0.0;
}
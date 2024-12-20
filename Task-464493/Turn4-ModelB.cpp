#include <iostream>
#include <chrono>
#include <omp.h>

const int SIZE = 1'000'000;

void access_with_index(int* arr) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = arr[i] * 2;
    }
}

void access_with_pointer(int* arr) {
    #pragma omp parallel for
    for (int* ptr = arr; ptr < arr + SIZE; ++ptr) {
        *ptr = *ptr * 2;
    }
}

int main() {
    int* array = new int[SIZE];

    // Initialize the array
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    // Measure index-based access
    auto start = std::chrono::high_resolution_clock::now();
    access_with_index(array);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> index_duration = end - start;
    std::cout << "Index-based access took " << index_duration.count() << " seconds with " << omp_get_max_threads() << " threads.\n";

    // Reinitialize the array
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    // Measure pointer-based access
    start = std::chrono::high_resolution_clock::now();
    access_with_pointer(array);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> pointer_duration = end - start;
    std::cout << "Pointer-based access took " << pointer_duration.count() << " seconds with " << omp_get_max_threads() << " threads.\n";

    delete[] array;
    return 0;
}

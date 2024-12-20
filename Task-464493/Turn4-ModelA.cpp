#include <iostream>
#include <omp.h>
#include <vector>

const int SIZE = 1'000'000;

void thread_indexing(int* arr) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = arr[i] * 2;
    }
}

void thread_pointer(int* arr) {
    #pragma omp parallel
    {
        int* ptr = arr + omp_get_thread_num() * (SIZE / omp_get_num_threads());
        for (int i = 0; i < SIZE / omp_get_num_threads(); ++i) {
            *ptr = *ptr * 2;
            ptr++;
        }
    }
}

int main() {
    int* array = new int[SIZE];

    // Initialize the array
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    // Measure index-based access
    double start = omp_get_wtime();
    thread_indexing(array);
    double end = omp_get_wtime();
    std::cout << "Index-based access took " << end - start << " seconds.\n";

    // Reinitialize the array
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i;
    }

    // Measure pointer-based access
    start = omp_get_wtime();
    thread_pointer(array);
    end = omp_get_wtime();
    std::cout << "Pointer-based access took " << end - start << " seconds.\n";

    delete[] array;
    return 0;
}

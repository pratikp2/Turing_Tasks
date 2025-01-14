#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

void accessArrayWithRowMajorOrder(int** array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Simulating some computation
            volatile int temp = array[i][j];
            temp++;
        }
    }
}

void accessArrayWithColumnMajorOrder(int** array, int rows, int cols) {
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            // Simulating some computation
            volatile int temp = array[i][j];
            temp++;
        }
    }
}

int main() {
    const int rows = 1000; // Adjust for larger sizes
    const int cols = 1000; // Adjust for larger sizes

    // Allocate a 2D array dynamically
    int** array = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols];
        // Initialize the array with random values
        for (int j = 0; j < cols; ++j) {
            array[i][j] = rand() % 100; // Random value
        }
    }

    // Measure time for row-major order access
    auto start = std::chrono::high_resolution_clock::now();
    accessArrayWithRowMajorOrder(array, rows, cols);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> rowMajorDuration = end - start;
    std::cout << "Row-major order access time: " << rowMajorDuration.count() << " seconds\n";

    // Measure time for column-major order access
    start = std::chrono::high_resolution_clock::now();
    accessArrayWithColumnMajorOrder(array, rows, cols);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> columnMajorDuration = end - start;
    std::cout << "Column-major order access time: " << columnMajorDuration.count() << " seconds\n";

    // Cleanup memory
    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}

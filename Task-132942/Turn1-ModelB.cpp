#include <iostream>
#include <chrono>
#include <random>

// Function to measure the time taken to access elements in the array
template <typename T>
double measure_access_time(T* arr, size_t size) {
    const size_t num_iterations = 10000000;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_iterations; ++i) {
        for (size_t j = 0; j < size; ++j) {
            arr[j];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    return time_span.count() / num_iterations;
}

int main() {
    const size_t array_size = 1000000;

    // Unaligned array
    int* unaligned_arr = new int[array_size];
    double unaligned_time = measure_access_time(unaligned_arr, array_size);

    // Aligned array using alignas
    alignas(64) int* aligned_arr = new int[array_size];
    double aligned_time = measure_access_time(aligned_arr, array_size);

    // Display the results
    std::cout << "Unaligned array access time: " << unaligned_time << " seconds" << std::endl;
    std::cout << "Aligned array access time: " << aligned_time << " seconds" << std::endl;

    // Delete the allocated memory
    delete[] unaligned_arr;
    delete[] aligned_arr;

    return 0;
}

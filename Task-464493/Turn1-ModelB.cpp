#include <iostream>
#include <array>
#include <chrono>

constexpr size_t SIZE = 10000000;

void sumUsingIndex(const double arr[]) {
    double sum = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        sum += arr[i];
    }
}

void sumUsingPointer(const double arr[]) {
    const double* ptr = arr;
    double sum = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        sum += *ptr;
        ++ptr;
    }
}

int main() {
    std::array<double, SIZE> arr;
    // Fill the array with random values
    // You can add your random number generation here.
    for (int i = 0; i < SIZE; i++) {
        arr[i] = 1.0;
    }

    // Benchmarking
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; ++i) {  // 10 iterations to average the result
        sumUsingIndex(arr.data());
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time taken using index: " << duration.count() << " microseconds" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; ++i) {
        sumUsingPointer(arr.data());
    }

    end_time = std::chrono::high_resolution_clock::now();
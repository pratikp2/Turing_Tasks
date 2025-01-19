#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <memory>
#include <random>
#include <chrono>
#include <algorithm>

template <typename T>
class PointerVector {
    // ... (Previous implementation goes here)
};

// Helper function for generating random data
template <typename T>
std::vector<T> generateRandomData(size_t size) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<T> data(size);
    std::uniform_int_distribution<T> dist(0, 1000);
    for (auto& i : data) {
        i = dist(g);
    }
    return data;
}

// Benchmark function for random access
template <typename T>
void benchmarkRandomAccess(const T* data, size_t size) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < size; ++i) {
        (void)data[i]; // Dummy use to avoid optimization out
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    std::cout << "Random Access: " << duration << " microseconds\n";
}

// Benchmark function for bulk modification
template <typename T>
void benchmarkBulkModify(T* data, size_t size) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    std::function<void(T*)> modifier = [](T* p) { if (p) *p *= 2; };
    for (size_t i = 0; i < size; ++i) {
        modifier(&data[i]);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    std::cout << "Bulk Modification: " << duration << " microseconds\n";
}

// Benchmark function for resizing
template <typename T>
void benchmarkResize(T& container, size_t size) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    container.reserve(size);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    std::cout << "Resizing: " << duration << " microseconds\n";
}

int main() {
    const size_t num_test_cases = 3; // Number of test sizes
    size_t test_sizes[] = {10000, 100000, 1000000}; // Dataset sizes for testing

    for (size_t test_case = 0; test_case < num_test_cases; ++test_case) {
        size_t size = test_sizes[test_case];

        // Generate random data
        std::vector<int> std_vector_data = generateRandomData<int>(size);

        // Create and fill PointerVector
        PointerVector<int> pointer_vector;
        for (const int& val : std_vector_data) {
            pointer_vector.push_back(val);
        }

        std::cout << "\nTest Size: " << size << "\n";

        // Benchmarks for std::vector
        std::cout << "std::vector:\n";
        benchmarkRandomAccess(std_vector_data.data(), size);
        benchmarkBulkModify(std_vector_data.data(), size);
        benchmarkResize(std_vector_data, size);

        // Benchmarks for PointerVector
        std::cout << "PointerVector:\n";
        benchmarkRandomAccess(pointer_vector.data(), size);
        benchmarkBulkModify(pointer_vector.data(), size);
        benchmarkResize(pointer_vector, size);
    }

    return 0;
}

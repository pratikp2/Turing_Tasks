#include <iostream>
#include <cstdlib>
#include <chrono>

void useArrayStatic(size_t size) {
    int arr[size]; // Static Array
    // Simple operation to make the compiler keep the array
    for (size_t i = 0; i < size; ++i) {
        arr[i] = i % 100; // Dummy operation
    }
}

void useArrayDynamic(size_t size) {
    int* arr = new int[size]; // Dynamically allocated array
    for (size_t i = 0; i < size; ++i) {
        arr[i] = i % 100; // Dummy operation
    }
    delete[] arr; // Ensure proper memory management
}

int main(int argc, char* argv[]) {
    std::cout << "Starting memory footprint analysis..." << std::endl;

    const size_t sizes[] = {1024, 10000, 1000000}; // Change as necessary

    for (const auto& size : sizes) {
        // Measure static array
        auto startStatic = std::chrono::high_resolution_clock::now();
        useArrayStatic(size);
        auto endStatic = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationStatic = endStatic - startStatic;

        // Measure dynamic array
        auto startDynamic = std::chrono::high_resolution_clock::now();
        useArrayDynamic(size);
        auto endDynamic = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationDynamic = endDynamic - startDynamic;

        // Output results
        std::cout << "Array Size: " << size << " bytes" << std::endl;
        std::cout << "Static Array Time: " << durationStatic.count() << " seconds" << std::endl;
        std::cout << "Dynamic Array Time: " << durationDynamic.count() << " seconds" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
    }

    return 0;
}

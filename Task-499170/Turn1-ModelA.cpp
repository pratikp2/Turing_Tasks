#include <iostream>
#include <cstring>
#include <chrono>
#include <vector>

void measureStrcpy(const char* source, size_t iterations) {
    char* destination = new char[strlen(source) + 1]; // Allocate memory for the destination

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        strcpy(destination, source); // Copying string
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "strcpy: Time taken for " << iterations << " iterations: " 
              << duration.count() << " seconds." << std::endl;

    delete[] destination; // Free allocated memory
}

void measureStrlen(const char* source, size_t iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        volatile size_t length = strlen(source); // Using volatile to prevent optimization
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "strlen: Time taken for " << iterations << " iterations: " 
              << duration.count() << " seconds." << std::endl;
}

int main() {
    const char* testString = "Hello, Edge Computing!";
    const size_t iterations = 1000000; // Number of iterations for measurement

    measureStrcpy(testString, iterations);
    measureStrlen(testString, iterations);

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Function to initialize memory (redundant but good practice for simulation)
void initializeMemory(char** data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            data[i][j] = static_cast<char>(rand() % 256);
        }
    }
}

// Function to perform operation on memory (simulates data processing)
void processMemory(char** data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            // Simple operation: Square the value (or any other complex operation)
            data[i][j] = data[i][j] * data[i][j];
        }
    }
}

int main() {
    // Set size of the dataset (RAM-dependent)
    const size_t size = 1024 * 1024; // 1MB in this case, adjust as needed

    std::cout << "Dataset size: " << size * size * sizeof(char) / (1024 * 1024) << " MB\n";

    // Allocate memory dynamically using new
    char** data = new char*[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = new char[size];
    }

    // Set the seed for the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    // Initialize memory
    std::cout << "Initializing memory...\n";
    initializeMemory(data, size);

    // Measure time to process memory
    std::cout << "Processing memory...\n";
    const clock_t begin = clock();

    processMemory(data, size);

    const clock_t end = clock();
    const double time_taken = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    // Free allocated memory
    for (size_t i = 0; i < size; i++) {
        delete[] data[i];
    }
    delete[] data;

    // Display execution time
    std::cout << "Execution time: " << time_taken << " seconds\n";

    return 0;
}

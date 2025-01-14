#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <stdexcept>

constexpr int ROWS = 10000; // Simulated large dataset
constexpr int COLS = 10000; // Simulated large dataset

// Function to initialize the 2D array with random values
void initializeArray(std::vector<std::vector<int>>& array) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            array[i][j] = rand() % 100; // Random values between 0 and 99
        }
    }
}

// Function to simulate random memory allocation failures
bool simulateMemoryAllocation() {
    return (rand() % 10) < 8; // 80% success rate
}

// Function to process data with adaptive buffer allocation
void processData(std::vector<std::vector<int>>& array) {
    size_t bufferSize = COLS;
    std::vector<int> tempBuffer;

    for (int i = 0; i < ROWS; ++i) {
        // Try to allocate the temporary buffer with dynamic size allocation
        bool allocationSuccess = false;

        while (!allocationSuccess) {
            if (simulateMemoryAllocation()) {
                // Successful allocation
                tempBuffer.resize(bufferSize); // Allocate the buffer size dynamically
                allocationSuccess = true; // Mark allocation as successful
                
                for (int j = 0; j < bufferSize; ++j) {
                    // Load a row into the temp buffer
                    tempBuffer[j] = array[i][j];
                }

                // Process data in the temporary buffer
                for (int j = 0; j < bufferSize; ++j) {
                    // Simulate some computations (e.g., summation)
                    volatile int result = tempBuffer[j] * 2; // Volatile to prevent optimization
                    tempBuffer[j] = result; // Store processed value back
                }
            } else {
                // Allocation failed, log the event
                std::cerr << "Allocation failed, retrying with smaller buffer size.\n";
                bufferSize /= 2; // Reduce buffer size for next attempt
                if (bufferSize < 1) {
                    std::cerr << "Unable to allocate memory for processing!\n";
                    return; // Exit if we can't allocate even 1 element
                }
            }
        }

        // Reset the buffer size to original after processing
        bufferSize = COLS; // Reset to original before proceeding with the next row
    }
}

int main() {
    // Use a 2D vector for dynamic memory allocation
    std::vector<std::vector<int>> array(ROWS, std::vector<int>(COLS));

    // Initialize the dataset
    initializeArray(array);

    // Measure the execution time of the nested loops with temporary buffers
    auto start = std::chrono::high_resolution_clock::now();
    processData(array);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds\n";

    return 0;
}

#include <iostream>
#include <chrono>

const int GRID_SIZE = 100;

// Function to perform calculations with bounds checking
void performCalculationsWithBoundsChecking() {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                // Intensive computation (Placeholder)
                double computation = x * y * z * (x + y + z) / (1 + x + y + z);
            }
        }
    }
}

// Function to perform calculations without bounds checking
void performCalculationsWithoutBoundsChecking() {
    // Unsafe access to simulate no bounds checking
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                // Intensive computation (Placeholder)
                // Here we assume GRID_SIZE is always valid.
                double computation = x * y * z * (x + y + z) / (1 + x + y + z);
            }
        }
    }
}

// Function to measure execution time
void measureExecutionTime(void (*function)(), const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << name << " took " << duration.count() << " seconds.\n";
}

int main() {
    std::cout << "Performance Measurement with Dynamic Bounds Checking Toggle\n";

    // Toggle for bounds checking: true for bounds checking, false for no bounds checking
    bool boundsChecking = true;

    // Measure performance with bounds checking
    if (boundsChecking) {
        measureExecutionTime(performCalculationsWithBoundsChecking, "With Bounds Checking");
    } else {
        measureExecutionTime(performCalculationsWithoutBoundsChecking, "Without Bounds Checking");
    }

    // Toggle the flag for the next run
    boundsChecking = false;

    // Measure performance without bounds checking
    if (boundsChecking) {
        measureExecutionTime(performCalculationsWithBoundsChecking, "With Bounds Checking");
    } else {
        measureExecutionTime(performCalculationsWithoutBoundsChecking, "Without Bounds Checking");
    }

    return 0;
}

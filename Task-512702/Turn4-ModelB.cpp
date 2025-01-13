#include <iostream>
#include <chrono>
#include <cstring>

const int GRID_SIZE = 100;

#define WITH_BOUNDS_CHECKING 1 // Default mode with bounds checking

void performCalculations(bool withBoundsChecking) {
    double computation;

    #ifdef WITH_BOUNDS_CHECKING
    if (withBoundsChecking) {
        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                for (int z = 0; z < GRID_SIZE; z++) {
                    computation = x * y * z * (x + y + z) / (1 + x + y + z);
                }
            }
        }
    } else {
        // Note: The performance difference will be minimal without actual data access
        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                for (int z = 0; z < GRID_SIZE; z++) {
                    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && z >= 0 && z < GRID_SIZE) {
                        computation = x * y * z * (x + y + z) / (1 + x + y + z);
                    }
                }
            }
        }
    }
    #else
    // Without bounds checking, we directly use the loops
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                computation = x * y * z * (x + y + z) / (1 + x + y + z);
            }
        }
    }
    #endif
}

void measureExecutionTime(void (*function)(bool), const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    function(true); // Perform with bounds checking
    auto endWithBounds = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> durationWithBounds = endWithBounds - start;
    std::cout << name << " (With Bounds Checking) took " << durationWithBounds.count() << " seconds.\n";

    start = std::chrono::high_resolution_clock::now();
    function(false); // Perform without bounds checking
    auto endWithoutBounds = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> durationWithoutBounds = endWithoutBounds - start;
    std::cout << name << " (Without Bounds Checking) took " << durationWithoutBounds.count() << " seconds.\n";
}

int main() {
    std::cout << "Performance Comparison of Loop Bounds Checking\n";

    measureExecutionTime(performCalculations, "Nested Loops");

    return 0;
}

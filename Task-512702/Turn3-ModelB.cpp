#include <iostream>
#include <chrono>
#include <omp.h>

const int GRID_SIZE = 100;

void performCalculationsWithBoundsCheckingAndOptimizedLoops() {
    #pragma GCC optimize("loop-unroll")
    #pragma GCC optimize("loop-vectorize")
    #pragma GCC optimize("no-frame-pointer-elim")

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                double computation = x * y * z * (x + y + z) / (1 + x + y + z);
            }
        }
    }
}

void performCalculationsWithBoundsCheckingAndOpenMP() {
    #pragma omp parallel for collapse(3)
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                double computation = x * y * z * (x + y + z) / (1 + x + y + z);
            }
        }
    }
}

int main() {
    std::cout << "Comparison of Optimized Loop Performance\n";

    measureExecutionTime(performCalculationsWithBoundsCheckingAndOptimizedLoops, "With GCC Optimized Loops");
    measureExecutionTime(performCalculationsWithBoundsCheckingAndOpenMP, "With OpenMP Parallelization");

    return 0;
}

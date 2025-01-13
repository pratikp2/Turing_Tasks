#include <iostream>
#include <chrono>
#include <vector>

const int GRID_SIZE = 100;

void computeWithoutBoundsCheck() {
    std::vector<std::vector<std::vector<double>>> grid(GRID_SIZE, std::vector<std::vector<double>>(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0)));

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                // Intensive computation
                grid[x][y][z] = (x * y * z) * 0.001; // Example computation
            }
        }
    }
}

void computeWithBoundsCheck() {
    std::vector<std::vector<std::vector<double>>> grid(GRID_SIZE, std::vector<std::vector<double>>(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0)));

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int z = 0; z < GRID_SIZE; z++) {
                // Intensive computation with bounds checking (although STL does not perform manual bounds checks)
                if (x < GRID_SIZE && y < GRID_SIZE && z < GRID_SIZE) {
                    grid[x][y][z] = (x * y * z) * 0.001; // Example computation
                }
            }
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    computeWithoutBoundsCheck();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time without bounds check: " << elapsed.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    computeWithBoundsCheck();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time with bounds check: " << elapsed.count() << " seconds." << std::endl;

    return 0;
}

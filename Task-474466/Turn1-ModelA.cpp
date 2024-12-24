#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>  // For parallel execution (C++17 and above)

void processMatrixTraditional(std::vector<std::vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j] *= matrix[i][j];  // Squaring the element
        }
    }
}

void processMatrixVectorized(std::vector<std::vector<int>>& matrix) {
    // Assuming we are using IT, which will respect vectorization automatically
    for (auto& row : matrix) { 
        std::transform(row.begin(), row.end(), row.begin(), [](int x) {
            return x * x;  // Squaring operation
        });
    }
}

void processMatrixParallel(std::vector<std::vector<int>>& matrix) {
    // Uses parallel STL (requires C++17 and compiler support)
    std::for_each(std::execution::par, matrix.begin(), matrix.end(), [](std::vector<int>& row) {
        std::transform(row.begin(), row.end(), row.begin(), [](int x) { return x * x; });
    });
}

int main() {
    const size_t N = 1000;
    const size_t M = 1000;
    std::vector<std::vector<int>> matrix(N, std::vector<int>(M, 1)); // Example with the initialized value of 1s

    // Traditional nested loop example
    std::cout << "Traditional approach" << std::endl;
    processMatrixTraditional(matrix);

    // Vectorized approach
    std::cout << "Vectorized approach" << std::endl;
    processMatrixVectorized(matrix);

    // Parallel processing (if supported)
    std::cout << "Parallel processing" << std::endl;
    processMatrixParallel(matrix);

    return 0;
}

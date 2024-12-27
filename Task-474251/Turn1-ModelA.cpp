#include <iostream>
#include <vector>
#include <future>
#include <numeric>

const int SIZE = 1000; // Size of the matrix

// Function to compute a row of the result matrix
std::vector<int> computeRow(const std::vector<std::vector<int>>& A,
                             const std::vector<std::vector<int>>& B,
                             int row) {
    std::vector<int> result(B[0].size(), 0);
    for (size_t j = 0; j < B[0].size(); ++j) {
        for (size_t k = 0; k < A[0].size(); ++k) {
            result[j] += A[row][k] * B[k][j];
        }
    }
    return result;
}

int main() {
    // Initialize matrices A and B
    std::vector<std::vector<int>> A(SIZE, std::vector<int>(SIZE, 1));
    std::vector<std::vector<int>> B(SIZE, std::vector<int>(SIZE, 1));
    std::vector<std::vector<int>> C(SIZE, std::vector<int>(SIZE, 0));

    std::vector<std::future<std::vector<int>>> futures;

    // Launch asynchronous tasks for each row
    for (int i = 0; i < SIZE; ++i) {
        futures.push_back(std::async(std::launch::async, computeRow, std::ref(A), std::ref(B), i));
    }

    // Collect results from futures
    for (int i = 0; i < SIZE; ++i) {
        C[i] = futures[i].get(); // This will block until the result is ready
    }

    // Output result (optional)
    std::cout << "Result C[0][0]: " << C[0][0] << std::endl; // Should be SIZE (1000)

    return 0;
}

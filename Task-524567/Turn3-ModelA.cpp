#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

// Function to perform matrix multiplication C = A * B
void matrix_mult(const double* A, const double* B, double* C, int N) {
    // Initialize the result matrix C to zero
    for (int i = 0; i < N; ++i) {
        // Use pointer arithmetic to access row i of C
        double* rowC = C + (i * N);
        for (int j = 0; j < N; ++j) {
            rowC[j] = 0.0; // C[i][j] = 0.0
        }
    }

    // Multiply matrices A and B
    for (int i = 0; i < N; ++i) {
        const double* rowA = A + (i * N); // Pointer to the ith row of A
        for (int j = 0; j < N; ++j) {
            const double* colB = B + j; // Pointer to the jth column of B
            // Use pointer arithmetic to access elements in the column of B
            for (int k = 0; k < N; ++k) {
                rowC[j] += rowA[k] * colB[k * N]; // C[i][j] += A[i][k] * B[k][j]
            }
        }
    }
}

// Function to print a matrix
void print_matrix(const double* matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int N = 512; // Size of NxN matrix
    double *A = new double[N * N]; // Allocate memory for matrix A
    double *B = new double[N * N]; // Allocate memory for matrix B
    double *C = new double[N * N]; // Allocate memory for result matrix C

    // Initialize matrices A and B with random values
    for (int i = 0; i < N * N; ++i) {
        A[i] = static_cast<double>(rand()) / RAND_MAX; // Random values for A
        B[i] = static_cast<double>(rand()) / RAND_MAX; // Random values for B
    }

    // Start timing the multiplication
    auto start = std::chrono::high_resolution_clock::now();

    // Perform matrix multiplication
    matrix_mult(A, B, C, N);

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Matrix multiplication completed in " << duration.count() << " seconds.\n";
    
    // Optionally, print the resulting matrix C
    // print_matrix(C, N);

    // Clean up allocated memory
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}

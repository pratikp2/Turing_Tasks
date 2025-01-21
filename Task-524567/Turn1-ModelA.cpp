#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

void matrix_mult(const double* A, const double* B, double* C, int N) {
    // Initialize matrix C to zero
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i * N + j] = 0.0;
        }
    }

    // Compute matrix product C = A * B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Use pointer arithmetic for matrix access
            const double* rowA = A + (i * N);
            const double* colB = B + j; // pobj - pointer to specific column start in B

            for (int k = 0; k < N; ++k) {
                C[i * N + j] += rowA[k] * colB[k * N]; // C[_row][j] += A[_row][k] * B[k][_col]
            }
        }
    }
}

void print_matrix(const double* matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int N = 512; // size of NxN matrix
    double *A = new double[N * N];
    double *B = new double[N * N];
    double *C = new double[N * N];

    // Initializing matrices A and B with random values
    for (int i = 0; i < N * N; ++i) {
        A[i] = static_cast<double>(rand()) / RAND_MAX;
        B[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Perform matrix multiplication and timing it
    auto start = std::chrono::high_resolution_clock::now();

    matrix_mult(A, B, C, N);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    std::cout << "Matrix multiplication completed in " << duration.count() << " seconds.\n";
    
    // Optionally, print the resulting matrix C
    // print_matrix(C, N);

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}

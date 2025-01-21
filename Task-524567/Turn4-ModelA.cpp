#include <iostream>
#include <cstdlib>
#include <ctime>

#define N 512   // Size of the matrices
#define BLOCK_SIZE 32  // Size of the block (adjust as needed for your cache size)

// Function to multiply two matrices using blocking
void matrix_mult_block(const double* A, const double* B, double* C, int blockSize) {
    // Initialize matrix C to zeros
    for (int i = 0; i < N * N; ++i) {
        C[i] = 0.0;
    }

    // Block matrix multiplication
    for (int i = 0; i < N; i += blockSize) {
        for (int j = 0; j < N; j += blockSize) {
            for (int k = 0; k < N; k += blockSize) {
                // Multiply submatrices
                for (int ii = i; ii < std::min(i + blockSize, N); ++ii) {
                    for (int jj = j; jj < std::min(j + blockSize, N); ++jj) {
                        double sum = 0.0;
                        for (int kk = k; kk < std::min(k + blockSize, N); ++kk) {
                            sum += A[ii * N + kk] * B[kk * N + jj];  // Access A and B directly
                        }
                        C[ii * N + jj] += sum;  // Accumulate result in C
                    }
                }
            }
        }
    }
}

void print_matrix(const double* matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    // Dynamically allocate memory for matrices A, B, and C
    double* A = new double[N * N];
    double* B = new double[N * N];
    double* C = new double[N * N];

    // Initialize matrices A and B with random values
    for (int i = 0; i < N * N; ++i) {
        A[i] = static_cast<double>(rand()) / RAND_MAX;
        B[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Perform matrix multiplication using blocking
    matrix_mult_block(A, B, C, BLOCK_SIZE);

    // Optionally print the resulting matrix C
    // std::cout << "Result Matrix C:\n";
    // print_matrix(C);

    // Memory clean up
    delete[] A;
    delete[] B;
    delete[] C;

    std::cout << "Matrix multiplication completed successfully!\n";

    return 0;
}

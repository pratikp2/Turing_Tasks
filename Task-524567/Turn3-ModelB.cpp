#include <iostream>
#include <cstdlib>
#include <ctime>

#define N 512   // Size of the matrices (you can change this as needed)

void matrix_mult(const double* A, const double* B, double* C) {

    // Initialize matrix C to zeros
    for (int i = 0; i < N * N; ++i) {
        C[i] = 0.0;
    }

    /* 
     * Multiply matrices A and B using pointers. 
     * We perform the multiplication element-wise 
     * and sum the results. 
     * Matrix A and B are assumed to be in row-major format.
     */
    for (int i = 0; i < N; ++i) {
        // Pointer to the i-th row in A
        const double* rowA = A + i * N;

        for (int j = 0; j < N; ++j) {
            // Pointer to the j-th column in B
            const double* colB = B + j;

            double sum = 0.0;

            // Accumulate the dot product of the i-th row in A and the j-th column in B
            for (int k = 0; k < N; ++k) {
                sum += rowA[k] * colB[k * N];
            }

            // Store the result in C
            C[i * N + j] = sum;
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

    // Perform matrix multiplication using pointers
    matrix_mult(A, B, C);

    /* 
     * Below is an optional section to print the result matrix C.
     * In a real-world application, you might skip this to avoid
     * excessive output and keep the computation efficient.
     */
    //std::cout << "Result Matrix C:\n";
    //print_matrix(C);

    // Memory clean up
    delete[] A;
    delete[] B;
    delete[] C;

    std::cout << "Matrix multiplication completed successfully!\n";

    return 0;
}

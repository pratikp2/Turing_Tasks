#include <iostream>
#include <cstdlib>
#include <ctime>

#define N 512   // Size of the matrices (you can change this as needed)
#define BLOCK_SIZE 16 // Choose an appropriate block size based on cache characteristics

void matrix_mult_blocked(const double* A, const double* B, double* C) {
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                double sum[BLOCK_SIZE][BLOCK_SIZE] = {};
                for (int ii = 0; ii < BLOCK_SIZE; ii++) {
                    for (int kk = 0; kk < BLOCK_SIZE; kk++) {
                        int idx_A_row = (i + ii) * N + (k + kk);
                        if (idx_A_row >= N * N)
                            break;
                        for (int jj = 0; jj < BLOCK_SIZE; jj++) {
                            int idx_B_col = (k + kk) * N + (j + jj);
                            if (idx_B_col >= N * N)
                                break;
                            sum[ii][jj] += A[idx_A_row] * B[idx_B_col];
                        }
                    }
                    if ((i + ii + BLOCK_SIZE) > N)
                        break;
                }
                for (int ii = 0; ii < BLOCK_SIZE; ii++) {
                    for (int jj = 0; jj < BLOCK_SIZE; jj++) {
                        int idx_C = (i + ii) * N + (j + jj);
                        if (idx_C >= N * N)
                            break;
                        C[idx_C] += sum[ii][jj];
                    }
                    if ((i + ii + BLOCK_SIZE) > N)
                        break;
                }
            }
            if ((j + BLOCK_SIZE) > N)
                break;
        }
        if ((i + BLOCK_SIZE) > N)
            break;
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

    // Perform matrix multiplication using blocking (tiling) technique
    matrix_mult_blocked(A, B, C);

    /* 
     * Commenting out the matrix printout to improve performance
     * for larger matrix sizes
     */
    //std::cout << "Result Matrix C:\n";
    //print_matrix(C);

    // Memory clean up
    delete[] A;
    delete[] B;
    delete[] C;

    std::cout << "Matrix multiplication completed successfully with blocking optimization!\n";

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 1024 // Make these constant based on your climate model matrices
#define N 1024
#define K 1024

void matrixMultiply(float* A, float* B, float* C) {
    // Use block-level matrix multiplication for improved cache locality
    const int BLOCK_SIZE = 32; // Choose a suitable block size

    for (int i = 0; i < M; i += BLOCK_SIZE) {
        for (int k = 0; k < K; k += BLOCK_SIZE) {
            float temp[BLOCK_SIZE][BLOCK_SIZE];

            #pragma omp parallel for
            for (int j = 0; j < BLOCK_SIZE; j++) {
                for (int p = 0; p < BLOCK_SIZE; p++) {
                    temp[j][p] = 0;
                    for (int l = 0; l < min(BLOCK_SIZE, K - k); l++) {
                        int idxA = (i + j) * K + k + l;
                        int idxB = (k + p) * N + l;
                        temp[j][p] += A[idxA] * B[idxB];
                    }
                }
            }

            #pragma omp parallel for
            for (int j = 0; j < BLOCK_SIZE; j++) {
                for (int p = 0; p < N; p++) {
                    int idxC = (i + j) * N + p;
                    for (int l = 0; l < min(BLOCK_SIZE, K - k); l++) {
                        int idxT = j * BLOCK_SIZE + l;
                        int idxB = k * N + p + l;
                        C[idxC] += temp[idxT][l] * B[idxB];
                    }
                }
            }
        }
    }
}


int main() {
    size_t matrixSize = M * N * sizeof(float);

    // Memory allocation for the matrices
    float* A = (float*) malloc(matrixSize);
    float* B = (float*) malloc(matrixSize);
    float* C = (float*) malloc(matrixSize);

    // Randomly initialize the matrices
    for (size_t i = 0; i < M * N; i++) {
        A[i] = (float) rand() / RAND_MAX;
        B[i] = (float) rand() / RAND_MAX;
    }

    // Perform matrix multiplication
    matrixMultiply(A, B, C);

    // Optional: perform verification by comparing with a reference implementation

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}

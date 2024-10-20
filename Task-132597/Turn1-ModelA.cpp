#include <iostream>
#include <chrono>

const int MATRIX_SIZE = 1024;

void matrixMultiply(const float* A, const float* B, float* C) {
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      float sum = 0.0f;
      for (int k = 0; k < MATRIX_SIZE; ++k) {
        sum += A[i * MATRIX_SIZE + k] * B[k * MATRIX_SIZE + j];
      }
      C[i * MATRIX_SIZE + j] = sum;
    }
  }
}

int main() {
  float* A = new float[MATRIX_SIZE * MATRIX_SIZE];
  float* B = new float[MATRIX_SIZE * MATRIX_SIZE];
  float* C = new float[MATRIX_SIZE * MATRIX_SIZE];

  // Initialize matrices A and B with random data
  for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; ++i) {
    A[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    B[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  }

  // Warm up the cache
  matrixMultiply(A, B, C);

  auto start = std::chrono::high_resolution_clock::now();

  // Matrix multiplication with optimization
  matrixMultiply(A, B, C);

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

  std::cout << "Execution time: " << time_span.count() << " seconds" << std::endl;

  delete[] A;
  delete[] B;
  delete[] C;
  return 0;
}
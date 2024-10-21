#include <iostream>
#include <omp.h>
#include <vector>

const int NUM_ELEMENTS = 10000000;

void calculateSquares(std::vector<int>& data) {
  #pragma omp parallel for
  for (int i = 0; i < static_cast<int>(data.size()); i++) {
    data[i] *= data[i];
  }
}

int main() {
  std::vector<int> data(NUM_ELEMENTS);

  // Initialize the data array
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    data[i] = i;
  }

  double startTime = omp_get_wtime();

  // Calculate squares of elements in parallel
  calculateSquares(data);

  double endTime = omp_get_wtime();

  std::cout << "Execution time: " << (endTime - startTime) << " seconds" << std::endl;

  return 0;
}
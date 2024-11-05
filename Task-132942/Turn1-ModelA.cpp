#include <iostream>
#include <chrono>
#include <array>

const int NUM_ELEMENTS = 10000000;
const int ARRAY_SIZE = sizeof(double) * NUM_ELEMENTS;

// Function to perform element-wise addition on two arrays
void addArrays(const double* src1, const double* src2, double* dest) {
	for (int i = 0; i < NUM_ELEMENTS; i++) {
		dest[i] = src1[i] + src2[i];
	}
}

int main() {
	// Unaligned arrays
	double* unaligned_arr1 = new double[NUM_ELEMENTS];
	double* unaligned_arr2 = new double[NUM_ELEMENTS];
	double* unaligned_result = new double[NUM_ELEMENTS];

	// Aligned arrays
	posix_memalign((void**)&aligned_arr1, sizeof(double), ARRAY_SIZE);
	posix_memalign((void**)&aligned_arr2, sizeof(double), ARRAY_SIZE);
	posix_memalign((void**)&aligned_result, sizeof(double), ARRAY_SIZE);

	// Initialize arrays with some data
	for (int i = 0; i < NUM_ELEMENTS; i++) {
		unaligned_arr1[i] = static_cast<double>(i);
		unaligned_arr2[i] = static_cast<double>(i) * 2.0;
	}

	// Measure time for unaligned array addition
	auto start = std::chrono::high_resolution_clock::now();
	addArrays(unaligned_arr1, unaligned_arr2, unaligned_result);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = end - start;
	std::cout << "Unaligned addition time: " << time_span.count() << " seconds" << std::endl;

	// Measure time for aligned array addition
	start = std::chrono::high_resolution_clock::now();
	addArrays(aligned_arr1, aligned_arr2, aligned_result);
	end = std::chrono::high_resolution_clock::now();
	time_span = end - start;
	std::cout << "Aligned addition time: " << time_span.count() << " seconds" << std::endl;

	// Free allocated memory
	delete[] unaligned_arr1;
	delete[] unaligned_arr2;
	delete[] unaligned_result;
	free(aligned_arr1);
	free(aligned_arr2);
	free(aligned_result);

	return 0;
}

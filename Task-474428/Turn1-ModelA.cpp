#include <iostream>
#include <vector>

const int N = 1000;

void nestedLoopRowMajor(int arr[N][N]) {
    for (int i = 0; i < N; ++i) { // Row-major order
        for (int j = 0; j < N; ++j) {
            arr[i][j] += 1; // Accessing in row-major order
        }
    }
}

void nestedLoopColumnMajor(int arr[N][N]) {
    for (int j = 0; j < N; ++j) { // Column-major order
        for (int i = 0; i < N; ++i) {
            arr[i][j] += 1; // Accessing in column-major order
        }
    }
}

int main() {
    int arr[N][N] = {0};

    // Test row-major loop
    nestedLoopRowMajor(arr);

    // Reset array
    std::fill(&arr[0][0], &arr[0][0] + sizeof(arr) / sizeof(int), 0);

    // Test column-major loop
    nestedLoopColumnMajor(arr);

    return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

void benchmarkSort() {
    const int size = 1000000;
    int* cArray = new int[size];
    std::vector<int> stlVector(size);

    // Initialize the arrays
    for (int i = 0; i < size; ++i) {
        cArray[i] = rand();
        stlVector[i] = rand();
    }

    // C library sort
    clock_t start = clock();
    std::qsort(cArray, size, sizeof(int), std::less<int>());
    clock_t end = clock();
    std::cout << "C library (qsort) time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    // STL sort
    start = clock();
    std::sort(stlVector.begin(), stlVector.end());
    end = clock();
    std::cout << "STL (sort) time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

    // Clean up
    delete[] cArray;

    // Optionally check if both arrays are sorted
    // for (int i = 1; i < size; ++i) {
    //     if (stlVector[i] < stlVector[i - 1] || cArray[i] < cArray[i - 1]) {
    //         std::cout << "Warning: Sort failed!\n";
    //         break;
    //     }
    // }
}

int main() {
    srand(time(0));
    benchmarkSort();
    return 0;
}
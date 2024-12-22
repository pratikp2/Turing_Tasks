#include <iostream>
#include <chrono>

int sumUsingPointer(int arr[], int size) {
    int sum = 0;
    int *ptr = arr;

    for (int i = 0; i < size; i++) {
        sum += *ptr;
        ptr++;
    }

    return sum;
}

int sumUsingIndexing(int arr[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum;
}

int main() {
    const int size = 10000000;
    int arr[size];

    // Initialize the array
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        int sum = sumUsingPointer(arr, size);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Sum using pointer: " << sum << "\n";
        std::cout << "Time taken: " << elapsed.count() << " seconds\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        int sum = sumUsingIndexing(arr, size);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Sum using indexing: " << sum << "\n";
        std::cout << "Time taken: " << elapsed.count() << " seconds\n";
    }

    return 0;
}

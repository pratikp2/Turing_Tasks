#include <iostream>

int main() {
    int* arr = new int[10];
    for (int i = 0; i < 10; ++i) {
        arr[i] = 0; // Initialize each element
    }
    std::cout << arr[5] << std::endl; // Now, this is safe
    delete[] arr;
    return 0;
}
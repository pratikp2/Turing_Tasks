#include <iostream>

int main() {
    int* arr = new int[10];
    std::cout << arr[5] << std::endl; // Accessing uninitialized memory
    delete[] arr;
    return 0;
}

#include <iostream>
#include <cstdlib> // For malloc and free
#include <cstring> // For memset

using namespace std;

// Function to allocate an array dynamically using pointers
void* allocateDynamicArray(size_t size) {
    void* ptr = malloc(size);
    if (ptr == nullptr) {
        cerr << "Memory allocation failed!" << endl;
        exit(EXIT_FAILURE);
    }
    memset(ptr, 0, size);
    return ptr;
}

// Function to deallocate the dynamically allocated array
void deallocateDynamicArray(void* ptr) {
    free(ptr);
}

int main() {
    const size_t array_size = 1024 * 1024; // 1 MB array size

    // Static array
    int staticArray[array_size];
    memset(staticArray, 0, sizeof(staticArray));

    // Dynamic array
    int* dynamicArray = static_cast<int*>(allocateDynamicArray(sizeof(int) * array_size));

    // Add a delay here to ensure the memory is allocated for a measurable period
    for (int i = 0; i < 100000000; i++) {}

    // Deallocate the dynamic array
    deallocateDynamicArray(dynamicArray);

    return 0;
}

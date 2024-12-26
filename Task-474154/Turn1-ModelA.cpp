#include <iostream>

void duplicateArray(int* arr, int size) {
    // Create a new array to hold the duplicated values
    int* duplicated = new int[size * 2]; // Allocate double the size

    // Use pointer arithmetic to populate the duplicated array
    int* pSrc = arr;                 // Pointer to the original array
    int* pDest = duplicated;         // Pointer to the new duplicated array

    for (int i = 0; i < size; ++i) {
        *pDest++ = *pSrc;  // Duplicate by copying the value
        *pDest++ = *pSrc++; // Duplicate the element again and move to next
    }

    // Output the duplicated array
    std::cout << "Duplicated Array: ";
    for (int i = 0; i < size * 2; ++i) {
        std::cout << duplicated[i] << " ";
    }
    std::cout << std::endl;

    // Free the allocated memory
    delete[] duplicated;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    duplicateArray(arr, size);

    return 0;
}

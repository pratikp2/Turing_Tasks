#include <iostream>
#include <stdexcept>

void duplicateArray(const int* arr, std::size_t size) {
    if (size == 0) {
        std::cout << "Duplicated Array: (empty)" << std::endl;
        return;
    }

    if (size < 0) {
        throw std::invalid_argument("Array size must be non-negative.");
    }

    try {
        int* duplicated = new int[size * 2];
        int* pSrc = const_cast<int*>(arr);
        int* pDest = duplicated;

        for (std::size_t i = 0; i < size; ++i) {
            *pDest++ = *pSrc;
            *pDest++ = *pSrc++;
        }

        std::cout << "Duplicated Array: ";
        for (int i = 0; i < size * 2; ++i) {
            std::cout << duplicated[i] << " ";
        }
        std::cout << std::endl;

        delete[] duplicated;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    duplicateArray(arr, sizeof(arr) / sizeof(arr[0]));

    return 0;
}

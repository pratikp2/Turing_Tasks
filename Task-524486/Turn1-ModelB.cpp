#include <iostream>
#include <vector>

template <typename T>
class PointerVector : public std::vector<T> {
public:
    using typename std::vector<T>::iterator;
    using typename std::vector<T>::const_iterator;

    // Function to get the raw pointer to the underlying data
    T* dataPointer() {
        return this->data();
    }

    const T* dataPointer() const {
        return this->data();
    }

    // Function to get the pointer to the element at a specific index
    T* pointerAt(size_t index) {
        return &(this->at(index));
    }

    const T* pointerAt(size_t index) const {
        return &(this->at(index));
    }
};

// Example usage of the custom pointer-based vector
int main() {
    PointerVector<int> prices = {100, 105, 102, 108, 103};

    std::cout << "Original prices: \n";
    for (const int& price : prices) {
        std::cout << price << " ";
    }
    std::cout << "\n";
    // Using pointer-based access for faster operations
    int* firstPricePointer = prices.pointerAt(0);
    int* lastPricePointer = prices.pointerAt(prices.size() - 1);

    // Performing operations using pointers
    *firstPricePointer = 98;
    *lastPricePointer = 110;

    std::cout << "Modified prices: \n";
    for (const int& price : prices) {
        std::cout << price << " ";
    }
    std::cout << "\n";

    return 0;
}

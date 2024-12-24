#include <iostream>
#include <stdexcept>
#include <type_traits>

// Template class to enforce array bounds checking
template <typename T, std::size_t N>
class SafeArray {
public:
    // Constructor
    SafeArray() = default;

    // Access operator with bounds checking
    T& operator[](std::size_t index) {
        checkBounds(index);
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        checkBounds(index);
        return data[index];
    }

private:
    T data[N]; // underlying array

    // Function to check array bounds
    void checkBounds(std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Array index out of bounds");
        }
    }
};

int main() {
    SafeArray<int, 5> arr;

    // Valid access
    arr[0] = 10;
    arr[1] = 20;

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "arr[1]: " << arr[1] << std::endl;

    try {
        // Invalid access
        std::cout << "arr[5]: " << arr[5] << std::endl; // This will throw
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Catch the exception
    }

    return 0;
}

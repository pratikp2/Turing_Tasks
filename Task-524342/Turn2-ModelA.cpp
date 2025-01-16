#include <iostream>
#include <stdexcept>

// The DynamicArray class as defined previously
class DynamicArray {
public:
    // Constructor that allocates memory for the array
    DynamicArray(size_t size)
        : size_(size), data_(nullptr) {
        if (size_ == 0) {
            throw std::invalid_argument("Size must be greater than zero.");
        }
        data_ = new int[size_]; // Allocate memory
        if (!data_) {
            throw std::runtime_error("Memory allocation failed.");
        }
    }

    // Destructor that deallocates memory
    ~DynamicArray() {
        delete[] data_; // Release memory
    }

    DynamicArray(const DynamicArray&) = delete; // No copy
    DynamicArray& operator=(const DynamicArray&) = delete; // No copy assignment

    DynamicArray(DynamicArray&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0; // Invalidate the source object
        other.data_ = nullptr;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_; // Clean up existing resource
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0; // Invalidate the source object
            other.data_ = nullptr;
        }
        return *this;
    }

    int& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index is out of bounds.");
        }
        return data_[index];
    }

    size_t size() const {
        return size_;
    }

private:
    size_t size_; // Size of the array
    int* data_;   // Pointer to the dynamically allocated array
};

// Function demonstrating exception scenarios
void testDynamicArray() {
    try {
        DynamicArray arr(5);  // Create a dynamic array of size 5

        // Intentionally cause an out-of-bounds access to trigger an exception
        std::cout << arr[5] << std::endl; // This will throw std::out_of_range
    } catch (const std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    try {
        // This will throw an exception for size 0
        DynamicArray arr(0);
    } catch (const std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    try {
        // Simulating a scenario where memory allocation fails
        // Note: This cannot be directly simulated, but we can show that
        // if the allocation fails, it will throw an exception.
        DynamicArray arr(1 << 30); // Large size to increase chances of failure
    } catch (const std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
}

int main() {
    testDynamicArray();
    return 0;
}

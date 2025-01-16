#include <iostream>
#include <stdexcept>

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

    // Copy constructor (deleted to prevent shallow copy)
    DynamicArray(const DynamicArray&) = delete;

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0; // Invalidate the source object
        other.data_ = nullptr;
    }

    // Copy assignment operator (deleted to prevent shallow copy)
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Move assignment operator
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

    // Access element at a given index with bounds checking
    int& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index is out of bounds.");
        }
        return data_[index];
    }

    // Access element at a given index (const version)
    const int& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index is out of bounds.");
        }
        return data_[index];
    }

    // Get the size of the array
    size_t size() const {
        return size_;
    }

private:
    size_t size_; // Size of the array
    int* data_;   // Pointer to the dynamically allocated array
};

int main() {
    try {
        DynamicArray arr(5);  // Create a dynamic array of size 5
        for (size_t i = 0; i < arr.size(); ++i) {
            arr[i] = static_cast<int>(i + 1); // Initialize array elements
        }

        for (size_t i = 0; i < arr.size(); ++i) {
            std::cout << "Element at index " << i << ": " << arr[i] << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

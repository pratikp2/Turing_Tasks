#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

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

    // Deleted copy constructor and assignment operator
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0; // Invalidate the source object
        other.data_ = nullptr;
    }

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

    // Get the size of the array
    size_t size() const {
        return size_;
    }

private:
    size_t size_; // Size of the array
    int* data_;   // Pointer to the dynamically allocated array
};

class DynamicArrayManager {
public:
    // Allocates a new DynamicArray of given size and stores a pointer to it
    void allocate(size_t size) {
        try {
            auto array = std::make_unique<DynamicArray>(size);
            arrays_.push_back(std::move(array));
        } catch (const std::exception& e) {
            std::cerr << "Exception during allocation: " << e.what() << std::endl;
        }
    }

    // Retrieves the DynamicArray at the specified index
    DynamicArray* getArray(size_t index) {
        if (index >= arrays_.size()) {
            throw std::out_of_range("Array index is out of bounds.");
        }
        return arrays_[index].get();
    }

    // Prints all arrays and their sizes
    void printArrays() const {
        for (size_t i = 0; i < arrays_.size(); ++i) {
            std::cout << "Array " << i << " size: " << arrays_[i]->size() << std::endl;
            for (size_t j = 0; j < arrays_[i]->size(); ++j) {
                std::cout << "Element at " << j << ": " << (*arrays_[i])[j] << std::endl; // accessing elements
            }
        }
    }

private:
    std::vector<std::unique_ptr<DynamicArray>> arrays_; // Store multiple DynamicArrays using unique_ptr
};

int main() {
    DynamicArrayManager manager;

    // Allocate multiple DynamicArray instances
    manager.allocate(5); // This should succeed
    manager.allocate(0); // This will cause an exception (size must be greater than zero)
    manager.allocate(10); // This should succeed

    // Access and initialize some arrays
    try {
        DynamicArray* arr1 = manager.getArray(0);
        for (size_t i = 0; i < arr1->size(); ++i) {
            (*arr1)[i] = static_cast<int>(i + 1);
        }

        DynamicArray* arr3 = manager.getArray(1); // Access the second array, which should throw an exception
        for (size_t i = 0; i < arr3->size(); ++i) {
            (*arr3)[i] = static_cast<int>(i + 10);
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Exception while accessing arrays: " << e.what() << std::endl;
    }

    // Print out all arrays
    manager.printArrays();

    return 0;
}

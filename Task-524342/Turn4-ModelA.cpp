#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>

class DynamicArray {
public:
    // Constructor that allocates memory for the array
    DynamicArray(size_t size)
        : size_(size), data_(nullptr) {
        if (size_ == 0) {
            throw std::invalid_argument("Size must be greater than zero.");
        }
        data_ = new int[size_]; // Allocate memory
        std::fill(data_, data_ + size_, 0); // Initialize elements to zero
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

    // Resize the array dynamically
    void resize(size_t newSize) {
        if (newSize == size_) {
            return; // No change in size
        }

        // Create a new array to hold the new size
        int* newData = nullptr;
        try {
            newData = new int[newSize];
            std::fill(newData, newData + newSize, 0); // Initialize new elements to zero

            // Copy old data to the new array
            size_t copySize = std::min(size_, newSize);
            for (size_t i = 0; i < copySize; ++i) {
                newData[i] = data_[i];
            }

            // Release old data
            delete[] data_; // Clean up old data
            data_ = newData; // Point to the new data
            size_ = newSize; // Update size
        } catch (const std::bad_alloc&) {
            delete[] newData; // Clean up if new allocation fails
            throw; // Re-throw the exception
        }
    }

private:
    size_t size_; // Size of the array
    int* data_;   // Pointer to the dynamically allocated array
};

class DynamicArrayManager {
public:
    void allocate(size_t size) {
        try {
            auto array = std::make_unique<DynamicArray>(size);
            arrays_.push_back(std::move(array));
        } catch (const std::exception& e) {
            std::cerr << "Exception during allocation: " << e.what() << std::endl;
        }
    }

    DynamicArray* getArray(size_t index) {
        if (index >= arrays_.size()) {
            throw std::out_of_range("Array index is out of bounds.");
        }
        return arrays_[index].get();
    }

    void printArrays() const {
        for (size_t i = 0; i < arrays_.size(); ++i) {
            std::cout << "Array " << i << " size: " << arrays_[i]->size() << std::endl;
            for (size_t j = 0; j < arrays_[i]->size(); ++j) {
                std::cout << "Element at " << j << ": " << (*arrays_[i])[j] << std::endl; // Accessing elements
            }
        }
    }

private:
    std::vector<std::unique_ptr<DynamicArray>> arrays_; // Store multiple DynamicArrays using unique_ptr
};

int main() {
    DynamicArrayManager manager;

    // Allocate two DynamicArray instances
    manager.allocate(5);
    manager.allocate(3);

    // Access the first array and initialize it
    try {
        DynamicArray* arr1 = manager.getArray(0);
        for (size_t i = 0; i < arr1->size(); ++i) {
            (*arr1)[i] = static_cast<int>(i + 1); // Fill with sample data
        }
        
        // Resize the first array (upsize)
        arr1->resize(8);
        std::cout << "After resizing Array 0 to 8:" << std::endl;
        manager.printArrays();

        // Resize the first array (downsize)
        arr1->resize(3);
        std::cout << "After resizing Array 0 to 3:" << std::endl;
        manager.printArrays();

    } catch (const std::exception& e) {
        std::cerr << "Exception while accessing arrays: " << e.what() << std::endl;
    }

    return 0;
}

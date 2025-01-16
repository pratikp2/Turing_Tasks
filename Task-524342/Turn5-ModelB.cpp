#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <iomanip>

class DynamicArray {
public:
    DynamicArray(size_t size)
        : size_(size), data_(nullptr) {
        if (size_ == 0) {
            throw std::invalid_argument("Size must be greater than zero.");
        }
        data_ = new int[size_]; // Allocate memory
        std::fill(data_, data_ + size_, 0); // Initialize elements to zero
        log_.push_back({"Allocated", "DynamicArray of size " + std::to_string(size_)});
    }

    ~DynamicArray() {
        delete[] data_; // Release memory
        log_.push_back({"Deallocated", "DynamicArray of size " + std::to_string(size_)});
    }

    // Deleted copy constructor and assignment operator
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    DynamicArray(DynamicArray&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0; // Invalidate the source object
        other.data_ = nullptr;
        log_.push_back({"Moved", "DynamicArray of size " + std::to_string(size_)});
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_; // Clean up existing resource
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0; // Invalidate the source object
            other.data_ = nullptr;
            log_.push_back({"Moved", "DynamicArray of size " + std::to_string(size_)});
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

    void resize(size_t newSize) {
        if (newSize == size_) {
            return; // No change in size
        }

        int* newData = nullptr;
        try {
            newData = new int[newSize];
            std::fill(newData, newData + newSize, 0); // Initialize new elements to zero

            size_t copySize = std::min(size_, newSize);
            for (size_t i = 0; i < copySize; ++i) {
                newData[i] = data_[i];
            }

            delete[] data_; // Clean up old data
            data_ = newData; // Point to the new data
            size_ = newSize; // Update size

            log_.push_back({"Reallocated", "DynamicArray from size " + std::to_string(old_size_) + " to size " + std::to_string(size_)});
            old_size_ = size_;
        } catch (const std::bad_alloc&) {
            delete[] newData; // Clean up if new allocation fails
            throw; // Re-throw the exception
        }
    }

    void printLog() const {
        std::cerr << "\nDynamicArray Memory Management Log:\n";
        for (const auto& entry : log_) {
            std::cerr << std::left << std::setw(15) << entry.first << ": " << entry.second << std::endl;
        }
    }

private:
    size_t size_; // Size of the array
    int* data_;   // Pointer to the dynamically allocated array
    mutable std::vector<std::pair<std::string, std::string>> log_;
    size_t old_size_ = 0;
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
                std::cout << "Element at " << j << ": " << (*arrays_[i])[j] << std::endl;
            }
        }
    }

private:
    std::vector<std::unique_ptr<DynamicArray>> arrays_; // Store multiple DynamicArrays using unique_ptr
};

int main() {
    DynamicArrayManager manager;

    manager.allocate(5);
    manager.allocate(3);

    DynamicArray* arr1 = manager.getArray(0);
    arr1->resize(8);
    arr1->resize(3);

    arr1->printLog();
    return 0;
}

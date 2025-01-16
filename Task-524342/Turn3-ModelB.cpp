#include <iostream>
#include <stdexcept>
#include <vector>

class MultiDynamicArray {
public:
    MultiDynamicArray(const std::initializer_list<size_t>& sizes) {
        for (size_t size : sizes) {
            if (size == 0) {
                throw std::invalid_argument("Size must be greater than zero.");
            }
            data_.push_back(new int[size]);
            if (!data_.back()) {
                // If allocation fails, clear all previous allocations and throw
                for (int* ptr : data_) {
                    delete[] ptr;
                }
                data_.clear();
                throw std::runtime_error("Memory allocation failed.");
            }
        }
    }

    ~MultiDynamicArray() {
        for (int* ptr : data_) {
            delete[] ptr;
        }
        data_.clear();
    }

    MultiDynamicArray(const MultiDynamicArray&) = delete; // No copy
    MultiDynamicArray& operator=(const MultiDynamicArray&) = delete; // No copy assignment

    MultiDynamicArray(MultiDynamicArray&& other) noexcept
        : data_(std::move(other.data_)) {
        other.data_.clear();
    }

    MultiDynamicArray& operator=(MultiDynamicArray&& other) noexcept {
        if (this != &other) {
            data_.swap(other.data_);
        }
        return *this;
    }

    // Access element at a given index of the specified array with bounds checking
    int& operator[](size_t arrayIndex, size_t elementIndex) {
        if (arrayIndex >= data_.size()) {
            throw std::out_of_range("Array index is out of bounds.");
        }
        size_t arrSize = data_[arrayIndex];
        if (elementIndex >= arrSize) {
            throw std::out_of_range("Element index is out of bounds.");
        }
        return data_[arrayIndex][elementIndex];
    }

    // Access element at a given index (const version)
    const int& operator[](size_t arrayIndex, size_t elementIndex) const {
        if (arrayIndex >= data_.size()) {
            throw std::out_of_range("Array index is out of bounds.");
        }
        size_t arrSize = data_[arrayIndex];
        if (elementIndex >= arrSize) {
            throw std::out_of_range("Element index is out of bounds.");
        }
        return data_[arrayIndex][elementIndex];
    }

    size_t numArrays() const {
        return data_.size();
    }

private:
    std::vector<int*> data_; // Vector of pointers to dynamically allocated arrays
};

int main() {
    try {
        MultiDynamicArray arr{2, 5, 3}; // Create multiple dynamic arrays
        for (size_t i = 0; i < arr.numArrays(); ++i) {
            std::cout << "Array " << i << " size: " << arr.numArrays() << std::endl;
            for (size_t j = 0; j < arr[i, j]; ++j) {
                arr[i, j] = static_cast<int>(i * arr[i, j] + j + 1);
            }
        }

        for (size_t i = 0; i < arr.numArrays(); ++i) {
            std::cout << "Array " << i << ":" << std::endl;
            for (size_t j = 0; j < arr[i, j]; ++j) {
                std::cout << arr[i, j] << " ";
            }
            std::cout << std::endl;
        }

        // Attempt to access out-of-bounds element, which will trigger an exception
        std::cout << arr[0, arr[0, 0] + 1] << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}

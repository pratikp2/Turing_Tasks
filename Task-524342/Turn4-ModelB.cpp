#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

class DynamicArray {
public:
    DynamicArray(size_t size)
        : size_(size), data_(nullptr) {
        allocate(size);
    }

    ~DynamicArray() {
        delete[] data_;
    }

    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    DynamicArray(DynamicArray&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    void resize(size_t newSize) {
        reallocate(newSize);
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
    size_t size_;
    int* data_;

    void allocate(size_t size) {
        if (size == 0) {
            throw std::invalid_argument("Size must be greater than zero.");
        }
        data_ = new int[size];
        if (!data_) {
            throw std::runtime_error("Memory allocation failed.");
        }
    }

    void reallocate(size_t newSize) {
        if (newSize == 0) {
            throw std::invalid_argument("Size must be greater than zero.");
        }

        int* newData = new int[newSize];
        if (!newData) {
            throw std::runtime_error("Memory allocation failed.");
        }

        // Copy existing data
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }

        // Free the old memory and update pointers
        delete[] data_;
        data_ = newData;
        size_ = newSize;
    }
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

    void reallocate(size_t index, size_t newSize) {
        if (index >= arrays_.size()) {
            throw std::out_of_range("Array index is out of bounds.");
        }

        try {
            arrays_[index]->resize(newSize);
        } catch (const std::exception& e) {
            std::cerr << "Exception during reallocation: " << e.what() << std::endl;
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
    std::vector<std::unique_ptr<DynamicArray>> arrays_;
};

int main() {
    DynamicArrayManager manager;

    manager.allocate(5);   // Initial allocation
    manager.allocate(10);  // Second allocation

    try {
        // Upsizing and downsizing arrays
        manager.reallocate(0, 15); // Upsize array 0 to 15
        manager.reallocate(1, 3);   // Downsize array 1 to 3

        DynamicArray* arr1 = manager.getArray(0);
        for (size_t i = 0; i < arr1->size(); ++i) {
            (*arr1)[i] = static_cast<int>(i + 1);
        }

        DynamicArray* arr2 = manager.getArray(1);
        for (size_t i = 0; i < arr2->size(); ++i) {
            (*arr2)[i] = static_cast<int>(i + 10);
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception while accessing or reallocating arrays: " << e.what() << std::endl;
    }

    manager.printArrays();

    return 0;
}

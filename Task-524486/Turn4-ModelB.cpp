#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional> // for std::function
#include <stddef.h>  // for nullptr

template <typename T>
class PointerVector {
public:
    PointerVector(size_t initial_capacity = 10) 
        : data_(nullptr), size_(0), capacity_(initial_capacity) {
        data_ = new T[capacity_]; // Allocate an initial buffer
    }

    ~PointerVector() {
        if (data_) delete[] data_; // Deallocate memory
        data_ = nullptr; // Prevent dangling pointers
    }

    PointerVector(const PointerVector<T>& other) : data_(nullptr), size_(0), capacity_(0) {
        if (other.data_) {
            data_ = new T[other.size_];
            capacity_ = other.size_;
            size_ = other.size_;
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    PointerVector& operator=(const PointerVector<T>& other) {
        if (this != &other) {
            if (data_) delete[] data_;
            data_ = nullptr;

            if (other.data_) {
                data_ = new T[other.size_];
                capacity_ = other.size_;
                size_ = other.size_;
                std::copy(other.data_, other.data_ + size_, data_);
            }
        }
        return *this;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new T[new_capacity]; // Allocate new buffer
            std::copy(data_, data_ + size_, new_data); // Move existing elements
            delete[] data_; // Free old buffer
            data_ = new_data; // Point to new buffer
            capacity_ = new_capacity; // Update capacity
        }
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_] = value;
        ++size_;
    }

    T* at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_ + index;
    }

    const T* at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_ + index;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void bulk_modify(std::function<void(T*)> modifier) {
        for (size_t i = 0; i < size_; ++i) {
            modifier(data_ + i);
        }
    }

    template<typename Predicate>
    std::vector<T*> filter(Predicate pred) {
        std::vector<T*> result;
        for (size_t i = 0; i < size_; ++i) {
            if (pred(data_[i])) {
                result.push_back(data_ + i);
            }
        }
        return result;
    }

    void print() const {
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    void resize() {
        size_t new_capacity = capacity_ * 2; // Double the capacity
        reserve(new_capacity); // Use reserve to manage the resizing
    }

    T* data_;
    size_t size_;
    size_t capacity_;
};

int main() {
    PointerVector<int> pvec;

    pvec.push_back(1);
    pvec.push_back(2);
    pvec.push_back(3);

    std::cout << "Original elements: ";
    pvec.print();

    try {
        int* dangling_ptr = pvec.at(3); // WILL CRASH HERE
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        int* illegal_index_ptr = pvec.at(-1); // WILL CRASH HERE
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional> // for std::function

template <typename T>
class PointerVector {
public:
    PointerVector(size_t initial_capacity = 10) 
        : size_(0), capacity_(initial_capacity) {
        data_ = new T[capacity_]; // Allocate an initial buffer
    }

    ~PointerVector() {
        delete[] data_; // Deallocate memory
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
        return &data_[index];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void bulk_modify(std::function<void(T*)> modifier) {
        for (size_t i = 0; i < size_; ++i) {
            modifier(at(i));
        }
    }

    template<typename Predicate>
    std::vector<T*> filter(Predicate pred) {
        std::vector<T*> result;
        for (size_t i = 0; i < size_; ++i) {
            if (pred(data_[i])) {
                result.push_back(at(i));
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

    // Pre-allocating memory
    pvec.reserve(20); // Reserve space for 20 integers

    // Adding elements to the PointerVector
    for (int i = 0; i < 15; ++i) {
        pvec.push_back(i);
    }

    std::cout << "Elements in PointerVector: ";
    pvec.print();

    // Bulk modification: multiply each element by 3
    pvec.bulk_modify([](int* p) { if (p) *p *= 3; });

    std::cout << "After bulk modification: ";
    pvec.print();

    return 0;
}

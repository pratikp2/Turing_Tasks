#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <functional>

template <typename T>
class PointerVector {
public:
    PointerVector() = default;

    // Pre-allocate memory with a specified capacity
    void reserve(size_t capacity) {
        if (capacity == 0) {
            free_memory();
            data_ = nullptr;
            capacity_ = 0;
            size_ = 0;
            return;
        }

        if (data_) {
            std::realloc(data_, sizeof(T) * capacity);
        } else {
            data_ = std::malloc(sizeof(T) * capacity);
        }

        capacity_ = capacity;
    }

    // Add an element to the vector
    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);  // Double the capacity when needed
        }

        T* new_element = data_ + size_;
        *new_element = value;
        size_++;
    }

    // Dynamically resize the vector with minimal fragmentation
    void resize(size_t new_capacity) {
        if (new_capacity == 0) {
            free_memory();
            data_ = nullptr;
            capacity_ = 0;
            size_ = 0;
            return;
        }

        T* new_data = static_cast<T*>(std::malloc(sizeof(T) * new_capacity));
        if (!new_data) {
            throw std::bad_alloc();
        }

        std::copy(data_, data_ + size_, new_data);
        free_memory();
        data_ = new_data;
        capacity_ = new_capacity;
    }

    T* at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_ + index;
    }

    size_t size() const {
        return size_;
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

    ~PointerVector() {
        free_memory();
    }

private:
    void free_memory() {
        if (data_) {
            std::free(data_);
            data_ = nullptr;
        }
    }

    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

int main() {
    PointerVector<int> pvec;

    // Pre-allocate memory for 1 million elements
    pvec.reserve(1'000'000);

    // Generate and add random elements
    for (int i = 0; i < 500'000; ++i) {
        pvec.push_back(std::rand() % 100);
    }
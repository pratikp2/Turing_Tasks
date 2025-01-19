#include <iostream>
#include <stdexcept>
#include <functional> // for std::function
#include <memory>     // for std::unique_ptr
#include <algorithm>

template <typename T>
class PointerVector {
public:
    // Constructor
    PointerVector(size_t initial_capacity = 10)
        : size_(0), capacity_(initial_capacity) {
        data_ = std::unique_ptr<T[]>(new T[capacity_]); // Use unique_ptr for safety
    }

    // Copy Constructor
    PointerVector(const PointerVector& other) 
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::unique_ptr<T[]>(new T[capacity_]);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    // Move Constructor
    PointerVector(PointerVector&& other) noexcept 
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Copy Assignment Operator
    PointerVector& operator=(const PointerVector& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = std::unique_ptr<T[]>(new T[capacity_]);
            std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        }
        return *this;
    }

    // Move Assignment Operator
    PointerVector& operator=(PointerVector&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Destructor
    ~PointerVector() = default; // Unique_ptr will handle memory cleanup.

    // Reserve memory
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            auto new_data = std::make_unique<T[]>(new_capacity);
            std::copy(data_.get(), data_.get() + size_, new_data.get());
            data_ = std::move(new_data);
            capacity_ = new_capacity;
        }
    }

    // Add new element
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_] = value;
        ++size_;
    }

    // Access element with bounds checking
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Const version of 'at' method
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Get current size
    size_t size() const {
        return size_;
    }

    // Get current capacity
    size_t capacity() const {
        return capacity_;
    }

    // Apply a function to each element safely
    void bulk_modify(std::function<void(T&)> modifier) {
        for (size_t i = 0; i < size_; ++i) {
            modifier(at(i));
        }
    }

    // Filter elements satisfying a predicate
    template<typename Predicate>
    std::vector<T*> filter(Predicate pred) {
        std::vector<T*> result;
        for (size_t i = 0; i < size_; ++i) {
            if (pred(data_[i])) {
                result.push_back(&data_[i]);
            }
        }
        return result;
    }

    // Print elements
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

    std::unique_ptr<T[]> data_; // Use unique_ptr for safe memory management
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
    pvec.bulk_modify([](int& p) { p *= 3; });

    std::cout << "After bulk modification: ";
    pvec.print();

    // Accessing an element safely
    try {
        std::cout << "Accessing element at index 3: " << pvec.at(3) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

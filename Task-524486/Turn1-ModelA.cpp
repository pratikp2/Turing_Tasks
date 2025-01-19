#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm> // For std::copy

template<typename T>
class Array {
public:
    // Constructor allocating and initializing the array
    Array(size_t size) : _size(size), _data(new T[size]) {
        std::fill(_data.get(), _data.get() + _size, T());
    }
    
    // Copy constructor
    Array(const Array& other) : _size(other._size), _data(new T[other._size]) {
        std::copy(other._data.get(), other._data.get() + other._size, _data.get());
    }
    
    // Move constructor
    Array(Array&& other) noexcept : _size(other._size), _data(std::move(other._data)) {
        other._size = 0;
    }
    
    // Access element using pointer arithmetic
    T& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return *(_data.get() + index);
    }
    
    // Const access for read-only
    const T& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return *(_data.get() + index);
    }
    
    size_t size() const { return _size; }
    
    // A simple summation function using pointers
    T sum() const {
        T total = T();
        for (size_t i = 0; i < _size; ++i) {
            total += *(_data.get() + i);
        }
        return total;
    }

private:
    size_t _size;                      // Size of the array
    std::unique_ptr<T[]> _data;       // Pointer to the data
};

int main() {
    try {
        Array<int> arr(5); // Create an array of 5 integers
        for (size_t i = 0; i < arr.size(); ++i) {
            arr[i] = (int)i + 1; // Initialize array with 1 to 5
        }
        
        std::cout << "Array elements: ";
        for (size_t i = 0; i < arr.size(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
        
        std::cout << "Sum of elements: " << arr.sum() << "\n"; // Output the sum
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

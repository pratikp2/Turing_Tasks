#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class PointerVector {
public:
    PointerVector() = default;

    // Add an element to the vector
    void push_back(const T& value) {
        data_.push_back(value);
    }

    // Get a pointer to the element at the specified index
    T* at(size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return &data_[index];
    }

    // Get a pointer to the first element
    T* begin() {
        return data_.empty() ? nullptr : &data_[0];
    }

    // Get a pointer to one past the last element
    T* end() {
        return data_.empty() ? nullptr : &data_[0] + data_.size();
    }

    // Get the number of elements in the vector
    size_t size() const {
        return data_.size();
    }

    // Print all elements
    void print() const {
        for (const auto& elem : data_) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> data_;
};

int main() {
    PointerVector<int> pvec;

    // Adding elements to the PointerVector
    for (int i = 1; i <= 5; ++i) {
        pvec.push_back(i);
    }

    // Printing original elements
    std::cout << "Original elements: ";
    pvec.print();

    // Modify elements via pointer-based access
    for (size_t i = 0; i < pvec.size(); ++i) {
        int* ptr = pvec.at(i);
        if (ptr) {
            *ptr *= 2;  // Double each element
        }
    }

    // Printing modified elements
    std::cout << "Modified elements: ";
    pvec.print();

    return 0;
}

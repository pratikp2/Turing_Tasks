#include <iostream>
#include <vector>
#include <iterator>
#include <stdexcept>

template <typename T>
class PointerVector {
public:
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    PointerVector() = default;

    // Add an element to the vector
    void push_back(const T& value) {
        data_.push_back(value);
    }

    // Direct element access by pointer
    pointer at(size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return &data_[index];
    }

    const_pointer at(size_t index) const {
        if (index >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return &data_[index];
    }

    // Begin and end iterators
    iterator begin() {
        return data_.data();
    }

    const_iterator begin() const {
        return data_.data();
    }

    cbegin() const {
        return begin();
    }

    iterator end() {
        return data_.data() + data_.size();
    }

    const_iterator end() const {
        return data_.data() + data_.size();
    }

    cend() const {
        return end();
    }

    // Size
    size_type size() const {
        return data_.size();
    }

    // Clear
    void clear() {
        data_.clear();
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
    for (int i = 1; i <= 100000; ++i) {
        pvec.push_back(i);
    }

    // Printing original elements
    std::cout << "Original elements: ";
    pvec.print();

    /** Performance comparison block **/
    {
        std::cout << "\nPerforming element doubling via pointers: \n";
        const auto start = std::chrono::high_resolution_clock::now();

        // Efficient loop with pointers
        for (auto* ptr = pvec.begin(); ptr != pvec.end(); ++ptr) {
            *ptr *= 2;
        }

        const auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " microseconds\n";
    }

    {
        std::cout << "\nPerforming element doubling via iterators: \n";
        const auto start = std::chrono::high_resolution_clock::now();

        // Same loop with iterators
        for (auto it = pvec.begin(); it != pvec.end(); ++it) {
            *it *= 2;
        }

        const auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " microseconds\n";
    }

    // Printing modified elements
    std::cout << "\nModified elements: ";
    pvec.print();

    return 0;
}

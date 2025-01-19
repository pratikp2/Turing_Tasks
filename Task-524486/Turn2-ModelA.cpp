#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class PointerVector {
public:
    PointerVector() = default;

    void push_back(const T& value) {
        data_.push_back(value);
    }

    T* at(size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return &data_[index];
    }

    size_t size() const {
        return data_.size();
    }

    // Bulk modification of elements
    void bulk_modify(std::function<void(T*)> modifier) {
        for (size_t i = 0; i < data_.size(); ++i) {
            modifier(at(i));
        }
    }

    // Retrieve filtered pointers to elements satisfying a predicate
    template<typename Predicate>
    std::vector<T*> filter(Predicate pred) {
        std::vector<T*> result;
        for (size_t i = 0; i < data_.size(); ++i) {
            if (pred(data_[i])) {
                result.push_back(at(i));
            }
        }
        return result;
    }

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

    for (int i = 0; i < 10; ++i) {
        pvec.push_back(i);
    }

    std::cout << "Original elements: ";
    pvec.print();

    // Bulk modification: multiply each element by 2
    pvec.bulk_modify([](int* p) { if (p) *p *= 2; });

    std::cout << "After bulk modification: ";
    pvec.print();

    // Filtering: getting pointers to even elements
    auto evens = pvec.filter([](int value) { return value % 2 == 0; });

    std::cout << "Filtered even elements: ";
    for (int* p : evens) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;

    return 0;
}

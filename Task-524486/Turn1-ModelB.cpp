#include <iostream>
#include <vector>
#include <algorithm>

class ArrayProcessor {
public:
    explicit ArrayProcessor(const std::vector<int>& data) : data_(&data.front()), size_(data.size()) {}

    void squareElements() {
        for (int* it = data_, *end = data_ + size_; it != end; ++it) {
            *it *= *it;
        }
    }

    void sumElements() {
        sum_ = 0;
        for (int* it = data_, *end = data_ + size_; it != end; ++it) {
            sum_ += *it;
        }
    }

    int getSum() const {
        return sum_;
    }

private:
    const int* data_;
    size_t size_;
    int sum_ = 0;
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ArrayProcessor processor(data);

    processor.squareElements();

    // Display the modified data using iterators
    for (const int& element : data) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    processor.sumElements();
    std::cout << "Sum of squared elements: " << processor.getSum() << std::endl;

    return 0;
}

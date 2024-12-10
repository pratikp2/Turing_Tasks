#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

class LazyEvaluator {
public:
    // Constructor takes a starting value and a function to generate the next value
    LazyEvaluator(int startValue, std::function<int(int)> fn)
        : start_(startValue), fn_(fn), size_(0) {}

    class Iterator {
    public:
        Iterator(int value, int size, std::function<int(int)> fn)
            : value_(value), size_(size), fn_(fn) {}

        bool operator!=(const Iterator& other) const { return value_ != other.value_ || size_ != other.size_; }

        int operator*() const { return value_; }

        // Move to the next value
        Iterator& operator++() {
            value_ = fn_(value_); // calculate new value
            return *this;
        }

        // Move to the previous value
        Iterator& operator--() {
            value_ = findPrevious(value_);
            return *this;
        }

    private:
        int findPrevious(int val) {
            // Generate the previous value inversely here
            for (int i = 0; i < size_; ++i) {
                val = (val - 1); // mock inverse operation
            }
            return val;
        }

        int value_;
        int size_;
        std::function<int(int)> fn_;
    };

    Iterator begin() { return Iterator(start_, size_, fn_); }
    Iterator end() { return Iterator(start_ + size_, size_, fn_); }
    
    void generate(int newSize) { size_ = newSize; } // Trigger generation of next values

private:
    int start_;
    std::function<int(int)> fn_;
    int size_;
};

int main() {
    auto nextValue = [](int v) { return v + 1; }; // sample transformation function

    LazyEvaluator lazySequence(0, nextValue);
    lazySequence.generate(10); // generates first 10 numbers

    std::cout << "Forward Iteration:\n";
    for (auto it = lazySequence.begin(); it != lazySequence.end(); ++it) {
        std::cout << *it << " "; // Prints 0 1 2 3 4 5 6 7 8 9
    }
    std::cout << "\n\nBackward Iteration (simulated explicitly):\n";
    for (auto it = lazySequence.end(); it != lazySequence.begin(); ) {
        --it; // Decrement the iterator
        std::cout << *it << " "; // Prints 9 8 7 6 5 4 3 2 1 0
    }

    return 0;
}

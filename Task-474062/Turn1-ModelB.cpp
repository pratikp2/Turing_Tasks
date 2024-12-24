#include <iostream>
#include <type_traits>

template <typename T, size_t Size>
class SafeArray {
public:
    SafeArray(const T* data, size_t size)
        : data_(data), size_(static_cast<std::decay_t<decltype(size)>>(size)) {
        if (size_ > Size) {
            static_assert(false, "Array size mismatch");
        }
    }

    T operator[](size_t index) const {
        static_assert(index < size_, "Array index out of bounds");
        return data_[index];
    }

    T* operator()() {
        return data_;
    }

private:
    const T* data_;
    size_t size_;
};

// Example usage:
int main() {
    int data[] = {1, 2, 3, 4, 5};

    SafeArray<int, 3> safeArray1(data, 3);  // Compiles fine
    SafeArray<int, 3> safeArray2(data, 5);  // Compile-time error

    std::cout << safeArray1[0] << std::endl; // Compiles fine
    std::cout << safeArray1[3] << std::endl;  // Compile-time error

    int* rawPtr = data;
    // rawPtr[3]; // No bounds checking - potential runtime error

    return 0;
}

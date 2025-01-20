#include <type_traits>
#include <iostream>

template <typename T>
struct IsIntegral : std::false_type {};

template <typename T>
struct IsIntegral<T*> : std::false_type {};

template <typename T>
struct IsIntegral<T> : std::is_integral<T> {};

// Type trait to check if the type is a pointer
template <typename T>
struct IsPointer : std::false_type {};

template <typename T>
struct IsPointer<T*> : std::true_type {};

// Template specialization for pointer types to handle element-wise operations
template <typename T>
struct ElementWiseOperation<T*> {
    using result_type = T*;

    static T* apply(T* data, const T* filter, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            data[i] = static_cast<T>(data[i]) + static_cast<T>(filter[i]);
        }
        return data;
    }
};

// Template specialization for non-pointer types to handle element-wise operations
template <typename T>
struct ElementWiseOperation<T> {
    using result_type = T;

    static T apply(T data, const T filter) {
        return data + filter;
    }
};

template <typename DataType, typename FilterType>
auto elementWiseAdd(DataType data, const FilterType filter, size_t count = 1)
    -> typename ElementWiseOperation<DataType>::result_type {
    using Op = ElementWiseOperation<DataType>;

    static_assert(IsIntegral<DataType>::value && IsIntegral<FilterType>::value,
                  "DataType and FilterType must be integral types");

    if constexpr (IsPointer<DataType>::value) {
        return Op::apply(data, filter, count);
    } else {
        return Op::apply(data, filter);
    }
}

int main() {
    // Example usage with pointers
    size_t imageSize = 1024;
    int* imageData = new int[imageSize];
    int* filterData = new int[imageSize];

    // Initialize imageData and filterData with some values
    // ...

    elementWiseAdd(imageData, filterData, imageSize);

    delete[] imageData;
    delete[] filterData;

    // Example usage with non-pointers
    int scalarData = 10;
    int scalarFilter = 20;
    int result = elementWiseAdd(scalarData, scalarFilter);

    std::cout << "Result: " << result << std::endl;

    return 0;
}

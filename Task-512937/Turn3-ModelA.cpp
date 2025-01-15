#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <array>

template<typename T>
class Matrix {
public:
    Matrix(std::array<size_t, 2> dimensions)
        : dimensions_(dimensions), data_(dimensions_[0] * dimensions_[1]) {}

    T& operator()(size_t row, size_t col) {
        return data_[row * dimensions_[1] + col];
    }

    const T& operator()(size_t row, size_t col) const {
        return data_[row * dimensions_[1] + col];
    }

    std::array<size_t, 2> getDimensions() const {
        return dimensions_;
    }

    template<typename Func>
    void apply(Func func) {
        applyImpl(func, 0, 0);
    }

private:
    std::array<size_t, 2> dimensions_;
    std::vector<T> data_;

    void applyImpl(std::function<void(size_t, size_t, T&)> func, size_t row, size_t col) {
        if (row < dimensions_[0]) {
            if (col < dimensions_[1]) {
                func(row, col, (*this)(row, col));
                applyImpl(func, row, col + 1); // Process next column
            } else {
                applyImpl(func, row + 1, 0); // Move to the next row
            }
        }
    }
};

template<typename T, typename Func>
void transformMatrix(Matrix<T>& matrix, Func func) {
    matrix.apply([&](size_t row, size_t col, T& value) {
        value = func(value);
    });
}

int main() {
    const size_t rows = 1000;
    const size_t cols = 1000;
    Matrix<int> mat({rows, cols});

    // Initialize the matrix
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat(i, j) = i + j; // Sample data
        }
    }

    // Define a transformation operation
    auto increment = [](int x) { return x + 1; };

    // Measure the performance before the transformation
    auto start_time = std::chrono::high_resolution_clock::now();
    transformMatrix(mat, increment);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Matrix transformed in: " << duration.count() << " seconds.\n";

    // Output the first few elements to verify correctness if needed
    for (size_t i = 0; i < 5 && i < rows; ++i) {
        for (size_t j = 0; j < 5 && j < cols; ++j) {
            std::cout << mat(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

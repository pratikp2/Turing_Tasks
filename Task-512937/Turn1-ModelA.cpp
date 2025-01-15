#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

template<typename T>
class Matrix {
public:
    Matrix(size_t rows, size_t cols) 
        : rows_(rows), cols_(cols), data_(rows * cols) {}

    T& operator()(size_t row, size_t col) {
        return data_[row * cols_ + col];
    }

    const T& operator()(size_t row, size_t col) const {
        return data_[row * cols_ + col];
    }

    void forEach(const std::function<void(size_t, size_t, T&)>& func) {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                func(i, j, (*this)(i, j));
            }
        }
    }

private:
    size_t rows_;
    size_t cols_;
    std::vector<T> data_;
};

template<typename T, typename Func>
void transformMatrix(Matrix<T>& matrix, Func func) {
    matrix.forEach([&](size_t row, size_t col, T& value) {
        value = func(value);
    });
}

int main() {
    const size_t rows = 1000;
    const size_t cols = 1000;
    Matrix<int> mat(rows, cols);

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

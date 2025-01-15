#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <chrono>
#include <random>

class ConventionalMatrix {
public:
    ConventionalMatrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows * cols) {}

    int& operator()(size_t row, size_t col) {
        return data_[row * cols_ + col];
    }

    const int& operator()(size_t row, size_t col) const {
        return data_[row * cols_ + col];
    }

    void transform(const std::function<int(int)>& func) {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                (*this)(i, j) = func((*this)(i, j));
            }
        }
    }

private:
    size_t rows_;
    size_t cols_;
    std::vector<int> data_;
};

template<typename T>
class TemplateMatrix {
public:
    TemplateMatrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows * cols) {}

    T& operator()(size_t row, size_t col) {
        return data_[row * cols_ + col];
    }

    const T& operator()(size_t row, size_t col) const {
        return data_[row * cols_ + col];
    }

    void apply(const std::function<T(T)>& func) {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                (*this)(i, j) = func((*this)(i, j));
            }
        }
    }

private:
    size_t rows_;
    size_t cols_;
    std::vector<T> data_;
};

template<typename T>
void runBenchmark(size_t rows, size_t cols) {
    // Initialize random seed
    std::mt19937 gen(0);
    std::uniform_int_distribution<> distrib(1, 100);

    // Conventional approach
    ConventionalMatrix conventionalMatrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            conventionalMatrix(i, j) = distrib(gen); // Fill with random data
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    conventionalMatrix.transform([](int x) { return x + 1; });
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> conventionalTime = end - start;

    // Template-based approach
    TemplateMatrix<int> templateMatrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            templateMatrix(i, j) = distrib(gen); // Fill with random data
        }
    }

    start = std::chrono::high_resolution_clock::now();
    templateMatrix.apply([](int x) { return x + 1; });
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> templateTime = end - start;

    std::cout << "Rows: " << rows << ", Cols: " << cols << "\n";
    std::cout << "Conventional Time: " << conventionalTime.count() << " seconds.\n";
    std::cout << "Template Time: " << templateTime.count() << " seconds.\n";
    std::cout << "------------------------------------\n";
}

int main() {
    std::vector<std::pair<size_t, size_t>> testSizes = {
        {100, 100},
        {500, 500},
        {1000, 1000},
        {2000, 2000},
    };

    for (const auto& size : testSizes) {
        runBenchmark(size.first, size.second);
    }

    return 0;
}

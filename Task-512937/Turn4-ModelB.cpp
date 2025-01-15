#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <array>
#include <random>

template<typename T>
class Matrix {
public:
    // (Remains the same)
};

template<typename T, typename Func>
void transformMatrixTemplate(Matrix<T>& matrix, Func func) {
    matrix.apply([&](size_t row, size_t col, T& value) {
        value = func(value);
    });
}

template<typename T, typename Func>
void transformMatrixConventional(Matrix<T>& matrix, Func func) {
    size_t rows = matrix.getDimensions()[0];
    size_t cols = matrix.getDimensions()[1];

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = func(matrix(i, j));
        }
    }
}

int main() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> uni(0, 10000);

    // Matrix sizes for benchmarking
    const int size1[] = {100, 100};
    const int size2[] = {1000, 500};
    const int size3[] = {5000, 2000};

    using namespace std::chrono;

    auto increment = [](int x) { return x + 1; };

    for (const auto& size : {size1, size2, size3}) {
        Matrix<int> mat({size[0], size[1]});

        // Initialize matrix with random data
        for (size_t i = 0; i < mat.getDimensions()[0]; ++i) {
            for (size_t j = 0; j < mat.getDimensions()[1]; ++j) {
                mat(i, j) = uni(g);
            }
        }

        {
            // Template-based method
            auto start = high_resolution_clock::now();
            transformMatrixTemplate(mat, increment);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            std::cout << "Template - Matrix size (" << size[0] << "x" << size[1] << "): "
                      << duration.count() << " microseconds\n";
        }

        {
            // Conventional method
            auto start = high_resolution_clock::now();
            transformMatrixConventional(mat, increment);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            std::cout << "Conventional - Matrix size (" << size[0] << "x" << size[1] << "): "
                      << duration.count() << " microseconds\n";
        }
    }

    return 0;
}

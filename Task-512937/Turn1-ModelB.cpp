#include <iostream>
#include <vector>
#include <chrono>

const int SIZE = 1000000;

template <typename T>
inline T mask_mul(T a, T b)
{
    return a * b;
}

// Loop approach
template <typename T>
void multiplyVectorLoop(const std::vector<T>& a, const std::vector<T>& b, std::vector<T>& c) {
    for (size_t i = 0; i < a.size(); ++i) {
        c[i] = mask_mul(a[i], b[i]);
    }
}

// Dummy Vectorization for demonstration, use actual SIMD intrinsics in practice
template <typename T>
void multiplyVectorSimd(const std::vector<T>& a, const std::vector<T>& b, std::vector<T>& c)
{
    for (size_t i = 0; i < a.size(); i += 4) {
        // Process elements at indexes i, i+1, i+2, i+3
    }
}


int main() {
    std::vector<float> x(SIZE), y(SIZE), z(SIZE);

    // Populate vectors with random data
    for (size_t i = 0; i < SIZE; ++i) {
        x[i] = i;
        y[i] = i + 1;
    }

    /* Benchmark */
    auto start = std::chrono::high_resolution_clock::now();
    {
        multiplyVectorLoop(x, y, z);
    }
    auto end_loop = std::chrono::high_resolution_clock::now();
    auto loop_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_loop - start);

    start = std::chrono::high_resolution_clock::now();
    {
        multiplyVectorSimd(x, y, z);
    }
    auto end_simd = std::chrono::high_resolution_clock::now();
    auto simd_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_simd - start);

    std::cout << "Loop duration: " << loop_duration.count() << " microseconds" << std::endl;
    std::cout << "SIMD duration: " << simd_duration.count() << " microseconds" << std::endl;
    return 0;
}

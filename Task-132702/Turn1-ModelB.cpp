

#include <iostream>
#include <mkl.h>

void vector_add_scalar(const float* a, const float* b, float* c, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
}

void vector_add_simd(const float* a, const float* b, float* c, size_t n) {
    // Check if SIMD is supported
    if (!mkl_get_max_threads()) {
        vector_add_scalar(a, b, c, n);
        return;
    }

    // Assume n is a multiple of 8 (SIMD width)
    size_t simd_n = n / 8;

    // Load SIMD registers with the first 8 elements of a and b
    __m256 va = _mm256_loadu_ps(a);
    __m256 vb = _mm256_loadu_ps(b);

    for (size_t i = 0; i < simd_n; ++i) {
        // Add the corresponding elements in va and vb and store in vc
        __m256 vc = _mm256_add_ps(va, vb);

        // Store the result in c
        _mm256_storeu_ps(c, vc);

        // Update va and vb with the next 8 elements of a and b
        va = _mm256_loadu_ps(a + 8);
        vb = _mm256_loadu_ps(b + 8);

        // Move to the next 8 elements in c
        c += 8;
    }

    // Handle the remaining elements (if any) using scalar code
    size_t remaining = n % 8;
    for (size_t i = 0; i < remaining; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    const size_t n = 1000000;
    float* a = new float[n];
    float* b = new float[n];
    float* c_scalar = new float[n];
    float* c_simd = new float[n];

    // Initialize a and b with random values
    for (size_t i = 0; i < n; ++i) {
        a[i] = static_cast<float>(rand()) / RAND_MAX;
        b[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    // Measure time for scalar implementation
    double time_scalar = 0.0;
    {
        auto start = std::chrono::high_resolution_clock::now();
        vector_add_scalar(a, b, c_scalar, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        time_scalar = duration.count();
    }

    // Measure time for SIMD implementation
    double time_simd = 0.0;
    {
        auto start = std::chrono::high_resolution_clock::now();
        vector_add_simd(a, b, c_simd, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        time_simd = duration.count();
    }

    // Print the results
    std::cout << "Vector Addition using Scalar Code: " << time_scalar << " seconds" << std::endl;
    std::cout << "Vector Addition using SIMD Code: " << time_simd << " seconds" << std::endl;
    std::cout << "Speedup using SIMD: " << time_scalar / time_simd << "x" << std::endl;

    // Free memory
    delete[] a;
    delete[] b;
    delete[] c_scalar;
    delete[] c_simd;

    return 0;
}


#include <iostream>
#include <array>
#include <numeric>
#include <ctime>
#include <cstdlib>

// Using SIMD instructions with SSE4.2
#include <xmmintrin.h>

const int ARRAY_SIZE = 512; // Use a large size to notice performance differences

void nestedLoops_scalar(std::array<std::array<float, ARRAY_SIZE>, ARRAY_SIZE>& data) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < ARRAY_SIZE; ++j) {
            data[i][j] = data[i][j] * data[i][j];
        }
    }
}

void nestedLoops_vectorized(std::array<std::array<float, ARRAY_SIZE>, ARRAY_SIZE>& data) {
    const int vectorWidth = sizeof(__m128) / sizeof(float);
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < ARRAY_SIZE; j += vectorWidth) {
            __m128 result;
            
            for (int k = 0; k < vectorWidth; ++k) {
                int idx = j + k;
                if (idx >= ARRAY_SIZE) break;
                
                float element = data[i][idx];
                result = _mm_set_ps(element, result);
            }

            for (int k = 0; k < vectorWidth; ++k) {
                int idx = j + k;
                if (idx >= ARRAY_SIZE) break;

                float element = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 2, 1, 0)));
                if (k == 0) {
                    data[i][idx] = element * element;
                } else {
                    data[i][idx] = data[i][idx] * element;
                }
            }
        }
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    std::array<std::array<float, ARRAY_SIZE>, ARRAY_SIZE> data;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = 0; j < ARRAY_SIZE; ++j) {
            data[i][j] = std::rand() / static_cast<float>(RAND_MAX);
        }
    }

    // Scalar version
    {
        auto start = std::clock();
        nestedLoops_scalar(data);
        auto end = std::clock();
        std::cout << "Scalar nested loops time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
    }

    // Vectorized version
    {
        auto start = std::clock();
        nestedLoops_vectorized(data);
        auto end = std::clock();
        std::cout << "Vectorized nested loops time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
    }

    return 0;
}

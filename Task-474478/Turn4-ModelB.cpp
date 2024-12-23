#include <iostream>
#include <immintrin.h>
#include <memory>

// Implementor Interface
class BitwiseOperations {
public:
    virtual ~BitwiseOperations() = default;
    virtual __m128i performOperation(__m128i a, __m128i b) = 0;
};

// Concrete Implementor for AND operation using SIMD
class AndOperationSIMD : public BitwiseOperations {
public:
    inline __m128i performOperation(__m128i a, __m128i b) override {
        return _mm_and_si128(a, b);
    }
};

// Abstraction
class BooleanConfigurator {
protected:
    std::unique_ptr<BitwiseOperations> operation;

public:
    BooleanConfigurator(std::unique_ptr<BitwiseOperations> op) : operation(std::move(op)) {}

    __m128i configure(__m128i a, __m128i b) {
        return operation->performOperation(a, b);
    }
};

// Client code
int main() {
    const int numElements = 4;
    __m128i data[numElements] = {
        _mm_set_epi32(1, 2, 3, 4),
        _mm_set_epi32(5, 6, 7, 8),
        _mm_set_epi32(9, 10, 11, 12),
        _mm_set_epi32(13, 14, 15, 16)
    };

    __m128i otherData[numElements] = {
        _mm_set_epi32(5, 4, 3, 2),
        _mm_set_epi32(9, 8, 7, 6),
        _mm_set_epi32(13, 12, 11, 10),
        _mm_set_epi32(17, 16, 15, 14)
    };

    __m128i results[numElements];

    std::unique_ptr<BitwiseOperations> andOperationSIMD = std::make_unique<AndOperationSIMD>();
    BooleanConfigurator configuratorSIMD(std::move(andOperationSIMD));

    for (int i = 0; i < numElements; ++i) {
        results[i] = configuratorSIMD.configure(data[i], otherData[i]);
    }

    // Print results
    for (int i = 0; i < numElements; ++i) {
        __m128i result = results[i];
        int r0 = _mm_extract_epi32(result, 0);
        int r1 = _mm_extract_epi32(result, 1);
        int r2 = _mm_extract_epi32(result, 2);
        int r3 = _mm_extract_epi32(result, 3);
        std::cout << "Result " << i << ": " << r0 << ", " << r1 << ", " << r2 << ", " << r3 << std::endl;
    }

    return 0;
}

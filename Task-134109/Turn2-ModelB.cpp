#include <iostream>
#include <fixed_point.hpp>

int main() {
    using namespace fixed_point;

    // Define a fixed-point type with 16 bits for the integer part and 16 bits for the fractional part
    using fp_t = fixed_point<int16_t, 16>;

    // Create fixed-point variables
    fp_t a = fp_t(3.14); // Convert 3.14 to fixed-point
    fp_t b = fp_t(2.71); // Convert 2.71 to fixed-point

    // Perform arithmetic operations
    fp_t c = a + b;
    fp_t d = a * b;
    fp_t e = a / b;

    // Print the results
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "e: " << e << std::endl;

    return 0;
}
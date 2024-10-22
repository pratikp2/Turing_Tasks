#include <iostream>
#include <boost/multiprecision/fixed_point.hpp>

namespace mp = boost::multiprecision;

// Define a fixed-point type with 32 integer bits and 16 fractional bits
using fixed_point_t = mp::cpp_fixed<32, 16>;

int main() {
    fixed_point_t radius = 5.25; // Assign a value to the fixed-point variable

    // Calculate the area of the circle using fixed-point arithmetic
    fixed_point_t pi = 3.14159;
    fixed_point_t area = pi * radius * radius;

    std::cout << "Radius: " << radius << std::endl;
    std::cout << "Area: " << area << std::endl;
    return 0;
}
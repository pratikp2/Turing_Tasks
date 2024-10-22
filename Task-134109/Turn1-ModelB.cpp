#include <iostream>
#include <arm_math.h>

int main() {
    // Define the input points using fixed-point format (Q15 format)
    q15_t x1 = 100;     // Representing 1.0 in Q15 format
    q15_t y1 = 200;     // Representing 2.0 in Q15 format
    q15_t x2 = 300;     // Representing 3.0 in Q15 format
    q15_t y2 = 400;     // Representing 4.0 in Q15 format

    // Calculate the Euclidean distance using fixed-point arithmetic
    q15_t dx = x2 - x1;
    q15_t dy = y2 - y1;
    q31_t squaredDistance = arm_q15_mul(dx, dx) + arm_q15_mul(dy, dy);
    q15_t distance = sqrtf(squaredDistance); // Convert back to floating-point for printing

    // Print the results
    std::cout << "Distance between points (1,2) and (3,4) using fixed-point arithmetic: " << (float)distance << std::endl;

    return 0;
}
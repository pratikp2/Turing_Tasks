#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace mp = boost::multiprecision;

// Define a fixed-point type with 64 bits for the integer part and 32 bits for the fractional part
using FixedPoint = mp::cpp_dec_float<64, mp::digits10 + 32>;

// Function to calculate distance between two points using fixed-point arithmetic
FixedPoint calculateDistance(FixedPoint x1, FixedPoint y1, FixedPoint x2, FixedPoint y2) {
  FixedPoint dx = x2 - x1;
  FixedPoint dy = y2 - y1;
  return std::sqrt(dx * dx + dy * dy);
}

int main() {
  // Coordinates of two points
  FixedPoint x1 = 32.6514;
  FixedPoint y1 = -161.4333;
  FixedPoint x2 = 37.7747;
  FixedPoint y2 = -122.4182;

  // Calculate distance using fixed-point arithmetic
  FixedPoint distance = calculateDistance(x1, y1, x2, y2);

  // Display the result
  std::cout << "Distance between the points: " << distance << " kilometers" << std::endl;

  return 0;
}
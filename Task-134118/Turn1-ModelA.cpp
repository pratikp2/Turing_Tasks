#include <iostream>
#include <cmath>

// Function to calculate the area of a circle
double calculateArea(double radius) {
  // Check for invalid input
  if (radius < 0) {
    std::cerr << "Error: Radius cannot be negative." << std::endl;
    return 0.0;
  }

  const double pi = 3.14;
  return pi * std::pow(radius, 2);
}

int main() {
  double radius;

  std::cout << "Enter the radius of the circle: ";
  std::cin >> radius;

  double area = calculateArea(radius);
  if (area > 0) {
    std::cout << "The area of the circle is: " << area << std::endl;
  }

  return 0;
}
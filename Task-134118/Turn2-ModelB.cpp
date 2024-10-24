#include <iostream>
#include <cmath>

double calculateArea(double radius) {
  if (radius < 0) {
    throw std::invalid_argument("Radius cannot be negative.");
  }

  const double pi = 3.14;
  return pi * std::pow(radius, 2);
}

int main() {
  double radius;

  std::cout << "Enter the radius of the circle: ";
  if (!(std::cin >> radius)) {
    std::cerr << "Error: Invalid input for radius." << std::endl;
    return 1;
  }

  try {
    double area = calculateArea(radius);
    std::cout << "The area of the circle is: " << area << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
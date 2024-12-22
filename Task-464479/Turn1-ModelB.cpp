#include <iostream>
enum class Shape { CIRCLE, SQUARE, TRIANGLE };
constexpr auto area_circle(double radius) { return 3.14 * radius * radius; }
constexpr auto area_square(double side) { return side * side; }
constexpr auto area_triangle(double base, double height) { return 0.5 * base * height; }
void calculate_area(Shape shape, double radius = 0.0, double side = 0.0, double base = 0.0, double height = 0.0) {
  double area;
  switch (shape) {
    case Shape::CIRCLE:
      area = area_circle(radius);
      break;
    case Shape::SQUARE:
      area = area_square(side);
      break;
    case Shape::TRIANGLE:
      area = area_triangle(base, height);
      break;
  }
  std::cout << "Area: " << area << std::endl;
}
int main() {
  calculate_area(Shape::CIRCLE, 5.5); // Output: Area: 94.985
  calculate_area(Shape::SQUARE, 3.0); // Output: Area: 9.0
  calculate_area(Shape::TRIANGLE, 4.0, 6.0); // Output: Area: 12.0
}

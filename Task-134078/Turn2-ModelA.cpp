// shape_calculator.h
#pragma once

class Shape;

class ShapeCalculator {
public:
calculate_area(const Shape& shape) {
  return shape.area();
}
};

int main() {
  Circle circle(5.0);
  ShapeCalculator calculator;
  double area = calculator.calculate_area(circle);
  // ...
  return 0;
}
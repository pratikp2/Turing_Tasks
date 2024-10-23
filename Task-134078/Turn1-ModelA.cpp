#include <iostream>
#include <memory>
#include <boost/math/constants/constants.hpp>

class Shape {
public:
   virtual double area() const = 0;
   virtual ~Shape() = default;
};

class Circle : public Shape {
public:
   Circle(double radius) : radius(radius) {}
   double area() const override {
      using namespace boost::math;
      return const_pi<double>() * radius * radius;
   }

private:
   double radius;
};

class Rectangle : public Shape {
public:
   Rectangle(double length, double width) : length(length), width(width) {}
   double area() const override {
      return length * width;
   }

private:
   double length;
   double width;
};

class AreaCalculator {
public:
   double calculate_area(const Shape& shape) {
      return shape.area();
   }
};

int main() {
   std::unique_ptr<Shape> circle = std::make_unique<Circle>(5.5);
   std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(10, 20);

   AreaCalculator calculator;

   std::cout << "Area of circle: " << calculator.calculate_area(*circle) << std::endl;
   std::cout << "Area of rectangle: " << calculator.calculate_area(*rectangle) << std::endl;
   return 0;
}
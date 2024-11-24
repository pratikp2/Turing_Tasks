#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Shape interface
class Shape {
public:
    virtual std::string draw() = 0;
    virtual ~Shape() = default;
};

// Concrete Shape implementations
class Circle : public Shape {
public:
    std::string draw() override { return "Drawing a Circle."; }
};

class Square : public Shape {
public:
    std::string draw() override { return "Drawing a Square."; }
};

class Triangle : public Shape {
public:
    std::string draw() override { return "Drawing a Triangle."; }
};

// Shape Factory - The main focus of the Factory Method Pattern
class ShapeFactory {
public:
    enum ShapeType {
        CIRCLE,
        SQUARE,
        TRIANGLE
    };

    static std::unique_ptr<Shape> createShape(ShapeType type) {
        switch (type) {
            case CIRCLE:  return std::make_unique<Circle>();
            case SQUARE:  return std::make_unique<Square>();
            case TRIANGLE: return std::make_unique<Triangle>();
            default: return nullptr;
        }
    }
};

// Simulation of an "Algorithm" using shapes
class ShapeAlgorithm {
public:
    ShapeAlgorithm(const std::vector<std::unique_ptr<Shape>>& shapes) : m_shapes(shapes) {}

    void applyAlgorithm() {
        for (const auto& shape : m_shapes) {
            if (shape) {
                std::cout << shape->draw() << std::endl;
                // Perform some other operations on the shape based on the algorithm.
            }
        }
    }

private:
    std::vector<std::unique_ptr<Shape>> m_shapes;
};


int main() {
    // **Pre-C++14 legacy usage:**
    std::vector<Shape*> shapesLegacy;
    shapesLegacy.push_back(new Circle());
    shapesLegacy.push_back(new Square());
    shapesLegacy.push_back(new Triangle());

    // **Using the Factory Method Pattern:**
    std::vector<std::unique_ptr<Shape>> shapesModern;
    shapesModern.push_back(ShapeFactory::createShape(ShapeFactory::CIRCLE));
    shapesModern.push_back(ShapeFactory::createShape(ShapeFactory::SQUARE));
    shapesModern.push_back(ShapeFactory::createShape(ShapeFactory::TRIANGLE));

    // Apply the algorithm using modern C++ shapes.
    ShapeAlgorithm algorithm(shapesModern);
    algorithm.applyAlgorithm();

    // Without Factory, old implementations might require changes here.
    // Note: In legacy code, shapes were often created via `new`, leading to memory leaks.
    
    /* 
    for (auto shape : shapesLegacy) {
        delete shape;  // Remember to delete this in legacy code (must be done)!
    }
    */
    return 0;
}  

  
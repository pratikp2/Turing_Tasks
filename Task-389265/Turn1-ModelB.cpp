#include <cassert>
#include <iostream>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square." << std::endl;
    }
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Triangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a triangle." << std::endl;
    }
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& shapeType) {
        assert(!shapeType.empty()); // Assertion to check if shapeType is empty

        if (shapeType == "SQUARE") {
            return std::make_unique<Square>();
        } else if (shapeType == "CIRCLE") {
            return std::make_unique<Circle>();
        } else if (shapeType == "TRIANGLE") {
            return std::make_unique<Triangle>();
        }

        assert(false); // Assertion to check if shapeType is valid
        return nullptr;
    }
};

int main() {
    std::string shapeType;
    std::cout << "Enter the shape type (SQUARE, CIRCLE, TRIANGLE): ";
    std::getline(std::cin, shapeType);

    // Using the Factory design pattern to create a Shape object
    auto shape = ShapeFactory::createShape(shapeType);

    if (shape) {
        shape->draw();
    } else {
        std::cout << "Invalid shape type. Please try again." << std::endl;
    }

    return 0;
} 
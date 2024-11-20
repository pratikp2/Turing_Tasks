#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square." << std::endl;
    }
};

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;

    // Add shapes using shared_ptr to ensure proper memory management
    shapes.push_back(std::make_shared<Circle>());
    shapes.push_back(std::make_shared<Square>());
    shapes.push_back(std::make_shared<Circle>());

    // Now, you can safely pass shapes around without worrying about dangling pointers
    for (const auto& shape : shapes) {
        shape->draw();
    }

    return 0;
}
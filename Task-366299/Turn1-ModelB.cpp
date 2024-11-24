#include <iostream>
#include <cstring>

class Shape {
public:
    Shape(const char* name) {
        size_t nameLen = std::strlen(name) + 1;
        m_name = new char[nameLen];
        std::strcpy(m_name, name);
    }
    ~Shape() {
        delete[] m_name;
    }

    void draw() const {
        std::cout << "Drawing a shape named " << m_name << std::endl;
    }

private:
    char* m_name;
};

class Square : public Shape {
public:
    Square(const char* name, double side) : Shape(name), m_side(side) {
        m_sideLength = new double;
        *m_sideLength = side;
    }
    ~Square() {
        delete m_sideLength;
    }

    void draw() const override {
        Shape::draw();
        std::cout << "Side length: " << *m_sideLength << std::endl;
    }

    double getSide() const { return *m_sideLength; }

private:
    double* m_sideLength;
};

int main() {
    Shape* shapePtr = new Square("Square Shape", 10.0);

    shapePtr->draw();   // Output: Drawing a shape named Square Shape
    // We want to delete the Square object, but instead, Shape's destructor is called
    delete shapePtr;  // Memory leak for m_sideLength!
    return 0;
}
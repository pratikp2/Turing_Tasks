#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// Base class for Shape
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

// Derived classes for Circle and Square
class Circle : public Shape {
public:
    void draw() override { std::cout << "Drawing a circle." << std::endl; }
};

class Square : public Shape {
public:
    void draw() override { std::cout << "Drawing a square." << std::endl; }
};

// Monomorphic Data Structure
struct MonomorphicShape {
    int type;  // 0 for Circle, 1 for Square
    double radius; // Used for Circle
    double side;  // Used for Square
};

// Polymorphic Data Structure
using PolymorphicShapes = std::vector<Shape*>;

// Serialize Monomorphic Shapes
void serializeMonomorphic(const std::vector<MonomorphicShape>& shapes, const std::string& file_name) {
    std::ofstream ofs(file_name, std::ios::binary);
    if (!ofs.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return;
    }

    // Write the number of shapes first
    size_t num_shapes = shapes.size();
    ofs.write((char*)&num_shapes, sizeof(num_shapes));

    // Write each shape's data
    for (const MonomorphicShape& shape : shapes) {
        ofs.write((char*)&shape, sizeof(shape));
    }
    ofs.close();
}

// Deserialize Monomorphic Shapes
std::vector<MonomorphicShape> deserializeMonomorphic(const std::string& file_name) {
    std::ifstream ifs(file_name, std::ios::binary);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return {};
    }

    size_t num_shapes;
    ifs.read((char*)&num_shapes, sizeof(num_shapes));

    std::vector<MonomorphicShape> shapes(num_shapes);
    // Read each shape's data
    for (MonomorphicShape& shape : shapes) {
        ifs.read((char*)&shape, sizeof(shape));
    }
    ifs.close();
    return shapes;
}

// Serialize Polymorphic Shapes
void serializePolymorphic(const PolymorphicShapes& shapes, const std::string& file_name) {
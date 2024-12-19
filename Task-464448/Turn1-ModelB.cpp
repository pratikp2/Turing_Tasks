#include <variant>
#include <iostream>

enum class ShapeType { SQUARE, CIRCLE, TRIANGLE };

struct Shape {
    ShapeType type;
};

std::variant<Shape, int, std::string> process_data(Shape shape) {
    switch (shape.type) {
        case ShapeType::SQUARE:
            return "Square processed";
        case ShapeType::CIRCLE:
            return 42;
        case ShapeType::TRIANGLE:
            return Shape{ShapeType::TRIANGLE};
    }
}

int main() {
    Shape shape{ShapeType::CIRCLE};
    auto result = process_data(shape);
    std::visit([](const auto& x) {
        using T = std::decay_t<decltype(x)>;
        if constexpr (std::is_same_v<T, std::string>) {
            std::cout << x << std::endl;
        } else if constexpr (std::is_same_v<T, int>) {
            std::cout << "Integer result: " << x << std::endl;
        } else {
            std::cout << "Shape result: " << std::endl;
        }
    }, result);
    return 0;
}

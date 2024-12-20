#include <iostream>

enum ShapeType {
    SQUARE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
};

double calculateArea(ShapeType shape, double *dimensions) {
    switch (shape) {
        /* 
        Case: SQUARE
        Input: The side length of the square.
        Description: Calculates the area of the square using the formula A = side * side.
        Precondition: dimensions array should have exactly one element.
        Postcondition: Area of the square is returned.
        Potential Pitfall: If the input array has less than or more than one element, it will lead to undefined behaviour.
        */
        case SQUARE:
            if (dimensions == nullptr || *dimensions <= 0) {
                return -1; // Return a special value or handle invalid input as appropriate
            }
            return (*dimensions) * (*dimensions);
        /*
        Case: RECTANGLE
        Input: length and width of the rectangle.
        Description: Calculates the area of the rectangle using the formula A = length * width.
        Precondition: dimensions array should have exactly two elements.
        Postcondition: Area of the rectangle is returned.
        Potential Pitfall: Swapping the order of length and width in the input can give incorrect results.
        */
        case RECTANGLE:
            if (dimensions == nullptr || dimensions[0] <= 0 || dimensions[1] <= 0) {
                return -1;
            }
            return dimensions[0] * dimensions[1];
        /*
        Case: CIRCLE
        Input: The radius of the circle.
        Description: Calculates the area of the circle using the formula A = π * r * r.
        Precondition: dimensions array should have exactly one element.
        Postcondition: Area of the circle is returned.
        Potential Pitfall: Using a negative value for radius can give incorrect results, 
                           which might not be obvious from the function call.
        */
        case CIRCLE:
            if (dimensions == nullptr || *dimensions < 0) {
                return -1;
            }
            const double pi = 3.14;
            return pi * (*dimensions) * (*dimensions);
        /*
        Case: TRIANGLE
        Input: base and height of the triangle.
        Description: Calculates the area of the triangle using the formula A = 0.5 * base * height.
        Precondition: dimensions array should have exactly two elements.
        Postcondition: Area of the triangle is returned.
        Potential Pitfall: Negative values for base and height are allowed but may not have a real-world interpretation.
        */
        case TRIANGLE:
            if (dimensions == nullptr || dimensions[0] <= 0 || dimensions[1] <= 0) {
                return -1;
            }
            return 0.5 * dimensions[0] * dimensions[1];
        default:
            return -1; // Add a default case to handle invalid shape types
    }
}

int main() {
    double dimensions[2];
    ShapeType shape;

    // Example usage and error handling
    std::cout << "Enter shape (0 for SQUARE, 1 for RECTANGLE, 2 for CIRCLE, 3 for TRIANGLE): ";
    std::cin >> static_cast<int>(shape);

    switch (shape) {
        case SQUARE:
            std::cout << "Enter side length: ";
            std::cin >> dimensions[0];
            break;
        case RECTANGLE:
            std::cout << "Enter length: ";
            std::cin >> dimensions[0];
            std::cout << "Enter width: ";
            std::cin >> dimensions[1];
            break;
        case CIRCLE:
            std::cout << "Enter radius: ";
            std::cin >> dimensions[0];
            break;
        case TRIANGLE:
            std::cout << "Enter base: ";
            std::cin >> dimensions[0];
            std::cout << "Enter height: ";
            std::cin >> dimensions[1];
            break;
        default:
            std::cout << "Invalid shape type!" << std::endl;
            return 1;
    }
#include <iostream>
#include <stdexcept>

// Define the inline namespace for versioning
namespace MathLib {
    inline namespace V1 {
        inline double area(double width, double height) {
            // Version 1: Basic area calculation without error checking
            return width * height;
        }
    }
    
    inline namespace V2 {
        inline double area(double width, double height) {
            // Version 2: Area calculation with error checking
            if (width < 0 || height < 0) {
                throw std::invalid_argument("Width and height must be non-negative.");
            }
            return width * height;
        }
    }
}

// Function to demonstrate the usage of the MathLib
void demonstrateMathLib() {
    std::cout << "Using MathLib Version 1:" << std::endl;
    std::cout << "Area of rectangle (3, 4): " << MathLib::area(3, 4) << std::endl;

    std::cout << "Using MathLib Version 2:" << std::endl;
    try {
        std::cout << "Area of rectangle (3, -4): " << MathLib::area(3, -4) << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    demonstrateMathLib();
    return 0;
}

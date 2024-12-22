#include <iostream>
#include <string_view>

enum class Fruit {
    Apple,
    Banana,
    Cherry,
    Unknown
};

constexpr int fruitValue(Fruit fruit) {
    switch (fruit) {
        case Fruit::Apple: return 1;
        case Fruit::Banana: return 2;
        case Fruit::Cherry: return 3;
        default: return 0; // Unknown
    }
}

void describeFruit(Fruit fruit) {
    switch (fruit) {
        case Fruit::Apple:
            std::cout << "This is an Apple.\n";
            break;
        case Fruit::Banana:
            std::cout << "This is a Banana.\n";
            break;
        case Fruit::Cherry:
            std::cout << "This is a Cherry.\n";
            break;
        default:
            std::cout << "Unknown fruit.\n";
            break;
    }
}

int main() {
    constexpr Fruit myFruit = Fruit::Banana;

    // Compile-time evaluation
    constexpr int value = fruitValue(myFruit);
    std::cout << "Fruit value: " << value << "\n"; // Outputs: Fruit value: 2

    // Run-time evaluation
    describeFruit(myFruit); // Outputs: This is a Banana.

    return 0;
}

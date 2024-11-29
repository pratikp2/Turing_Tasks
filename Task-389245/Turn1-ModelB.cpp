#include <iostream>

int main() {
    int* ptr = nullptr;

    *ptr = 42; // Attempting to dereference a null pointer, triggering an invalid read

    std::cout << "Value stored in ptr: " << *ptr << std::endl;

    return 0;
}


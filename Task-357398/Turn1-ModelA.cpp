#include <iostream>

int main() {
    char* buffer = new char[100];
    // There's no code to delete the buffer, causing a memory leak
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
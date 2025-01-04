#include <iostream>

// Generic non-inlined copy function
void copyBytes(char* dest, const char* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Inlined copy function
inline void inlineCopyBytes(char* dest, const char* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    const size_t BUFFER_SIZE = 10;
    char srcBuffer[BUFFER_SIZE] = "Hello, world!";
    char destBuffer[BUFFER_SIZE];

    // Using non-inlined copy function
    std::cout << "Using non-inlined copy function:\n";
    copyBytes(destBuffer, srcBuffer, BUFFER_SIZE);
    std::cout << "Destination: " << destBuffer << std::endl;

    // Using inlined copy function
    std::cout << "\nUsing inlined copy function:\n";
    inlineCopyBytes(destBuffer, srcBuffer, BUFFER_SIZE);
    std::cout << "Destination: " << destBuffer << std::endl;

    return 0;
}

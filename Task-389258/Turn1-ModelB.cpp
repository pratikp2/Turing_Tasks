#include <iostream>
#include <cstring>

const unsigned int CANARY_SIZE = sizeof(unsigned int);

void *canary_alloc(size_t size) {
    void *ptr = malloc(size + CANARY_SIZE);
    unsigned int *canary = static_cast<unsigned int *>(ptr);
    *canary = 0xDEADBEEF; // Random canary value
    return reinterpret_cast<void *>(canary + 1);
}

void canary_free(void *ptr) {
    unsigned int *canary = static_cast<unsigned int *>(ptr) - 1;
    if (*canary != 0xDEADBEEF) {
        // Memory overflow detected
        std::cout << "Memory overflow detected!" << std::endl;
        exit(EXIT_FAILURE);
    }
    free(canary);
}

// Example function that may be prone to a buffer overflow
void vulnerable_function(char *input, size_t size) {
    char buffer[16];
    std::strcpy(buffer, input);
}

int main() {
    // Allocate memory with canary
    char *input = static_cast<char *>(canary_alloc(16));
    std::cin >> input;

    // Call the vulnerable function
    vulnerable_function(input, 16);

    // Free memory with canary
    canary_free(input);

    return 0;
}

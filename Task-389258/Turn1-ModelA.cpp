#include <cstdlib>
#include <iostream>

using namespace std;

void bufferOverflow(char* buffer, size_t bufferSize) {
    // Generate a random canary value
    uint32_t canary = rand();
    cout << "Generated canary: " << hex << canary << endl;

    // Place the canary on the stack
    char canaryStack[sizeof(uint32_t)];
    memcpy(canaryStack, &canary, sizeof(uint32_t));

    // Place the buffer on the stack
    cout << "Buffer size: " << bufferSize << endl;
    char bufferStack[bufferSize];

    // Copy data into the buffer
    strcpy(bufferStack, buffer);

    // Validate the canary
    uint32_t checkedCanary;
    memcpy(&checkedCanary, canaryStack, sizeof(uint32_t));
    
    if (checkedCanary != canary) {
        cout << "Buffer overflow detected! Canary was modified!" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Canary was not modified, function returning safely." << endl;
}

int main() {
    char* input = "This is a buffer overflow test";
    bufferOverflow(input, 20); // This will cause an overflow

    return 0;
}

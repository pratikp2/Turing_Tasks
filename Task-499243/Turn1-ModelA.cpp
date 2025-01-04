#include <iostream>
#include <cstring>

// Example structure that holds an array
struct Buffer {
    char data[256];
};

// Inline function to copy data from one buffer to another
inline void inline_memcpy(Buffer &dest, const Buffer &src) {
    std::memcpy(dest.data, src.data, sizeof(dest.data));
}

// A function that uses the inline memcpy
void processBuffers() {
    Buffer buffer1;
    Buffer buffer2;
    
    // Initialize buffer1
    std::strcpy(buffer1.data, "Hello, World!");
    
    // Perform multiple copies using inline function
    for (int i = 0; i < 1000; ++i) {
        inline_memcpy(buffer2, buffer1);
        
        // Do something with buffer2
        std::cout << "Buffer2 content: " << buffer2.data << " (iteration " << i << ")" << std::endl;
    }
}

int main() {
    processBuffers();
    return 0;
}

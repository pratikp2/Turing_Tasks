#include <iostream>
#include <vector>

class ArenaAllocator {
public:
    ArenaAllocator(size_t size) : buffer(new char[size]), end(buffer + size), current(buffer) {}

    ~ArenaAllocator() { delete[] buffer; }

    void* allocate(size_t size) {
        if (current + size > end) {
            return nullptr; // No more space in the arena
        }
        void* result = current;
        current += size;
        return result;
    }

private:
    char* buffer;
    char* end;
    char* current;
};

int main() {
    const size_t arena_size = 1024; // 1KB arena
    ArenaAllocator allocator(arena_size);

    // Allocate memory from the arena
    int* data1 = (int*)allocator.allocate(sizeof(int));
    double* data2 = (double*)allocator.allocate(sizeof(double));
    char* data3 = (char*)allocator.allocate(100);

    // Use the allocated memory
    *data1 = 42;
    *data2 = 3.14;
    std::strcpy(data3, "Hello, Arena Allocation!");

    // If the arena is full, allocate() will return nullptr
    if (allocator.allocate(1)) {
        std::cout << "Arena allocation failed." << std::endl;
    }

    return 0;
}
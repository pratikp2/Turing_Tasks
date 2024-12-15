#include <iostream>
#include <cassert>
#include <cstddef>

class PoolAllocator {
public:
    explicit PoolAllocator(std::size_t poolSize)
        : poolSize(poolSize), pool(new char[poolSize]), offset(0) {}

    ~PoolAllocator() {
        delete[] pool;
    }

    void* allocate(std::size_t size) {
        // Align size to the nearest multiple of sizeof(void*)
        size = (size + sizeof(void*) - 1) & ~(sizeof(void*) - 1); 

        if (offset + size > poolSize) {
            // Out of memory in the pool
            return nullptr;
        }

        void* ptr = pool + offset;
        offset += size; // Move the offset for the next allocation
        return ptr;
    }

    void deallocate(void* ptr) {
        // In this simple pool allocator, we do not implement deallocation.
        // You would typically implement a more complex strategy for real applications.
    }

    void reset() {
        offset = 0; // Reset the pool for reuse
    }

private:
    std::size_t poolSize;
    char* pool;
    std::size_t offset;
};

int main() {
    const int poolSize = 1024; // Size of the memory pool
    PoolAllocator allocator(poolSize);

    // Allocate some memory chunks
    int* intArray = static_cast<int*>(allocator.allocate(10 * sizeof(int)));
    assert(intArray != nullptr);

    for (int i = 0; i < 10; ++i) {
        intArray[i] = i;
    }

    // Print the allocated integers
    for (int i = 0; i < 10; ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;

    // Allocate another chunk
    double* doubleArray = static_cast<double*>(allocator.allocate(5 * sizeof(double)));
    assert(doubleArray != nullptr);

    for (int i = 0; i < 5; ++i) {
        doubleArray[i] = i * 1.1;
    }

    // Print the allocated doubles
    for (int i = 0; i < 5; ++i) {
        std::cout << doubleArray[i] << " ";
    }
    std::cout << std::endl;

    // Reset the allocator to reuse memory
    allocator.reset();

    return 0;
}

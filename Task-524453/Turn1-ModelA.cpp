#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

class MemoryPool {
public:
    MemoryPool(size_t size);
    ~MemoryPool();
    
    void* allocate(size_t numBytes);
    void deallocate(void* ptr);
    
private:
    size_t poolSize;
    char* pool;
    std::vector<void*> freeBlocks;

    void registerFreeBlock(void* ptr, size_t size);
    void mergeFreeBlocks();
};

MemoryPool::MemoryPool(size_t size) 
    : poolSize(size), pool(static_cast<char*>(std::malloc(size)))
{
    assert(pool != nullptr);
}

MemoryPool::~MemoryPool() {
    std::free(pool);
}

void* MemoryPool::allocate(size_t numBytes) {
    if (numBytes <= 0 || numBytes > poolSize) {
        return nullptr;
    }

    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        size_t blockSize = *static_cast<size_t*>(*it - sizeof(size_t));
        if (blockSize >= numBytes) {
            freeBlocks.erase(it);
            return *it;
        }
    }

    return nullptr;  // No suitable free block found
}

void MemoryPool::deallocate(void* ptr) {
    if (ptr) {
        size_t blockSize = *static_cast<size_t*>(ptr - sizeof(size_t));
        registerFreeBlock(ptr, blockSize);
        mergeFreeBlocks();
    }
}

void MemoryPool::registerFreeBlock(void* ptr, size_t size) {
    // Store size in the beginning of the block to keep track
    *static_cast<size_t*>(ptr - sizeof(size_t)) = size;
    freeBlocks.push_back(static_cast<char*>(ptr) - sizeof(size_t)); // Account for size header
}

void MemoryPool::mergeFreeBlocks() {
    // For simplicity, we will not merge free blocks in this example
    // This function should combine adjacent free blocks to avoid fragmentation.
    // This is a key improvement for memory efficiency.
}

// Example of usage:
int main() {
    MemoryPool pool(1024 * 1024); // 1MB pool

    // For example: allocating memory for an array of temperatures (e.g., 1000 floats)
    float* temperatureData = static_cast<float*>(pool.allocate(1000 * sizeof(float)));
    if (temperatureData) {
        for (int i = 0; i < 1000; ++i) {
            temperatureData[i] = i * 1.0f; // Init with some values
        }
    }

    // ... use the temperature data ...

    // When done, deallocate the memory
    pool.deallocate(static_cast<void*>(temperatureData));

    return 0;
}

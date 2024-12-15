#include <iostream>
#include <cassert>
#include <cstddef>
#include <cstring>

class PoolAllocator {
public:
    explicit PoolAllocator(std::size_t poolSize = 4096)
        : poolSize(poolSize), pool(new char[poolSize]), offset(0) {}

    ~PoolAllocator() {
        delete[] pool;
    }

    void* allocate(std::size_t size) {
        // Align size to the nearest multiple of sizeof(void*)
        size = (size + sizeof(void*) - 1) & ~(sizeof(void*) - 1);

        if (offset + size > poolSize) {
            // Reallocate more memory if the pool is exhausted
            char* newPool = new char[poolSize * 2]; // Double the pool size for simplicity
            std::memcpy(newPool, pool, offset);
            delete[] pool;
            pool = newPool;
            poolSize *= 2;
        }

        void* ptr = pool + offset;
        offset += size;
        return ptr;
    }

    void deallocate(void* ptr) {} // Implementation not provided in this basic version

    void reset() {
        offset = 0;
    }

private:
    std::size_t poolSize;
    char* pool;
    std::size_t offset;
};

int main() {
    // Example usage remains the same
    // ...

    return 0;
}

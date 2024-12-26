#include <iostream>
#include <cstdlib>
#include <vector>
#include <mutex>

class MemoryPool {
public:
    MemoryPool(size_t blockSize, size_t blockCount) 
        : blockSize(blockSize), blockCount(blockCount), freeBlocks(blockCount) {
        
        pool = malloc(blockSize * blockCount); // Allocate memory for the pool
        if (!pool) throw std::bad_alloc();

        // Create the linked list of free blocks
        for (size_t i = 0; i < blockCount; ++i) {
            freeList.push_back(static_cast<char*>(pool) + i * blockSize);
        }
    }

    ~MemoryPool() {
        free(pool);
    }

    void* allocate() {
        std::lock_guard<std::mutex> lock(mutex);
        if (freeList.empty()) {
            return nullptr; // No free blocks available
        }
        
        // Get a block from the free list
        void* block = freeList.back();
        freeList.pop_back();
        return block;
    }

    void deallocate(void* block) {
        std::lock_guard<std::mutex> lock(mutex);
        freeList.push_back(static_cast<char*>(block)); // Return block to free list
    }

private:
    void* pool; // The allocated block of memory
    size_t blockSize; // Size of each block
    size_t blockCount; // Total number of blocks
    std::vector<void*> freeList; // List of free blocks
    std::mutex mutex; // Mutex for thread safety
};

// Usage Example
struct Data {
    int id;
    float value;
};

int main() {
    MemoryPool pool(sizeof(Data), 10); // Create a pool for 10 Data structures

    // Allocate a Data object
    Data* d1 = static_cast<Data*>(pool.allocate());
    if (d1) {
        d1->id = 1;
        d1->value = 42.0f;
        std::cout << "Allocated: " << d1->id << ", " << d1->value << std::endl;
    }

    // Deallocate the object
    pool.deallocate(d1);

    return 0;
}

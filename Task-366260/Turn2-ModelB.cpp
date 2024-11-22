#include <iostream>

// Simple buddy allocator implementation
class BuddyAllocator {
public:
    BuddyAllocator(size_t totalSize) : totalSize(totalSize) {
        heap = new char[totalSize];
        freeBlocks = new bool[totalSize / blockSize];
        for (size_t i = 0; i < totalSize / blockSize; i++) {
            freeBlocks[i] = true;
        }
    }

    ~BuddyAllocator() {
        delete[] heap;
        delete[] freeBlocks;
    }

    void* allocate(size_t size) {
        size_t index = findFreeBlock(size);
        if (index == SIZE_MAX) {
            return nullptr;
        }

        freeBlocks[index] = false;
        return heap + index * blockSize;
    }

    void deallocate(void* ptr) {
        size_t index = (reinterpret_cast<char*>(ptr) - heap) / blockSize;
        freeBlocks[index] = true;
    }

private:
    size_t findFreeBlock(size_t size) {
        // Simple implementation for demonstration purposes
        for (size_t i = 0; i < totalSize / blockSize; i++) {
            if (freeBlocks[i] && getBlockSize(i) >= size) {
                return i;
            }
        }
        return SIZE_MAX;
    }

    size_t getBlockSize(size_t index) {
        return blockSize;
    }

    const size_t totalSize;
    const size_t blockSize = 64; // Assuming fixed-size blocks
    char* heap;
    bool* freeBlocks;
};

int main() {
    BuddyAllocator allocator(1024); // 1KB heap

    void* ptr1 = allocator.allocate(128);
    void* ptr2 = allocator.allocate(64);
    void* ptr3 = allocator.allocate(32);

    // Do some work...

    allocator.deallocate(ptr2);
    allocator.deallocate(ptr3);
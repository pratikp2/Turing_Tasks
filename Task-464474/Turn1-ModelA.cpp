#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_POOL_SIZE 32
#define BLOCK_SIZE 4

// Memory pool represented as an array of bytes
uint8_t memoryPool[MEMORY_POOL_SIZE];

// A bitmap to track allocated blocks
uint32_t allocationMap = 0;

// Function to allocate a block of memory
void* allocateBlock() {
    for (int i = 0; i < MEMORY_POOL_SIZE / BLOCK_SIZE; i++) {
        if (!(allocationMap & (1 << i))) { // Check if the block is free
            allocationMap |= (1 << i); // Mark block as allocated
            return &memoryPool[i * BLOCK_SIZE]; // Return pointer to the block
        }
    }
    return NULL; // No free blocks available
}

// Function to deallocate a block of memory
void deallocateBlock(void* block) {
    int index = ((uint8_t*)block - memoryPool) / BLOCK_SIZE;
    allocationMap &= ~(1 << index); // Mark block as free
}

// Function to print the allocation map
void printAllocationMap() {
    printf("Allocation Bitmap: ");
    for (int i = 0; i < MEMORY_POOL_SIZE / BLOCK_SIZE; i++) {
        printf("%d", (allocationMap & (1 << i)) ? 1 : 0);
    }
    printf("\n");
}

int main() {
    void* block1 = allocateBlock();
    printAllocationMap(); // Should show block 0 as allocated

    void* block2 = allocateBlock();
    printAllocationMap(); // Should show blocks 0 and 1 as allocated

    deallocateBlock(block1);
    printAllocationMap(); // Should show block 0 as free again

    void* block3 = allocateBlock();
    printAllocationMap(); // Should show block 0 (allocated again) and 1 as allocated

    deallocateBlock(block2);
    deallocateBlock(block3);
    
    printAllocationMap(); // All blocks should be free
    return 0;
}

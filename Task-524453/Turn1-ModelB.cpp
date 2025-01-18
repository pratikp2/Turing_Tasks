#include <iostream>
#include <cstdlib> // For size_t
#include <cstddef> // For std::nullptr_t

// Define a custom allocator
class MeteorologicalAllocator {

private:
    const size_t page_size;
    char* heap_base;
    size_t heap_size;
    unsigned char* bitmap;

    size_t min_block_size;

public:
    MeteorologicalAllocator(size_t initial_heap_size, size_t page_size = 4096, size_t min_block_size = 1024) : 
            page_size(std::max(page_size, min_block_size)),
            min_block_size(min_block_size) {
        
        // Round up the initial heap size to a multiple of the page size
        heap_size = ((initial_heap_size - 1) / page_size) * page_size + page_size;

        heap_base = static_cast<char*>(std::malloc(heap_size));
        if (heap_base == nullptr) {
            std::cerr << "Error: Cannot allocate initial heap." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Initialize the bitmap: all blocks are free
        bitmap = new unsigned char[(heap_size + sizeof(size_t) - 1) / sizeof(unsigned char)];
        std::memset(bitmap, 0, (heap_size + sizeof(size_t) - 1) / sizeof(unsigned char));
    }

    ~MeteorologicalAllocator() {
        std::free(heap_base);
        delete[] bitmap;
    }

private:
    // Helper function: returns the address of the n-th byte in the bitmap
    unsigned char* bitmap_index(size_t block_index) const {
        return bitmap + (block_index / 8);
    }

    // Helper function: sets a bit in the bitmap
    void set_bit(size_t block_index) {
        *(bitmap_index(block_index)) |= (1 << (block_index % 8));
    }

    // Helper function: clears a bit in the bitmap
    void clear_bit(size_t block_index) {
        *(bitmap_index(block_index)) &= ~(1 << (block_index % 8));
    }

    // Helper function: checks if a bit is set in the bitmap
    bool test_bit(size_t block_index) const {
        return (*(bitmap_index(block_index)) & (1 << (block_index % 8))) != 0;
    }

    struct Block {
        size_t size;
        bool allocated;
    };

    Block get_block_info(size_t block_index) const {
        Block info;
        info.size = (block_index == heap_size / page_size) ? (heap_size - block_index * page_size) : page_size;
        info.allocated = test_bit(block_index);
        return info;
    }

    // First-fit heuristic for allocation
    size_t find_free_block(size_t size) {
        size_t num_blocks = heap_size / page_size;
        for (size_t i = 0; i < num_blocks; ++i) {
            Block info = get_block_info(i);
            if (!info.allocated && info.size >= size) {
                return i;
            }
        }
        return -1; // No free block found
    }

    void coalesce_free_blocks(size_t block_index) {
        Block current = get_block_info(block_index);
        while (true) {
            block_index++;
            if (block_index == heap_size / page_size) {
                break;
            }
            Block next = get_block_info(block_index);
            if (next.allocated) {
                break;
            }

            // Coalesce the free blocks
            current.size += next.size;
            clear_bit(block_index);
        }
    }

public:
    // Allocate memory. Size is in bytes, aligns to page_size.
    void* allocate(size_t size) {
        if (size < min_block_size) {
            size = min_block_size;
        }
        size = ((size - 1) / page_size) * page_size + page_size;

        size_t block_index = find_free_block(size);
        if (block_index == -1) {
            std::cerr << "Error: No free memory available." << std::endl;
            return nullptr;
        }

        // Mark the block as allocated
        set_bit(block_index);

        coalesce_free_blocks(block_index);

        return heap_base + block_index * page_size;
    }

    // Deallocate memory
    void deallocate(void* ptr) {
        if (ptr == nullptr) {
            return;
        }

        size_t block_index = (static_cast<char*>(ptr) - heap_base) / page_size;
        clear_bit(block_index);

        coalesce_free_blocks(block_index);
    }

}; 
// Using the allocator
int main() {
    MeteorologicalAllocator allocator(1024 * 1024 * 8);  // 8MB heap

    void* ptr1 = allocator.allocate(1024 * 10);  // 10KB
    void* ptr2 = allocator.allocate(1024 * 100);  // 100KB

    std::cout << "ptr1: " << ptr1 << std::endl;
    std::cout << "ptr2: " << ptr2 << std::endl;

    allocator.deallocate(ptr1);

    return 0;
}

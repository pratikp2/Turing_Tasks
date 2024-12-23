#include <stdint.h>

// 8-bit memory block
uint8_t memory_block = 0x00; // Initialized with all zeros

// Define bit masks for specific positions in the memory block
const uint8_t FLAG_A = 0b00000001;  // LSB
const uint8_t FLAG_B = 0b00000010;
const uint8_t FLAG_C = 0b00000100;
const uint8_t FLAG_D = 0b00001000;

// Function to 'allocate' a bit (set it to 1)
void allocate_bit(uint8_t* memory_block, uint8_t flag) {
    *memory_block |= flag; // Set the corresponding bit to 1 using bitwise OR
}

// Function to 'deallocate' a bit (set it to 0)
void deallocate_bit(uint8_t* memory_block, uint8_t flag) {
    *memory_block &= ~flag; // Clear the corresponding bit using bitwise AND with complement
}

// Function to check if a bit is 'allocated' (read it)
bool is_bit_allocated(uint8_t* memory_block, uint8_t flag) {
    return (*memory_block & flag) != 0; // Check if the bit is set using bitwise AND
}

int main() {
    // Allocate bits
    allocate_bit(&memory_block, FLAG_A); // Set flag A
    allocate_bit(&memory_block, FLAG_C); // Set flag C

    // Status check
    if (is_bit_allocated(&memory_block, FLAG_A)) {
        printf("Flag A is allocated.\n");
    }

    if (is_bit_allocated(&memory_block, FLAG_B)) {
        printf("Flag B is allocated.\n");  // Should be 0
    }

    // Deallocate a bit
    deallocate_bit(&memory_block, FLAG_C); // Free flag C

    return 0;
}

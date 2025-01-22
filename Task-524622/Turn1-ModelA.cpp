#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Constants for bit positions and masks
#define SPEED_MASK         0xFF00  // Bits 8-15 for speed
#define TEMP_MASK          0x00F0  // Bits 4-7 for temperature
#define FAULT_CODE_MASK    0x000F  // Bits 0-3 for fault codes

// Function to extract speed from sensor data
uint8_t extract_speed(uint16_t sensor_data) {
    return (sensor_data & SPEED_MASK) >> 8; // Shift to get speed in lower 8 bits
}

// Function to extract temperature from sensor data
uint8_t extract_temperature(uint16_t sensor_data) {
    return (sensor_data & TEMP_MASK) >> 4; // Shift to get temperature in lower 4 bits
}

// Function to check for faults based on fault codes
bool check_faults(uint16_t sensor_data) {
    return (sensor_data & FAULT_CODE_MASK) != 0; // If any fault code bits are set
}

// Main function for testing
int main() {
    uint16_t sensor_data = 0xABCD; // Example sensor data

    // Extracting values
    uint8_t speed = extract_speed(sensor_data);
    uint8_t temperature = extract_temperature(sensor_data);
    bool has_fault = check_faults(sensor_data);

    // Output results
    printf("Speed: %u\n", speed);
    printf("Temperature: %u\n", temperature);
    printf("Fault detected: %s\n", has_fault ? "Yes" : "No");

    return 0;
}

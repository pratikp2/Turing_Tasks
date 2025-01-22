#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Define control register and bit masks
#define CONTROL_REGISTER_SIZE 8
uint8_t control_register = 0x00; // Start with all flags cleared

// Bit masks for each flag
#define SENSOR_HEALTH_MASK       (1 << 0) // 0b00000001
#define EMERGENCY_BRAKING_MASK   (1 << 1) // 0b00000010
#define TEMPERATURE_REGULATION_MASK (1 << 2) // 0b00000100

// Function to check the status of each flag
bool is_sensor_healthy() {
    return (control_register & SENSOR_HEALTH_MASK) != 0;
}

bool is_emergency_braking_active() {
    return (control_register & EMERGENCY_BRAKING_MASK) != 0;
}

bool is_temperature_regulation_active() {
    return (control_register & TEMPERATURE_REGULATION_MASK) != 0;
}

// Function to update sensor health flag
void update_sensor_health(bool healthy) {
    if (healthy) {
        control_register |= SENSOR_HEALTH_MASK; // Set the sensor health flag
    } else {
        control_register &= ~SENSOR_HEALTH_MASK; // Clear the sensor health flag
    }
}

// Function to update emergency braking flag
void update_emergency_braking(bool active) {
    if (active) {
        control_register |= EMERGENCY_BRAKING_MASK; // Set the emergency braking flag
    } else {
        control_register &= ~EMERGENCY_BRAKING_MASK; // Clear the emergency braking flag
    }
}

// Function to update temperature regulation flag
void update_temperature_regulation(bool active) {
    if (active) {
        control_register |= TEMPERATURE_REGULATION_MASK; // Set the temperature regulation flag
    } else {
        control_register &= ~TEMPERATURE_REGULATION_MASK; // Clear the temperature regulation flag
    }
}

// Main function for testing
int main() {
    // Initial state check
    printf("Initial States:\n");
    printf("Sensor Healthy: %s\n", is_sensor_healthy() ? "Yes" : "No");
    printf("Emergency Braking: %s\n", is_emergency_braking_active() ? "Yes" : "No");
    printf("Temperature Regulation: %s\n", is_temperature_regulation_active() ? "Yes" : "No");

    // Update flags
    update_sensor_health(true);
    update_emergency_braking(true);
    update_temperature_regulation(false);

    // State after updates
    printf("\nStates After Updates:\n");
    printf("Sensor Healthy: %s\n", is_sensor_healthy() ? "Yes" : "No");
    printf("Emergency Braking: %s\n", is_emergency_braking_active() ? "Yes" : "No");
    printf("Temperature Regulation: %s\n", is_temperature_regulation_active() ? "Yes" : "No");

    return 0;
}

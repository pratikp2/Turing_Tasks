#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Define control register and bit masks
#define CONTROL_REGISTER_SIZE 8
uint8_t control_register = 0x00; // Start with all flags cleared (0b00000000)

// Bit masks for each flag
#define SENSOR_HEALTH_MASK       (1 << 0) // 0b00000001 - Sensor health flag
#define EMERGENCY_BRAKING_MASK   (1 << 1) // 0b00000010 - Emergency braking flag
#define TEMPERATURE_REGULATION_MASK (1 << 2) // 0b00000100 - Temperature regulation flag

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

// Function to validate the emergency braking flag based on safety rules
void validate_emergency_braking_state() {
    if (is_emergency_braking_active()) {
        // Check if sensor health is also okay when emergency braking is active
        if (is_sensor_healthy()) {
            printf("Safety Status: Emergency braking is active and sensor health is OK.\n");
        } else {
            printf("Safety Status: Emergency braking is active but sensor health is NOT OK!\n");
            // Additional handling could be done here, such as logging or alerting
        }
    } else {
        printf("Safety Status: Emergency braking is NOT active.\n");
        // Any actions to take when emergency braking is off can be added here
    }
}

// Main function for testing
int main() {
    // Initial state check
    printf("Initial States:\n");
    validate_emergency_braking_state(); // Check emergency braking state initially

    // Update flags (e.g., simulate scenario)
    update_sensor_health(true);       // Set sensor health to OK
    update_emergency_braking(true);    // Activate emergency braking
    update_temperature_regulation(false); // Deactivate temperature regulation (not relevant for this check)

    // State after updates
    printf("\nStates After Updates:\n");
    validate_emergency_braking_state(); // Recheck emergency braking state

    return 0;
}

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

/**
 * @brief Check the status of each flag.
 * @param mask The mask corresponding to the flag to check.
 * @return true if the flag is set, false otherwise.
 */
bool is_flag_set(uint8_t mask) {
    return (control_register & mask) != 0;
}

/**
 * @brief Update the state of a flag.
 * @param mask The mask corresponding to the flag to update.
 * @param value true to set the flag, false to clear the flag.
 */
void update_flag(uint8_t mask, bool value) {
    if (value) {
        control_register |= mask; // Set the flag
    } else {
        control_register &= ~mask; // Clear the flag
    }
}

/**
 * @brief Validate the state of the emergency braking flag based on safety rules.
 *
 * According to the safety rules:
 * - Emergency braking can only be activated if sensor health is good.
 * - Emergency braking must be deactivated if temperature regulation is not active.
 *
 * @return true if the emergency braking flag state is valid, false otherwise.
 */
bool validate_emergency_braking() {
    // Check if sensor health is good
    if (!is_flag_set(SENSOR_HEALTH_MASK)) {
        printf("Safety Rule Violation: Emergency braking activated with bad sensor health.\n");
        return false;
    }

    // Check if temperature regulation is active
    if (!is_flag_set(TEMPERATURE_REGULATION_MASK)) {
        printf("Safety Rule Violation: Emergency braking active with temperature regulation disabled.\n");
        return false;
    }

    return true;
}

/**
 * @brief Generate a safety status report based on the flag states.
 */
void generate_safety_status_report() {
    printf("\nSafety Status Report:\n");

    if (is_flag_set(EMERGENCY_BRAKING_MASK)) {
        if (validate_emergency_braking()) {
            printf("Emergency Braking: Active - Valid state\n");
        } else {
            printf("Emergency Braking: Active - Invalid state\n");
        }
    } else {
        printf("Emergency Braking: Inactive\n");
    }

    printf("Sensor Healthy: %s\n", is_flag_set(SENSOR_HEALTH_MASK) ? "Yes" : "No");
    printf("Temperature Regulation: %s\n", is_flag_set(TEMPERATURE_REGULATION_MASK) ? "Yes" : "No");
}

// Main function for testing
int main() {
    // Initial state check
    printf("Initial States:\n");
    printf("Sensor Healthy: %s\n", is_flag_set(SENSOR_HEALTH_MASK) ? "Yes" : "No");
    printf("Emergency Braking: %s\n", is_flag_set(EMERGENCY_BRAKING_MASK) ? "Yes" : "No");
    printf("Temperature Regulation: %s\n", is_flag_set(TEMPERATURE_REGULATION_MASK) ? "Yes" : "No");

    // Update flags
    update_flag(SENSOR_HEALTH_MASK, true); // Sensor health is good
    update_flag(EMERGENCY_BRAKING_MASK, true); // Activate emergency braking
    update_flag(TEMPERATURE_REGULATION_MASK, true); // Temperature regulation is active

    // Generate safety status report
    generate_safety_status_report();

    return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Define constants for each flag position in the control register
#define SENSOR_HEALTH_FLAG  (1 << 0)  // Bit 0
#define EMERGENCY_BRAKING_FLAG (1 << 1)  // Bit 1
#define TEMPERATURE_REGULATION_FLAG (1 << 2)  // Bit 2

// Control register variable
uint32_t control_register = 0;

// Function to set a flag
void set_flag(uint32_t flag) {
    control_register |= flag;
}

// Function to clear a flag
void clear_flag(uint32_t flag) {
    control_register &= ~flag;
}

// Function to check the status of a flag
bool check_flag(uint32_t flag) {
    return (control_register & flag) != 0;
}

// Example usage:
int main() {
    // Initialise the control register
    control_register = 0;

    // Set the Sensor Health flag
    printf("Setting Sensor Health flag...\n");
    set_flag(SENSOR_HEALTH_FLAG);
    if (check_flag(SENSOR_HEALTH_FLAG)) {
        printf("Sensor Health flag: Set\n");
    } else {
        printf("Sensor Health flag: Not set\n");
    }

    // Set the Emergency Braking flag
    printf("\nSetting Emergency Braking flag...\n");
    set_flag(EMERGENCY_BRAKING_FLAG);
    if (check_flag(EMERGENCY_BRAKING_FLAG)) {
        printf("Emergency Braking flag: Set\n");
    } else {
        printf("Emergency Braking flag: Not set\n");
    }

    // Clear the Temperature Regulation flag
    printf("\nClearing Temperature Regulation flag...\n");
    clear_flag(TEMPERATURE_REGULATION_FLAG);
    if (check_flag(TEMPERATURE_REGULATION_FLAG)) {
        printf("Temperature Regulation flag: Set\n");
    } else {
        printf("Temperature Regulation flag: Not set\n");
    }

    // Monitor all flags
    printf("\nCurrent status of all flags:\n");
    if (check_flag(SENSOR_HEALTH_FLAG)) {
        printf("Sensor Health flag: Set\n");
    } else {
        printf("Sensor Health flag: Not set\n");
    }

    if (check_flag(EMERGENCY_BRAKING_FLAG)) {
        printf("Emergency Braking flag: Set\n");
    } else {
        printf("Emergency Braking flag: Not set\n");
    }

    if (check_flag(TEMPERATURE_REGULATION_FLAG)) {
        printf("Temperature Regulation flag: Set\n");
    } else {
        printf("Temperature Regulation flag: Not set\n");
    }

    return 0;
}

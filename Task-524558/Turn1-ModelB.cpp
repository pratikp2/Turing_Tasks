#include <stdbool.h>
#include <stdint.h>

#define POWER_SAVING_MODE      0x01  // Bit 0
#define HIGH_PERFORMANCE_MODE   0x02  // Bit 1
#define DEBUGGING_MODE         0x04  // Bit 2

typedef uint8_t ConfigMode;

void set_config_mode(ConfigMode mode, bool enable) {
    static ConfigMode current_mode = 0;
    if (enable) {
        current_mode |= mode;
    } else {
        current_mode &= ~mode;
    }
}

bool is_config_mode_enabled(ConfigMode mode) {
    static ConfigMode current_mode = 0;
    return (current_mode & mode) != 0;
}

void clear_all_config_modes() {
    static ConfigMode current_mode = 0;
    current_mode = 0;
}
int main() {
    set_config_mode(POWER_SAVING_MODE, true);
    set_config_mode(HIGH_PERFORMANCE_MODE, false);
    set_config_mode(DEBUGGING_MODE, true);

    printf("Power Saving Mode: %s\n", is_config_mode_enabled(POWER_SAVING_MODE) ? "Enabled" : "Disabled");
    printf("High Performance Mode: %s\n", is_config_mode_enabled(HIGH_PERFORMANCE_MODE) ? "Enabled" : "Disabled");  
    printf("Debugging Mode: %s\n", is_config_mode_enabled(DEBUGGING_MODE) ? "Enabled" : "Disabled");

    clear_all_config_modes();

    printf("\nAfter clearing all modes:\n");
    printf("Power Saving Mode: %s\n", is_config_mode_enabled(POWER_SAVING_MODE) ? "Enabled" : "Disabled");
    
    return 0;
}

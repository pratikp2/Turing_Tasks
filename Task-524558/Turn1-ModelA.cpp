#include <iostream>
#include <cstdint>

class ConfigManager {
private:
    uint8_t config; // Bitmask for modes (1 byte for compactness)

public:
    // Constructor
    ConfigManager() : config(0) {}

    // Set a mode
    void setMode(uint8_t mode) {
        config |= mode; // Use bitwise OR to set the mode
    }

    // Clear a mode
    void clearMode(uint8_t mode) {
        config &= ~mode; // Use bitwise AND with NOT to clear the mode
    }

    // Toggle a mode
    void toggleMode(uint8_t mode) {
        config ^= mode; // Use bitwise XOR to toggle the mode
    }

    // Check if a mode is set
    bool isModeSet(uint8_t mode) const {
        return (config & mode) != 0; // Use bitwise AND to check the mode
    }

    // Print current configuration
    void printConfig() const {
        std::cout << "Current Config: 0x" << std::hex << static_cast<int>(config) << std::dec << std::endl;
    }
};

// Define operational modes
const uint8_t POWER_SAVING_MODE = 0x01;   // 0000 0001
const uint8_t HIGH_PERFORMANCE_MODE = 0x02; // 0000 0010
const uint8_t DEBUGGING_MODE = 0x04;        // 0000 0100

// Example usage
int main() {
    ConfigManager cfgManager;

    // Set modes
    cfgManager.setMode(POWER_SAVING_MODE);
    cfgManager.setMode(DEBUGGING_MODE);
    cfgManager.printConfig(); // Should display 0x05

    // Toggle high performance mode
    cfgManager.toggleMode(HIGH_PERFORMANCE_MODE);
    cfgManager.printConfig(); // Should now display 0x07 (0x05 | 0x02)

    // Clear power saving mode
    cfgManager.clearMode(POWER_SAVING_MODE);
    cfgManager.printConfig(); // Should now display 0x06 (0x07 & ~0x01)

    // Check if debug mode is set
    if (cfgManager.isModeSet(DEBUGGING_MODE)) {
        std::cout << "Debugging mode is enabled." << std::endl;
    }

    // Clear debugging mode and check again
    cfgManager.clearMode(DEBUGGING_MODE);
    if (!cfgManager.isModeSet(DEBUGGING_MODE)) {
        std::cout << "Debugging mode is now disabled." << std::endl;
    }

    return 0;
}

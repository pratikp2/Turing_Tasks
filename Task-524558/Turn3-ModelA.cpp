#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

class ConfigManager {
private:
    uint8_t config; // Bitmask to hold configuration modes

public:
    // Constructor
    ConfigManager() : config(0) {}

    // Add a mode
    void addMode(uint8_t mode) {
        config |= mode; // Use bitwise OR to set the mode
    }

    // Remove a mode
    void removeMode(uint8_t mode) {
        config &= ~mode; // Use bitwise AND with NOT to clear the mode
    }

    // Check if a mode is set
    bool isModeSet(uint8_t mode) const {
        return (config & mode) != 0; // Use bitwise AND to check the mode
    }

    // Fetch the current configuration as a string of enabled modes
    std::vector<std::string> getCurrentConfiguration() const {
        std::vector<std::string> activeModes;
        if (isModeSet(POWER_SAVING_MODE)) activeModes.push_back("Power Saving");
        if (isModeSet(HIGH_PERFORMANCE_MODE)) activeModes.push_back("High Performance");
        if (isModeSet(DEBUGGING_MODE)) activeModes.push_back("Debugging");
        
        return activeModes;
    }

    // Print the current configuration in readable format
    void printConfig() const {
        std::cout << "Active Configurations: ";
        const auto activeModes = getCurrentConfiguration();
        if (activeModes.empty())
            std::cout << "None";
        else
            for (const auto& mode : activeModes)
                std::cout << mode << " ";
        std::cout << std::endl;
    }
};

// Define operational modes as constants
const uint8_t POWER_SAVING_MODE = 0x01;   // 0000 0001
const uint8_t HIGH_PERFORMANCE_MODE = 0x02; // 0000 0010
const uint8_t DEBUGGING_MODE = 0x04;        // 0000 0100

// Example usage
int main() {
    ConfigManager cfgManager;

    // Add modes
    cfgManager.addMode(POWER_SAVING_MODE);
    cfgManager.addMode(DEBUGGING_MODE);
    cfgManager.printConfig(); // Should display "Power Saving Debugging"

    // Add high-performance mode
    cfgManager.addMode(HIGH_PERFORMANCE_MODE);
    cfgManager.printConfig(); // Should display "Power Saving Debugging High Performance"

    // Remove power saving mode
    cfgManager.removeMode(POWER_SAVING_MODE);
    cfgManager.printConfig(); // Should display "Debugging High Performance"

    // Check if debugging mode is set
    if (cfgManager.isModeSet(DEBUGGING_MODE)) {
        std::cout << "Debugging mode is enabled." << std::endl;
    }

    // Remove debugging mode
    cfgManager.removeMode(DEBUGGING_MODE);
    cfgManager.printConfig(); // Should display "High Performance"

    return 0;
}

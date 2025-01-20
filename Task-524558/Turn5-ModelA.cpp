#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

const uint8_t POWER_SAVING_MODE = 0x01;    // 0000 0001
const uint8_t HIGH_PERFORMANCE_MODE = 0x02; // 0000 0010
const uint8_t DEBUGGING_MODE = 0x04;         // 0000 0100

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

    // Log current active modes
    std::string logActiveModes() const {
        std::ostringstream oss;
        const auto activeModes = getCurrentConfiguration();
        if (activeModes.empty()) {
            oss << "No active modes.";
        } else {
            oss << "Active Configurations: ";
            for (const auto& mode : activeModes) {
                oss << mode << " ";
            }
        }
        return oss.str();
    }

    // Print the current configuration in readable format
    void printConfig() const {
        std::cout << logActiveModes() << std::endl;
    }

    // Save configuration to a file
    bool saveConfig(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false; // Failed to open the file
        }
        file << static_cast<int>(config); // Save the config as an integer
        file.close();
        return true; // Success
    }

    // Load configuration from a file
    bool loadConfig(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false; // Failed to open the file
        }
        int value;
        file >> value; // Read the integer value from file
        config = static_cast<uint8_t>(value); // Set the config from the file
        file.close();
        return true; // Success
    }
};

// Example usage
int main() {
    ConfigManager cfgManager;

    // Add some modes
    cfgManager.addMode(POWER_SAVING_MODE);
    cfgManager.addMode(DEBUGGING_MODE);
    cfgManager.printConfig(); // Display current configuration

    // Save to file
    if (cfgManager.saveConfig("config.txt")) {
        std::cout << "Configuration saved successfully." << std::endl;
    } else {
        std::cout << "Failed to save configuration." << std::endl;
    }

    // Reset configuration
    cfgManager.removeMode(POWER_SAVING_MODE);
    cfgManager.removeMode(DEBUGGING_MODE);
    cfgManager.printConfig(); // Display current configuration after reset

    // Load configuration from file
    if (cfgManager.loadConfig("config.txt")) {
        std::cout << "Configuration loaded successfully." << std::endl;
    } else {
        std::cout << "Failed to load configuration." << std::endl;
    }

    cfgManager.printConfig(); // Display loaded configuration

    return 0;
}

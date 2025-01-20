#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// Define operational modes as constants
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
    bool saveToFile(const std::string& filePath) {
        std::ofstream outFile(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing: " << filePath << std::endl;
            return false;
        }

        outFile.write(reinterpret_cast<const char*>(&config), sizeof(config));
        outFile.close();

        std::cout << "Configuration saved to " << filePath << std::endl;
        return true;
    }

    // Load configuration from a file
    bool loadFromFile(const std::string& filePath) {
        std::ifstream inFile(filePath, std::ios::binary | std::ios::in);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file for reading: " << filePath << std::endl;
            return false;
        }

        inFile.read(reinterpret_cast<char*>(&config), sizeof(config));
        inFile.close();

        std::cout << "Configuration loaded from " << filePath << std::endl;
        return true;
    }
};

// Example usage
int main() {
    ConfigManager cfgManager;

    // Add modes
    cfgManager.addMode(POWER_SAVING_MODE);
    cfgManager.addMode(DEBUGGING_MODE);
    cfgManager.printConfig(); // Should display "Active Configurations: Power Saving Debugging"

    // Save configuration to a file
    cfgManager.saveToFile("config.bin");

    // Reset the configuration manager
    cfgManager.config = 0;
    cfgManager.printConfig(); // Should display "No active modes."

    // Load configuration from the file
    cfgManager.loadFromFile("config.bin");
    cfgManager.printConfig(); // Should display "Active Configurations: Power Saving Debugging"

    return 0;
}

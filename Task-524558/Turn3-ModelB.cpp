#include <iostream>
#include <cstdint>
#include <map>

class ConfigManager {
private:
    static const size_t MAX_MODES = 32; // Assuming modes fit in a 32-bit unsigned integer
    uint32_t config; // Bitmask for modes
    std::map<std::string, uint32_t> modeBits; // Mapping from mode names to their corresponding bit values

public:
    // Add a new mode dynamically
    bool addMode(const std::string& modeName) {
        if (modeBits.size() == MAX_MODES) {
            std::cout << "Error: Maximum number of modes reached." << std::endl;
            return false;
        }

        uint32_t newModeBit = 1U << modeBits.size(); // Assign the least significant bit for the new mode
        modeBits[modeName] = newModeBit;
        std::cout << "Mode '" << modeName << "' added with bit value: 0x" << std::hex << newModeBit << std::dec << std::endl;
        return true;
    }

    // Set a mode using its name
    void setMode(const std::string& modeName) {
        if (modeBits.count(modeName) == 0) {
            std::cout << "Error: Mode '" << modeName << "' not found." << std::endl;
            return;
        }
        config |= modeBits[modeName];
    }

    // Clear a mode using its name
    void clearMode(const std::string& modeName) {
        if (modeBits.count(modeName) == 0) {
            std::cout << "Error: Mode '" << modeName << "' not found." << std::endl;
            return;
        }
        config &= ~modeBits[modeName];
    }

    // Toggle a mode using its name
    void toggleMode(const std::string& modeName) {
        if (modeBits.count(modeName) == 0) {
            std::cout << "Error: Mode '" << modeName << "' not found." << std::endl;
            return;
        }
        config ^= modeBits[modeName];
    }

    // Check if a mode is set using its name
    bool isModeSet(const std::string& modeName) const {
        if (modeBits.count(modeName) == 0) {
            std::cout << "Error: Mode '" << modeName << "' not found." << std::endl;
            return false;
        }
        return (config & modeBits[modeName]) != 0;
    }

    // Print the current configuration
    void printConfig() const {
        for (const auto& modeBit : modeBits) {
            const std::string& modeName = modeBit.first;
            uint32_t modeValue = modeBit.second;
            if (config & modeValue) {
                std::cout << "Mode '" << modeName << "' is set." << std::endl;
            }
        }
        std::cout << "Current Config: 0x" << std::hex << config << std::dec << std::endl;
    }
};

// Example usage
int main() {
    ConfigManager cfgManager;

    // Dynamically add modes
    cfgManager.addMode("Power Saving");
    cfgManager.addMode("High Performance");
    cfgManager.addMode("Debugging");
    cfgManager.addMode("Low Latency");

    // Set modes
    cfgManager.setMode("Power Saving");
    cfgManager.setMode("Debugging");
    cfgManager.setMode("Low Latency");

    // Toggle a mode
    cfgManager.toggleMode("High Performance");

    // Check modes
    std::cout << "Is Debugging mode set? " << (cfgManager.isModeSet("Debugging") ? "Yes" : "No") << std::endl;
    std::cout << "Is High Performance mode set? " << (cfgManager.isModeSet("High Performance") ? "Yes" : "No") << std::endl;

    // Print configuration
    cfgManager.printConfig();

    return 0;
}

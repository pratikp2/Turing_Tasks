#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

const uint8_t POWER_SAVING_MODE = 0x01;   // 0000 0001
const uint8_t HIGH_PERFORMANCE_MODE = 0x02; // 0000 0010
const uint8_t DEBUGGING_MODE = 0x04;        // 0000 0100
const uint8_t LOW_LATENCY_MODE = 0x08;     // 0000 1000

class ConfigManager {
private:
    uint8_t config;
    std::vector<std::pair<uint8_t, std::string>> modeNames = {
        { POWER_SAVING_MODE, "Power Saving" },
        { HIGH_PERFORMANCE_MODE, "High Performance" },
        { DEBUGGING_MODE, "Debugging" },
        { LOW_LATENCY_MODE, "Low Latency" }
    };

public:
    ConfigManager() : config(0) {}

    void addMode(uint8_t mode) {
        config |= mode;
    }

    void removeMode(uint8_t mode) {
        config &= ~mode;
    }

    bool isModeSet(uint8_t mode) const {
        return (config & mode) != 0;
    }

    std::string getCurrentConfigurationString() const {
        std::string log;
        for (const auto& mode : modeNames) {
            if (isModeSet(mode.first)) {
                if (!log.empty()) log += ", ";
                log += mode.second;
            }
        }
        return log;
    }

    void printConfig() const {
        std::cout << "Current Configuration: " << getCurrentConfigurationString() << std::endl;
    }

    void logConfig() const {
        std::cout << "System Configuration Log: " << getCurrentConfigurationString() << std::endl;
    }
};

int main() {
    ConfigManager cfgManager;

    cfgManager.addMode(POWER_SAVING_MODE);
    cfgManager.addMode(DEBUGGING_MODE);
    cfgManager.addMode(LOW_LATENCY_MODE);

    cfgManager.printConfig();
    cfgManager.logConfig();

    cfgManager.removeMode(DEBUGGING_MODE);
    cfgManager.addMode(HIGH_PERFORMANCE_MODE);

    cfgManager.printConfig();
    cfgManager.logConfig();

    return 0;
}

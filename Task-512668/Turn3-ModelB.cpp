#include <iostream>

const int TEMP_HIGH_FLAG = 0b001;   // High temperature flag (1)
const int TEMP_LOW_FLAG  = 0b010;   // Low temperature flag (2)
const int HUMIDITY_HIGH_FLAG = 0b100; // High humidity flag (4)

int checkEnvironmentalConditions(int conditions, int tempThresholdHigh, int tempThresholdLow, int humidityThresholdHigh) {
    int tempFlag = 0;
    int humidityFlag = 0;

    // Simulate temperature reading
    int tempReading = 25; // Replace this with actual temperature reading

    // Simulate humidity reading
    int humidityReading = 60; // Replace this with actual humidity reading

    if (tempReading >= tempThresholdHigh) {
        tempFlag |= TEMP_HIGH_FLAG;
    } else if (tempReading <= tempThresholdLow) {
        tempFlag |= TEMP_LOW_FLAG;
    }

    if (humidityReading >= humidityThresholdHigh) {
        humidityFlag |= HUMIDITY_HIGH_FLAG;
    }

    conditions = tempFlag | humidityFlag;

    return conditions;
}

void printConditions(int conditions) {
    if (conditions & TEMP_HIGH_FLAG) {
        std::cout << "High Temperature detected." << std::endl;
    }
    if (conditions & TEMP_LOW_FLAG) {
        std::cout << "Low Temperature detected." << std::endl;
    }
    if (conditions & HUMIDITY_HIGH_FLAG) {
        std::cout << "High Humidity detected." << std::endl;
    }
}

int main() {
    int conditions = 0;
    const int tempThresholdHigh = 30;
    const int tempThresholdLow = 15;
    const int humidityThresholdHigh = 70;

    conditions = checkEnvironmentalConditions(conditions, tempThresholdHigh, tempThresholdLow, humidityThresholdHigh);

    std::cout << "Current Environmental Conditions: ";
    printConditions(conditions);

    // Let's see how it behaves under extreme conditions
    std::cout << "\nExtreme Conditions Simulation: ";

    // Simulate extreme temperature
    conditions = checkEnvironmentalConditions(conditions, tempThresholdHigh, tempThresholdLow, humidityThresholdHigh);
    printConditions(conditions);

    return 0;
}

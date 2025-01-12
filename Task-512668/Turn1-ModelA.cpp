#include <iostream>
#include <string>

const int TEMP_HIGH = 0b001; // 1: High Temperature
const int HUMIDITY_LOW = 0b010; // 2: Low Humidity
const int AIR_QUALITY_BAD = 0b100; // 4: Bad Air Quality

void checkEnvironmentalConditions(int conditions) {
    // Check conditions using bitwise operations
    if (conditions & TEMP_HIGH) {
        std::cout << "Warning: High Temperature detected!" << std::endl;
    }
    if (conditions & HUMIDITY_LOW) {
        std::cout << "Warning: Low Humidity detected!" << std::endl;
    }
    if (conditions & AIR_QUALITY_BAD) {
        std::cout << "Warning: Poor Air Quality detected!" << std::endl;
    }
}

void checkEnvironmentalConditionsVerbose(int conditions) {
    // Check conditions using simple boolean checks instead of bitwise
    bool highTemp = (conditions & TEMP_HIGH) != 0;
    bool lowHumidity = (conditions & HUMIDITY_LOW) != 0;
    bool badAirQuality = (conditions & AIR_QUALITY_BAD) != 0;

    if (highTemp) {
        std::cout << "Warning: High Temperature detected!" << std::endl;
    }
    if (lowHumidity) {
        std::cout << "Warning: Low Humidity detected!" << std::endl;
    }
    if (badAirQuality) {
        std::cout << "Warning: Poor Air Quality detected!" << std::endl;
    }
}

int main() {
    int environmentalConditions = TEMP_HIGH | HUMIDITY_LOW; // Simulating conditions: High Temp and Low Humidity

    std::cout << "Using Bitwise Operations:" << std::endl;
    checkEnvironmentalConditions(environmentalConditions);

    std::cout << "\nUsing Verbose Checks:" << std::endl;
    checkEnvironmentalConditionsVerbose(environmentalConditions);

    return 0;
}

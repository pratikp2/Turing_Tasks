#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <vector> // For error correction history

const int TEMP_HIGH = 0b001;      // Flag for high temperature
const int HUMIDITY_LOW = 0b010;   // Flag for low humidity
const int ERROR_BIT = 0b100;       // Error detection flag

// Simulated sensor readings
int getTemperatureReading() {
    return (rand() % 100);
}

int getHumidityReading() {
    return (rand() % 100);
}

int checkEnvironmentalConditions(int temperature, int humidity) {
    const int TEMP_THRESHOLD = 75;
    const int HUMIDITY_THRESHOLD = 30;

    int flags = 0;

    // Calculate conditions
    if (temperature > TEMP_THRESHOLD) {
        flags |= TEMP_HIGH;
    }
    if (humidity < HUMIDITY_THRESHOLD) {
        flags |= HUMIDITY_LOW;
    }

    // Check for noise using error correction
    flags |= correctError(flags); // Use bitwise OR to incorporate error correction result

    return flags;
}

int correctError(int flags) {
    static std::vector<int> errorHistory = {0, 0, 0}; // Redundant history for last 3 readings
    int error = detectError(errorHistory);

    if (error > 0) {
        errorHistory.push_back(error); // Add current error state
        if (errorHistory.size() > 3) {
            errorHistory.erase(errorHistory.begin()); // Remove oldest reading
        }
    }

    return ERROR_BIT * error; // Set ERROR_BIT only if error is detected
}

int detectError(const std::vector<int>& history) {
    int errorCount = 0;

    // Simulated detection of inconsistency (simple threshold-based)
    for (int reading : history) {
        if (reading > 0) {
            errorCount++;
        }
        if (errorCount > 1) {
            return 1; // More than one error flag set indicates inconsistency
        }
    }

    return 0;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 10; ++i) {
        int temperature = getTemperatureReading();
        int humidity = getHumidityReading();

        std::cout << "Reading " << (i + 1) << ": Temperature = " << temperature 
                  << "°C, Humidity = " << humidity << "%" << std::endl;

        int conditionFlags = checkEnvironmentalConditions(temperature, humidity);

        if (conditionFlags & TEMP_HIGH) {
            std::cout << "Warning: High Temperature detected!" << std::endl;
        }
        if (conditionFlags & HUMIDITY_LOW) {
            std::cout << "Warning: Low Humidity detected!" << std::endl;
        }
        if (conditionFlags & ERROR_BIT) {
            std::cout << "Sensor Error Detected!" << std::endl;
        }
        std::cout << (conditionFlags & (TEMP_HIGH | HUMIDITY_LOW) == 0 ? "Conditions are normal." : "") << std::endl;
    }

    return 0;
}

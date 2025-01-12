#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <vector>
#include <algorithm> // for sort

const int TEMP_HIGH = 0b001;         // Flag for high temperature
const int HUMIDITY_LOW = 0b010;      // Flag for low humidity

// Simulated sensor readings
int getTemperatureReading() {
    // Simulating temperature reading with random values
    // Random temperature between 0 and 99
    return (rand() % 100);
}

int getHumidityReading() {
    // Simulating humidity reading with random values
    // Random humidity between 0 and 99
    return (rand() % 100);
}

// Helper function to get median value from sensor readings
int getMedian(std::vector<int> readings) {
    std::sort(readings.begin(), readings.end()); // Sorting to find median
    return readings[readings.size() / 2];
}

// Function to check environmental conditions using bitwise operations
int checkEnvironmentalConditions(int temperature, int humidity) {
    int flags = 0;

    // Define thresholds
    const int TEMP_THRESHOLD = 75;      // High temperature threshold
    const int HUMIDITY_THRESHOLD = 30;   // Low humidity threshold

    // Set flags based on conditions
    if (temperature > TEMP_THRESHOLD) {
        flags |= TEMP_HIGH; // Set high temperature flag
    }
    if (humidity < HUMIDITY_THRESHOLD) {
        flags |= HUMIDITY_LOW; // Set low humidity flag
    }

    return flags;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness

    // Simulate readings for redundancy
    for (int i = 0; i < 10; ++i) {
        // Gather readings from multiple sensors (redundancy)
        std::vector<int> temperatureReadings(3);
        std::vector<int> humidityReadings(3);

        for (int j = 0; j < 3; ++j) {
            temperatureReadings[j] = getTemperatureReading();
            humidityReadings[j] = getHumidityReading();
        }

        // Get median to mitigate outliers
        int temperature = getMedian(temperatureReadings);
        int humidity = getMedian(humidityReadings);

        std::cout << "Reading " << (i + 1) << ": Temperature = " << temperature 
                  << "°C, Humidity = " << humidity << "%" << std::endl;

        int conditionFlags = checkEnvironmentalConditions(temperature, humidity);

        // Check flags and print warnings
        if (conditionFlags & TEMP_HIGH) {
            std::cout << "Warning: High Temperature detected!" << std::endl;
        }
        if (conditionFlags & HUMIDITY_LOW) {
            std::cout << "Warning: Low Humidity detected!" << std::endl;
        }

        std::cout << (conditionFlags == 0 ? "Conditions are normal." : "") << std::endl;

        // Introduce extreme conditions simulation
        if (temperature > 90 || humidity < 15) {
            std::cout << "Extreme conditions detected!" << std::endl;
        }
    }

    return 0;
}

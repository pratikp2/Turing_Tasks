#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

const int TEMP_HIGH = 0b001;         // Flag for high temperature
const int HUMIDITY_LOW = 0b010;      // Flag for low humidity

int getTemperatureReading() {
    return (rand() % 100); // Simulating temperature readings (0-99)
}

int getHumidityReading() {
    return (rand() % 100); // Simulating humidity readings (0-99)
}

int getMedian(std::vector<int> readings) {
    std::sort(readings.begin(), readings.end());
    return readings[readings.size() / 2];
}

int checkEnvironmentalConditions(int temperature, int humidity) {
    int flags = 0;
    const int TEMP_THRESHOLD = 75;      // High temperature threshold
    const int HUMIDITY_THRESHOLD = 30;   // Low humidity threshold

    if (temperature > TEMP_THRESHOLD) {
        flags |= TEMP_HIGH; // Set high temperature flag
    }
    if (humidity < HUMIDITY_THRESHOLD) {
        flags |= HUMIDITY_LOW; // Set low humidity flag
    }
    return flags;
}

void simulateReadings(int numReadings) {
    std::vector<int> temperatureReadings(3);
    std::vector<int> humidityReadings(3);

    for (int i = 0; i < numReadings; ++i) {
        // Collect readings
        for (int j = 0; j < 3; ++j) {
            temperatureReadings[j] = getTemperatureReading();
            humidityReadings[j] = getHumidityReading();
        }

        // Time the decision-making process
        auto startTime = std::chrono::high_resolution_clock::now();

        int temperature = getMedian(temperatureReadings);
        int humidity = getMedian(humidityReadings);
        int conditionFlags = checkEnvironmentalConditions(temperature, humidity);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;

        // Print results
        std::cout << "Reading " << (i + 1) << ": Temperature = " << temperature 
                  << "°C, Humidity = " << humidity << "%, Duration = " 
                  << duration.count() << " ms" << std::endl;

        // Check flags and print warnings
        if (conditionFlags & TEMP_HIGH) {
            std::cout << "Warning: High Temperature detected!" << std::endl;
        }
        if (conditionFlags & HUMIDITY_LOW) {
            std::cout << "Warning: Low Humidity detected!" << std::endl;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    const int numReadings = 10; // Change this for more readings

    simulateReadings(numReadings);

    return 0;
}

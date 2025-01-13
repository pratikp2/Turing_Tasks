#include <iostream>
#include <cstdint>

class EnvironmentalData {
private:
    uint32_t data; // Using uint32_t to accommodate more bits for sensor data

    // Constants for bit positions and number of bits for each sensor
    static const int TEMP_BITS = 8;     
    static const int HUMIDITY_BITS = 8; 
    static const int AQ_BITS = 20;      

    static const int TEMP_OFFSET = 0;      
    static const int HUMIDITY_OFFSET = TEMP_OFFSET + TEMP_BITS; 
    static const int AQ_OFFSET = HUMIDITY_OFFSET + HUMIDITY_BITS; 

public:
    EnvironmentalData() : data(0) {}

    // Setters
    void setTemperature(int temperature) {
        data &= ~((1 << TEMP_BITS) - 1); // Clear the temperature bits
        data |= (temperature & ((1 << TEMP_BITS) - 1)); // Set new temperature value
    }

    void setHumidity(int humidity) {
        data &= ~(((1 << HUMIDITY_BITS) - 1) << HUMIDITY_OFFSET); // Clear the humidity bits
        data |= (humidity & ((1 << HUMIDITY_BITS) - 1)) << HUMIDITY_OFFSET; // Set new humidity value
    }

    void setAirQuality(int airQuality) {
        data &= ~(((1 << AQ_BITS) - 1) << AQ_OFFSET); // Clear the air quality bits
        data |= (airQuality & ((1 << AQ_BITS) - 1)) << AQ_OFFSET; // Set new air quality value
    }

    // Getters
    int getTemperature() const {
        return data & ((1 << TEMP_BITS) - 1); // Get temperature
    }

    int getHumidity() const {
        return (data >> HUMIDITY_OFFSET) & ((1 << HUMIDITY_BITS) - 1); // Get humidity
    }

    int getAirQuality() const {
        return (data >> AQ_OFFSET) & ((1 << AQ_BITS) - 1); // Get air quality
    }

    // Method to check if any reading exceeds specified thresholds
    void checkThresholds(int tempThreshold, int humidityThreshold, int aqThreshold) {
        // Using bitwise operations to check thresholds
        bool tempExceeds = (getTemperature() > tempThreshold); // Check temperature threshold
        bool humidityExceeds = (getHumidity() > humidityThreshold); // Check humidity threshold
        bool aqExceeds = (getAirQuality() > aqThreshold); // Check air quality threshold

        // Display results
        if (tempExceeds) {
            std::cout << "Warning: Temperature exceeds threshold!" << std::endl;
        }
        if (humidityExceeds) {
            std::cout << "Warning: Humidity exceeds threshold!" << std::endl;
        }
        if (aqExceeds) {
            std::cout << "Warning: Air Quality Index exceeds threshold!" << std::endl;
        }
        if (!tempExceeds && !humidityExceeds && !aqExceeds) {
            std::cout << "All readings are within safe thresholds." << std::endl;
        }
    }
};

int main() {
    EnvironmentalData envData;

    // Simulating setting sensor values
    envData.setTemperature(30);      // Temperature set to 30 °C
    envData.setHumidity(75);         // Humidity set to 75%
    envData.setAirQuality(600000);   // Air Quality Index set to 600,000

    // Specify thresholds for alerts
    int tempThreshold = 28;          // Threshold for temperature
    int humidityThreshold = 70;      // Threshold for humidity
    int aqThreshold = 500000;        // Threshold for Air Quality Index

    // Check if any readings exceed the defined thresholds
    envData.checkThresholds(tempThreshold, humidityThreshold, aqThreshold);

    return 0;
}

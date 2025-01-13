#include <iostream>
#include <bitset>
#include <string>

class EnvironmentalData {
private:
    int data;  // Using an integer to store the combined sensor data

    // Constants to define bit positions and number of bits for each sensor
    static const int TEMP_BITS = 8;     // Temperature in 0-255 degrees
    static const int HUMIDITY_BITS = 8; // Humidity in 0-255 percent
    static const int AQ_BITS = 16;      // Air Quality Index (0-65535)

    static const int TEMP_OFFSET = 0;   // Starting bit position for temperature
    static const int HUMIDITY_OFFSET = TEMP_OFFSET + TEMP_BITS; // Humidity
    static const int AQ_OFFSET = HUMIDITY_OFFSET + HUMIDITY_BITS; // Air Quality

public:
    EnvironmentalData() : data(0) {}

    // Method to set temperature, humidity and air quality values
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

    // Method to get the current sensor values
    int getTemperature() const {
        return data & ((1 << TEMP_BITS) - 1); // Get temperature
    }

    int getHumidity() const {
        return (data >> HUMIDITY_OFFSET) & ((1 << HUMIDITY_BITS) - 1); // Get humidity
    }

    int getAirQuality() const {
        return (data >> AQ_OFFSET) & ((1 << AQ_BITS) - 1); // Get air quality
    }

    void displayData() const {
        std::cout << "Temperature: " << getTemperature() << " °C" << std::endl;
        std::cout << "Humidity: " << getHumidity() << " %" << std::endl;
        std::cout << "Air Quality Index: " << getAirQuality() << std::endl;
    }
};

int main() {
    EnvironmentalData envData;

    // Simulating setting sensor values
    envData.setTemperature(25);
    envData.setHumidity(60);
    envData.setAirQuality(300);

    // Displaying sensor values
    envData.displayData();

    return 0;
}

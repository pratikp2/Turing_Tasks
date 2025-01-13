#include <iostream>
#include <cstdint>

class EnvironmentalData {
private:
    uint32_t data;

    static const int MAX_TEMP_BITS = 8;      // Maximum resolution for temperature: 0-255
    static const int MAX_HUMIDITY_BITS = 8;  // Maximum resolution for humidity: 0-255
    static const int MAX_AQ_BITS = 20;       // Maximum resolution for air quality: 0-1048575

    static const int TEMP_OFFSET = 0;
    static const int HUMIDITY_OFFSET = TEMP_OFFSET + MAX_TEMP_BITS;
    static const int AQ_OFFSET = HUMIDITY_OFFSET + MAX_HUMIDITY_BITS;

    // Dynamic bit allocations
    int currentTempBits;
    int currentHumidityBits;
    int currentAqBits;

public:
    EnvironmentalData()
        : data(0),
          currentTempBits(MAX_TEMP_BITS),
          currentHumidityBits(MAX_HUMIDITY_BITS),
          currentAqBits(MAX_AQ_BITS) {
    }

    // Function to adjust the resolution of sensors dynamically
    void adjustResolution(int tempBits, int humidityBits, int aqBits) {
        // Validate resolution changes
        if (tempBits < 0 || tempBits > MAX_TEMP_BITS) {
            std::cerr << "Temperature resolution must be between 0 and " << MAX_TEMP_BITS << std::endl;
            return;
        }
        if (humidityBits < 0 || humidityBits > MAX_HUMIDITY_BITS) {
            std::cerr << "Humidity resolution must be between 0 and " << MAX_HUMIDITY_BITS << std::endl;
            return;
        }
        if (aqBits < 0 || aqBits > MAX_AQ_BITS) {
            std::cerr << "Air quality resolution must be between 0 and " << MAX_AQ_BITS << std::endl;
            return;
        }

        // Update current resolutions
        currentTempBits = tempBits;
        currentHumidityBits = humidityBits;
        currentAqBits = aqBits;

        // Clear the data in the new format
        data = 0;
        data &= ~(((1 << currentAqBits) - 1) << AQ_OFFSET);
        data &= ~(((1 << currentHumidityBits) - 1) << HUMIDITY_OFFSET);
        data &= ~((1 << currentTempBits) - 1);
    }

    // Setters with dynamic resolution scaling
    void setTemperature(int temperature) {
        // Scale the temperature value to the current resolution
        int scaledTemperature = temperature >> (MAX_TEMP_BITS - currentTempBits);

        // Set the temperature value using bitwise operations
        data &= ~((1 << currentTempBits) - 1);
        data |= (scaledTemperature & ((1 << currentTempBits) - 1));
    }

    void setHumidity(int humidity) {
        int scaledHumidity = humidity >> (MAX_HUMIDITY_BITS - currentHumidityBits);

        data &= ~(((1 << currentHumidityBits) - 1) << HUMIDITY_OFFSET);
        data |= (scaledHumidity & ((1 << currentHumidityBits) - 1)) << HUMIDITY_OFFSET;
    }

    void setAirQuality(int airQuality) {
        int scaledAirQuality = airQuality >> (MAX_AQ_BITS - currentAqBits);

        data &= ~(((1 << currentAqBits) - 1) << AQ_OFFSET);
        data |= (scaledAirQuality & ((1 << currentAqBits) - 1)) << AQ_OFFSET;
    }

    // Getters with dynamic resolution scaling
    int getTemperature() const {
        // Scale the temperature value back to maximum resolution
        int unscaledTemperature = (data & ((1 << currentTempBits) - 1)) << (MAX_TEMP_BITS - currentTempBits);
        return unscaledTemperature;
    }

    int getHumidity() const {
        int unscaledHumidity = ((data >> HUMIDITY_OFFSET) & ((1 << currentHumidityBits) - 1))
                              << (MAX_HUMIDITY_BITS - currentHumidityBits);
        return unscaledHumidity;
    }

    int getAirQuality() const {
        int unscaledAirQuality = ((data >> AQ_OFFSET) & ((1 << currentAqBits) - 1))
                                << (MAX_AQ_BITS - currentAqBits);
        return unscaledAirQuality;
    }

    // Method to check if any reading exceeds specified thresholds
    void checkThresholds(int tempThreshold, int humidityThreshold, int aqThreshold) {
        bool tempExceeds = (getTemperature() > tempThreshold);
        bool humidityExceeds = (getHumidity() > humidityThreshold);
        bool aqExceeds = (getAirQuality() > aqThreshold);

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

    // Simulating setting sensor values with initial maximum resolutions
    envData.setTemperature(230); // Scaled to 230 / 255 * 255 = 230
    envData.setHumidity(175); // Scaled to 175 / 255 * 255 = 175
    envData.setAirQuality(800000); // Scaled to 800000 / 1048575 * 1048575 = 800000

    envData.checkThresholds(250, 200, 700000);

    // Adjusting the resolution to lower precision
    envData.adjustResolution(4, 4, 10);

    // Set new values with lower resolution
    envData.setTemperature(230); // Scaled to 230 / 15 * 15 = 240 (rounded up)
    envData.setHumidity(175); // Scaled to 175 / 15 * 15 = 180 (rounded up)
    envData.setAirQuality(800000); // Scaled to 800000 / 1023 * 1023 = 800000

    envData.checkThresholds(250, 200, 700000);

    return 0;
}

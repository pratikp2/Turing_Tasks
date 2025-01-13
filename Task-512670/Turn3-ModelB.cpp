#include <iostream>
#include <bitset>

class EnvironmentalData {
private:
    uint32_t data;

    static const int TEMP_BITS = 8;
    static const int HUMIDITY_BITS = 8;
    static const int AQ_BITS = 20;

    static const int TEMP_OFFSET = 0;
    static const int HUMIDITY_OFFSET = TEMP_OFFSET + TEMP_BITS;
    static const int AQ_OFFSET = HUMIDITY_OFFSET + HUMIDITY_BITS;

public:
    EnvironmentalData() : data(0) {}
    // Setter and getter methods (removed for brevity)

    // Function to check if any sensor value exceeds the given thresholds
    bool exceedsThresholds(int tempThreshold, int humidityThreshold, int aqThreshold) const {
        uint32_t tempMask = ((1 << TEMP_BITS) - 1);  // Mask for temperature bits
        uint32_t humidityMask = ((1 << HUMIDITY_BITS) - 1) << HUMIDITY_OFFSET; // Mask for humidity bits
        uint32_t aqMask = ((1 << AQ_BITS) - 1) << AQ_OFFSET;  // Mask for AQ bits
 
        // Extract the sensor values
        int temp = (data & tempMask);
        int humidity = (data & humidityMask) >> HUMIDITY_OFFSET;
        int aq = (data & aqMask) >> AQ_OFFSET;
        
        // Check if any value exceeds the threshold using bitwise operations
        return temp > tempThreshold   || 
               humidity > humidityThreshold ||
               aq > aqThreshold;
    }
};

int main() {
    EnvironmentalData envData;
 
    // Simulating setting sensor values
    envData.setTemperature(95);
    envData.setHumidity(60);
    envData.setAirQuality(800);
 
    int tempThreshold = 80;
    int humidityThreshold = 70;
    int aqThreshold = 500;
 
    bool anyThresholdExceeded = envData.exceedsThresholds(tempThreshold, humidityThreshold, aqThreshold);
 
    std::cout << "Sensor Threshold Check:" << std::endl;
    if (anyThresholdExceeded) {
        std::cout << "One or more sensors exceed their thresholds!" << std::endl;
    } else {
        std::cout << "All sensors are within their thresholds." << std::endl;
    }
 
    envData.displayData();
 
    return 0;
}

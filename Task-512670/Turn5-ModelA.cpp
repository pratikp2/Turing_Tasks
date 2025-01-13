#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

class EnvironmentalData {
private:
    uint32_t data; // Using uint32_t to accommodate multiple sensor data

    // Constants for bit positions for each sensor
    static const int BASE_TEMP_BITS = 8;     // Base resolution for temperature
    static const int BASE_HUMIDITY_BITS = 8; // Base resolution for humidity
    static const int BASE_AQ_BITS = 16;       // Base resolution for Air Quality

    // Bit offsets for each sensor
    static const int TEMP_OFFSET = 0;      
    static const int HUMIDITY_OFFSET = TEMP_OFFSET + BASE_TEMP_BITS; 
    static const int AQ_OFFSET = HUMIDITY_OFFSET + BASE_HUMIDITY_BITS; 

public:
    EnvironmentalData() : data(0) {}

    // Setters with dynamic resolution adjustment
    void setTemperature(uint32_t temperature, int resolution) {
        int bits = BASE_TEMP_BITS + resolution; // Adjust bits dynamically
        int max_value = (1 << bits) - 1; // Maximum value based on bit size
        
        // Scale temperature value to fit the increased resolution
        temperature = std::min(temperature, static_cast<uint32_t>(max_value));
        
        // Clear current temperature bits and set new scaled value
        data &= ~((1 << bits) - 1); // Clear the temperature bits
        data |= (temperature & max_value); // Set new temperature value
    }

    void setHumidity(uint32_t humidity, int resolution) {
        int bits = BASE_HUMIDITY_BITS + resolution; // Adjust bits dynamically
        int max_value = (1 << bits) - 1; // Maximum value based on bit size
        
        // Scale humidity value to fit the increased resolution
        humidity = std::min(humidity, static_cast<uint32_t>(max_value));

        // Clear current humidity bits and set new scaled value
        data &= ~(((1 << bits) - 1) << HUMIDITY_OFFSET); // Clear humidity bits
        data |= (humidity & max_value) << HUMIDITY_OFFSET; // Set new humidity value
    }

    void setAirQuality(uint32_t airQuality, int resolution) {
        int bits = BASE_AQ_BITS + resolution; // Adjust bits dynamically
        int max_value = (1 << bits) - 1; // Maximum value based on bit size
        
        // Scale air quality value to fit the increased resolution
        airQuality = std::min(airQuality, static_cast<uint32_t>(max_value));

        // Clear current air quality bits and set new scaled value
        data &= ~(((uint32_t)(1 << bits) - 1) << AQ_OFFSET); // Clear AQ bits
        data |= (airQuality & max_value) << AQ_OFFSET; // Set new air quality value
    }

    // Getters with appropriate bit manipulations
    int getTemperature() const {
        return data & ((1 << (BASE_TEMP_BITS + 1)) - 1); // Get temperature
    }

    int getHumidity() const {
        return (data >> HUMIDITY_OFFSET) & ((1 << (BASE_HUMIDITY_BITS + 1)) - 1); // Get humidity
    }

    int getAirQuality() const {
        return (data >> AQ_OFFSET) & ((1 << (BASE_AQ_BITS + 1)) - 1); // Get air quality
    }

    // Display current sensor readings
    void displayData() const {
        std::cout << "Temperature: " << getTemperature() << " °C" << std::endl;
        std::cout << "Humidity: " << getHumidity() << " %" << std::endl;
        std::cout << "Air Quality Index: " << getAirQuality() << std::endl;
    }
};

class Sensor {
public:
    virtual void readData(EnvironmentalData& envData) = 0; // Pure virtual function
};

class TemperatureSensor : public Sensor {
public:
    void readData(EnvironmentalData& envData) override {
        // Simulating temperature reading in the range of 0 to 50 degrees Celsius
        int temp = rand() % 51; // Random value between 0 and 50
        envData.setTemperature(temp, 2); // Setting with dynamic resolution
    }
};

class HumiditySensor : public Sensor {
public:
    void readData(EnvironmentalData& envData) override {
        // Simulating humidity reading in the range of 0 to 100 percent
        int humidity = rand() % 101; // Random value between 0 and 100
        envData.setHumidity(humidity, 1); // Setting with dynamic resolution
    }
};

class AirQualitySensor : public Sensor {
public:
    void readData(EnvironmentalData& envData) override {
        // Simulating air quality index reading in a range of 0 to 1000
        int airQuality = rand() % 1001; // Random value between 0 and 1000
        envData.setAirQuality(airQuality, 4); // Setting with dynamic resolution
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    EnvironmentalData envData;

    // List of different sensors to simulate
    std::vector<Sensor*> sensors;
    sensors.push_back(new TemperatureSensor());
    sensors.push_back(new HumiditySensor());
    sensors.push_back(new AirQualitySensor());

    // Simulating data gathering over time
    for (int i = 0; i < 5; i++) { // Simulate 5 readings
        std::cout << "Reading " << (i + 1) << ":\n";
        
        for (Sensor* sensor : sensors) {
            sensor->readData(envData); // Each sensor reads data
        }
        
        // Display sensor data after each reading
        envData.displayData();
        std::cout << "-------------------------\n";
        
        // Sleep for a bit (simulate time passing)
        // std::this_thread::sleep_for(std::chrono::seconds(1)); // Uncomment when using C++11 or later
    }

    // Clean up
    for (Sensor* sensor : sensors) {
        delete sensor; // Clean up dynamically allocated memory
    }
    
    return 0;
}

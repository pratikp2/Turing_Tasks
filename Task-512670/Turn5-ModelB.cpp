#include <iostream>
#include <cstdint>
#include <cmath>
#include <cstdlib> // For rand() and srand() functions
#include <ctime>   // For seeding rand()
#include <thread>  // For simulating concurrent data collection

class EnvironmentalData {
    // ... (The same code as before)
};

// Function to simulate sensor data collection
void simulateSensorDataCollection(EnvironmentalData& envData, int sensorId) {
    while (true) {
        // Generate random data for each sensor
        uint32_t temperature = std::rand() % 256;
        uint32_t humidity = std::rand() % 256;
        uint32_t airQuality = std::rand() % 100000;

        // Adjust resolution based on sensor type and data conditions
        int tempResolution = sensorId == 0 ? (temperature > 200 ? 2 : 0) : 0;
        int humidityResolution = sensorId == 1 ? (humidity > 90 ? 1 : 0) : 0;
        int airQualityResolution = sensorId == 2 ? (airQuality > 50000 ? 4 : 0) : 0;

        // Set the sensor data with dynamic resolution
        envData.setTemperature(temperature, tempResolution);
        envData.setHumidity(humidity, humidityResolution);
        envData.setAirQuality(airQuality, airQualityResolution);

        // Simulate delay between data readings
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed rand() for reproducibility

    EnvironmentalData envData;

    // Create multiple threads to simulate concurrent data collection from different sensors
    std::thread sensorThread1(simulateSensorDataCollection, std::ref(envData), 0); // Sensor 1: Temperature
    std::thread sensorThread2(simulateSensorDataCollection, std::ref(envData), 1); // Sensor 2: Humidity
    std::thread sensorThread3(simulateSensorDataCollection, std::ref(envData), 2); // Sensor 3: Air Quality

    // Main loop to display sensor data periodically
    while (true) {
        std::cout << "Current Sensor Readings:" << std::endl;
        envData.displayData();
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Sleep for 5 seconds before displaying again
    }

    return 0;
}

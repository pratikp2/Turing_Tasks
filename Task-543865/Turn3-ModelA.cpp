#include <iostream>
#include <string>
#include <array>
#include <chrono>

// Define an enumeration for the sensor types
enum class SensorType {
    LIDAR,
    RADAR,
    CAMERA,
    UNKNOWN
};

// Struct for Sensor Metadata
struct SensorMetadata {
    std::string name;
    double processingDelay; // in milliseconds

    constexpr SensorMetadata(const std::string& n, double delay)
        : name(n), processingDelay(delay) {}
};

// Base struct for Sensor
struct Sensor {
    SensorType type;
    SensorMetadata metadata;

    Sensor(SensorType t, const SensorMetadata& m) : type(t), metadata(m) {}

    virtual void processData() = 0; // Pure virtual function for processing data
};

// LIDAR sensor
struct LidarSensor : public Sensor {
    LidarSensor()
        : Sensor(SensorType::LIDAR, SensorMetadata("LIDAR", 5.0)) {}

    void processData() override {
        std::cout << "Processing LIDAR data with delay: " << metadata.processingDelay << " ms\n";
        // Simulate processing delay
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));
    }
};

// RADAR sensor
struct RadarSensor : public Sensor {
    RadarSensor()
        : Sensor(SensorType::RADAR, SensorMetadata("RADAR", 10.0)) {}

    void processData() override {
        std::cout << "Processing RADAR data with delay: " << metadata.processingDelay << " ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));
    }
};

// CAMERA sensor
struct CameraSensor : public Sensor {
    CameraSensor()
        : Sensor(SensorType::CAMERA, SensorMetadata("CAMERA", 15.0)) {}

    void processData() override {
        std::cout << "Processing CAMERA data with delay: " << metadata.processingDelay << " ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));
    }
};

// A constexpr function to compute the delay factor for different sensors
constexpr double computeDelayFactor(SensorType type) {
    switch (type) {
        case SensorType::LIDAR: return 1.0; // No additional factor
        case SensorType::RADAR: return 1.5; // Radar has a higher processing factor
        case SensorType::CAMERA: return 2.0; // Camera has the highest processing factor
        default: return 1.0;
    }
}

// Function to process sensor data
void handleSensor(Sensor& sensor) {
    double adjustedDelay = sensor.metadata.processingDelay * computeDelayFactor(sensor.type);
    std::cout << "Adjusted processing delay for " << sensor.metadata.name << ": " << adjustedDelay << " ms\n";
    
    sensor.processData();
}

// Example of a compile-time evaluation with constexpr
constexpr int maxSensors = 3;

int main() {
    // Create sensor instances
    std::array<Sensor*, maxSensors> sensors = {
        new LidarSensor(),
        new RadarSensor(),
        new CameraSensor()
    };

    // Process each sensor
    for (auto sensor : sensors) {
        handleSensor(*sensor);
    }

    // Clean up dynamically allocated memory
    for (auto sensor : sensors) {
        delete sensor;
    }

    return 0;
}

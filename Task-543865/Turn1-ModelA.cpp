#include <iostream>
#include <string>
#include <array>

// Define an enumeration for the sensor types
enum class SensorType {
    LIDAR,
    RADAR,
    CAMERA,
    UNKNOWN
};

// Base struct for Sensor
struct Sensor {
    SensorType type;

    virtual void processData() = 0; // Pure virtual function for processing data
};

// LIDAR sensor
struct LidarSensor : public Sensor {
    LidarSensor() { type = SensorType::LIDAR; }

    void processData() override {
        // Unique processing steps for LIDAR
        std::cout << "Processing LIDAR data...\n";
    }
};

// RADAR sensor
struct RadarSensor : public Sensor {
    RadarSensor() { type = SensorType::RADAR; }

    void processData() override {
        // Unique processing steps for RADAR
        std::cout << "Processing RADAR data...\n";
    }
};

// CAMERA sensor
struct CameraSensor : public Sensor {
    CameraSensor() { type = SensorType::CAMERA; }

    void processData() override {
        // Unique processing steps for CAMERA
        std::cout << "Processing CAMERA data...\n";
    }
};

// Function to process sensor data
void handleSensor(Sensor& sensor) {
    switch (sensor.type) {
        case SensorType::LIDAR:
            dynamic_cast<LidarSensor&>(sensor).processData();
            break;
        case SensorType::RADAR:
            dynamic_cast<RadarSensor&>(sensor).processData();
            break;
        case SensorType::CAMERA:
            dynamic_cast<CameraSensor&>(sensor).processData();
            break;
        default:
            std::cout << "Unknown sensor type.\n";
            break;
    }
}

// Example of a compile-time evaluation with constexpr
constexpr int maxSensors = 3;

template <typename T, std::size_t N>
constexpr std::size_t getArraySize(const T(&)[N]) { return N; }

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

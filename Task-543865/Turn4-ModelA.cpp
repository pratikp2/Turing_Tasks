#include <iostream>
#include <array>
#include <unordered_map>
#include <string>
#include <thread>
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
    const char* name;
    double processingDelay; // in milliseconds

    constexpr SensorMetadata(const char* n, double delay)
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
    LidarSensor() : Sensor(SensorType::LIDAR, SensorMetadata("LIDAR", 5.0)) {}

    void processData() override {
        std::cout << "Processing LIDAR data with delay: " << metadata.processingDelay << " ms\n";
        // Simulate processing delay
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));

        // Example: Dynamically store sensor readings
        std::unordered_map<std::string, double> lidarReadings = {
            {"Range", 10.5},
            {"Intensity", 49.0},
            {"AmbientLight", 5.2}
        };

        std::cout << "LIDAR Readings:\n";
        for (const auto& entry : lidarReadings) {
            std::cout << "  " << entry.first << ": " << entry.second << '\n';
        }
    }
};

// RADAR sensor
struct RadarSensor : public Sensor {
    RadarSensor() : Sensor(SensorType::RADAR, SensorMetadata("RADAR", 10.0)) {}

    void processData() override {
        std::cout << "Processing RADAR data with delay: " << metadata.processingDelay << " ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));

        // Using an array for fixed number of radar readings
        std::array<double, 5> radarReadings = { 1.0, 2.5, 3.0, 2.1, 5.0 };
        std::cout << "RADAR Readings:\n";
        for (double reading : radarReadings) {
            std::cout << "  " << reading << '\n';
        }
    }
};

// CAMERA sensor
struct CameraSensor : public Sensor {
    CameraSensor() : Sensor(SensorType::CAMERA, SensorMetadata("CAMERA", 15.0)) {}

    void processData() override {
        std::cout << "Processing CAMERA data with delay: " << metadata.processingDelay << " ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));

        // Example: Using std::unordered_map for camera settings
        std::unordered_map<std::string, std::string> cameraSettings = {
            {"Resolution", "1920x1080"},
            {"FrameRate", "30 fps"},
            {"Exposure", "Auto"}
        };

        std::cout << "CAMERA Settings:\n";
        for (const auto& setting : cameraSettings) {
            std::cout << "  " << setting.first << ": " << setting.second << '\n';
        }
    }
};

// A constexpr function to compute the delay factor for different sensors
constexpr double computeDelayFactor(SensorType type) {
    switch (type) {
        case SensorType::LIDAR: return 1.0;
        case SensorType::RADAR: return 1.5;
        case SensorType::CAMERA: return 2.0;
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

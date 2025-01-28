#include <iostream>
#include <string>
#include <array>
#include <unordered_map>
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
    double processingDelay;

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

// Class to dynamically store additional sensor data
struct SensorAdditionalData {
    std::unordered_map<SensorType, std::string> configs;
    std::array<double, 3> samplingFrequency{{10.0, 15.0, 20.0}}; // Predefined for LIDAR, RADAR, CAMERA

    void setConfig(SensorType type, const std::string& key, const std::string& value) {
        configs[type] = value;
    }

    std::string getConfig(SensorType type, const std::string& key) const {
        return configs.at(type).empty() ? "Not Set" : configs.at(type);
    }
};

// LIDAR sensor
struct LidarSensor : public Sensor {
    LidarSensor(SensorAdditionalData& data)
        : Sensor(SensorType::LIDAR, SensorMetadata("LIDAR", 5.0)), additionalData(data) {}

    void processData() override {
        std::cout << "Processing LIDAR data with delay: " << metadata.processingDelay << " ms\n";
        std::cout << "Setting LIDAR sample frequency: " << additionalData.samplingFrequency[0] << " Hz\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));
    }

private:
    SensorAdditionalData& additionalData;
};

// RADAR sensor
struct RadarSensor : public Sensor {
    RadarSensor(SensorAdditionalData& data)
        : Sensor(SensorType::RADAR, SensorMetadata("RADAR", 10.0)), additionalData(data) {}

    void processData() override {
        std::cout << "Processing RADAR data with delay: " << metadata.processingDelay << " ms\n";
        std::cout << "Setting RADAR sample frequency: " << additionalData.samplingFrequency[1] << " Hz\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));
    }

private:
    SensorAdditionalData& additionalData;
};

// CAMERA sensor
struct CameraSensor : public Sensor {
    CameraSensor(SensorAdditionalData& data)
        : Sensor(SensorType::CAMERA, SensorMetadata("CAMERA", 15.0)), additionalData(data) {}

    void processData() override {
        std::cout << "Processing CAMERA data with delay: " << metadata.processingDelay << " ms\n";
        std::cout << "Setting CAMERA sample frequency: " << additionalData.samplingFrequency[2] << " Hz\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(metadata.processingDelay)));
    }

private:
    SensorAdditionalData& additionalData;
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

constexpr int maxSensors = 3;

int main() {
    SensorAdditionalData additionalData;

    // Add dynamic sensor configurations
    additionalData.setConfig(SensorType::LIDAR, "resolution", "0.1 degrees");
    additionalData.setConfig(SensorType::RADAR, "range", "50 meters");
    additionalData.setConfig(SensorType::CAMERA, "resolution", "1920x1080");

    // Create sensor instances
    std::array<Sensor*, maxSensors> sensors = {
        new LidarSensor(additionalData),
        new RadarSensor(additionalData),
        new CameraSensor(additionalData)
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

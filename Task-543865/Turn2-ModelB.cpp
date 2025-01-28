#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <unique_ptr>
#include <chrono>
#include <cmath>
#include <random>

enum class SensorType { LIDAR, RADAR, CAMERA, UNKNOWN };

struct Sensor {
    SensorType type;
    virtual void processData() = 0;
};

struct LidarSensor : Sensor {
    LidarSensor() { type = SensorType::LIDAR; }
    void processData() override {
        // Simulate some computation
        std::cout << "Processing LIDAR data...\n";
    }
};

struct RadarSensor : Sensor {
    RadarSensor() { type = SensorType::RADAR; }
    void processData() override {
        // Simulate some computation
        std::cout << "Processing RADAR data...\n";
    }
};

struct CameraSensor : Sensor {
    CameraSensor() { type = SensorType::CAMERA; }
    void processData() override {
        // Simulate some computation
        std::cout << "Processing CAMERA data...\n";
    }
};

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

template <typename Container>
void processSensorsUsingContainer(Container& sensors) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto& sensor : sensors) {
        handleSensor(sensor);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Processing time: " << elapsed.count() << " ms\n";
}

template <std::size_t N>
void processSensorsUsingArray(std::array<std::unique_ptr<Sensor>, N>& sensors) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto& sensor : sensors) {
        handleSensor(*sensor);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Processing time: " << elapsed.count() << " ms\n";
}

int main() {
    constexpr int numSensors = 1000;

    {
        // Using std::vector
        std::vector<std::unique_ptr<Sensor>> sensors;
        for (int i = 0; i < numSensors; ++i) {
            SensorType sensorType = static_cast<SensorType>(i % 3);
            switch (sensorType) {
                case SensorType::LIDAR:
                    sensors.emplace_back(new LidarSensor());
                    break;
                case SensorType::RADAR:
                    sensors.emplace_back(new RadarSensor());
                    break;
                case SensorType::CAMERA:
                    sensors.emplace_back(new CameraSensor());
                    break;
                default:
                    break;
            }
        }

        processSensorsUsingContainer(sensors);
    }

    {
        // Using std::array
        std::array<std::unique_ptr<Sensor>, numSensors> sensors;
        for (int i = 0; i < numSensors; ++i) {
            SensorType sensorType = static_cast<SensorType>(i % 3);
            switch (sensorType) {
                case SensorType::LIDAR:
                    sensors[i] = std::make_unique<LidarSensor>();
                    break;
                case SensorType::RADAR:
                    sensors[i] = std::make_unique<RadarSensor>();
                    break;
                case SensorType::CAMERA:
                    sensors[i] = std::make_unique<CameraSensor>();
                    break;
                default:
                    break;
            }
        }

        processSensorsUsingArray(sensors);
    }

    return 0;
}

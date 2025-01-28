#include <iostream>

enum class SensorType {
    LIDAR,
    RADAR,
    CAMERA,
    UNKNOWN
};

// struct to group sensor metadata
struct SensorMetadata {
    const char* name;
    constexpr size_t processingDelayMs() const { return delayMs; }

    constexpr SensorMetadata(const char* name, size_t delayMs) 
        : name(name), delayMs(delayMs) {}

    size_t delayMs;
};

constexpr SensorMetadata sensorMetadatas[] = {
    {"LIDAR", 10},  // 10ms processing delay
    {"RADAR", 20},  // 20ms processing delay
    {"CAMERA", 5},   // 5ms processing delay
};

constexpr size_t numSensors = sizeof(sensorMetadatas) / sizeof(sensorMetadatas[0]);

SensorType getSensorTypeFromString(const std::string& sensorName) {
    for (size_t i = 0; i < numSensors; ++i) {
        if (std::strcmp(sensorMetadatas[i].name, sensorName.c_str()) == 0) {
            return static_cast<SensorType>(i);
        }
    }
    return SensorType::UNKNOWN;
}

constexpr size_t getProcessingDelayMs(SensorType type) {
    if (type >= numSensors) return 0;
    return sensorMetadatas[static_cast<size_t>(type)].processingDelayMs();
}

void printSensorDelay(SensorType type) {
    std::cout << "Processing delay for " << sensorMetadatas[static_cast<size_t>(type)].name 
              << ": " << getProcessingDelayMs(type) << " ms\n";
}

int main() {
    std::string sensorName1 = "LIDAR";
    std::string sensorName2 = "INVALID";
    
    SensorType type1 = getSensorTypeFromString(sensorName1);
    SensorType type2 = getSensorTypeFromString(sensorName2);
    
    printSensorDelay(type1);
    printSensorDelay(type2);

    return 0;
}

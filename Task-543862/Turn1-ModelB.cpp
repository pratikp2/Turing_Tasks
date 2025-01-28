#include <iostream>

enum SensorStatus {
    OK = 0,       // Sensor is functioning normally
    FAULT = 1,    // Sensor has detected a fault
    LOW_SIGNAL = 2, // Sensor signal is too low
    HIGH_SIGNAL = 3, // Sensor signal is too high
    OVERHEAT = 4,   // Sensor is overheating
    COMM_ERROR = 5,  // Communication error with sensor
    UNKNOWN = 6     // Unrecognized sensor status code
};

std::string translateSensorStatus(SensorStatus status) {
    std::string response;
    switch (status) {
        case OK:
            response = "Sensor OK";
            break;
        case FAULT:
            response = "Sensor Fault";
            break;
        case LOW_SIGNAL:
            response = "Sensor Low Signal";
            break;
        case HIGH_SIGNAL:
            response = "Sensor High Signal";
            break;
        case OVERHEAT:
            response = "Sensor Overheating";
            break;
        case COMM_ERROR:
            response = "Sensor Communication Error";
            break;
        default:
            // Default case for unexpected status codes
            response = "Unexpected Sensor Status: " + std::to_string(static_cast<int>(status));
            std::cerr << "WARNING: Received unexpected sensor status code: " << response << std::endl;
    }
    return response;
}

int main() {
    SensorStatus statusCodes[] = {OK, FAULT, LOW_SIGNAL, HIGH_SIGNAL, OVERHEAT, COMM_ERROR, static_cast<SensorStatus>(7)};

    for (const auto& status : statusCodes) {
        std::cout << "Sensor Status: " << translateSensorStatus(status) << std::endl;
    }
    return 0;
}

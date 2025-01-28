#include <iostream>
#include <string>

enum SensorStatus {
    STATUS_OK = 0,
    STATUS_WARNING = 1,
    STATUS_ERROR = 2,
    STATUS_MAINTENANCE_REQUIRED = 3,
    STATUS_UNKNOWN = 99  // Example of a known unexpected status
    // Add more statuses as necessary
};

void processSensorStatus(int statusCode) {
    switch (statusCode) {
        case STATUS_OK:
            std::cout << "Sensor Status: OK. All systems are functioning normally." << std::endl;
            break;
        case STATUS_WARNING:
            std::cout << "Sensor Status: WARNING. Check the sensor readings." << std::endl;
            break;
        case STATUS_ERROR:
            std::cout << "Sensor Status: ERROR. Immediate attention required!" << std::endl;
            break;
        case STATUS_MAINTENANCE_REQUIRED:
            std::cout << "Sensor Status: MAINTENANCE REQUIRED. Schedule a maintenance check." << std::endl;
            break;
        default:
            // Handle unexpected status codes
            // This helps to improve reliability by logging and notifying the system.
            if (statusCode < 0) {
                std::cerr << "Error: Received negative status code: " << statusCode << ". This is invalid." << std::endl;
            } else {
                std::cerr << "Warning: Received unexpected status code: " << statusCode << ". Please check the sensor's integrity." << std::endl;
            }
            // Optionally, log the unexpected code for further analysis
            // logUnexpectedCode(statusCode);
            break;
    }
}

int main() {
    // Example usage of processSensorStatus
    processSensorStatus(STATUS_OK);                       // Expected status
    processSensorStatus(STATUS_WARNING);                  // Expected status
    processSensorStatus(STATUS_ERROR);                    // Expected status
    processSensorStatus(STATUS_MAINTENANCE_REQUIRED);     // Expected status
    processSensorStatus(STATUS_UNKNOWN);                  // Known unexpected status
    processSensorStatus(-1);                              // Invalid negative input
    processSensorStatus(100);                             // Unexpected input

    return 0;
}

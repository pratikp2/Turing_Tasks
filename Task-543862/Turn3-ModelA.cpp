#include <iostream>
#include <string>

// Define basic sensor status values using an enum for clarity.
enum SensorStatus {
    STATUS_ACTIVE = 100,          // Sensor is actively sensing.
    STATUS_IDLE = 200,            // Sensor is idle, but still operational.
    STATUS_DISCONNECTED = 404      // Sensor is disconnected and unable to provide data.
};

// Function to process the sensor status codes with appropriate handling.
void processSensorStatus(int statusCode) {
    switch (statusCode) {
        case STATUS_ACTIVE:
            std::cout << "Sensor Status: ACTIVE. The sensor is functioning properly." << std::endl;
            // Perform necessary actions for active status (e.g., data collection).
            break;

        case STATUS_IDLE:
            std::cout << "Sensor Status: IDLE. The sensor is waiting for further commands." << std::endl;
            // Potential interaction could be triggered for an idle sensor.
            break;

        case STATUS_DISCONNECTED:
            std::cout << "Sensor Status: DISCONNECTED. Check the connection or sensor integrity." << std::endl;
            // Prompt for a specific action like checking wiring or power supply.
            break;

        default:
            // Handle unexpected status codes, providing robustness against invalid inputs.
            std::cerr << "Warning: Received unrecognized status code: " << statusCode << ". "
                      << "This might indicate a malfunctioning sensor or incorrect input value." << std::endl;
            // Log the incident or take corrective action if necessary.
            break;
    }
}

int main() {
    // Example usage of processSensorStatus with different status codes.
    processSensorStatus(STATUS_ACTIVE);          // Normal operation
    processSensorStatus(STATUS_IDLE);            // Normal operation but awaiting action
    processSensorStatus(STATUS_DISCONNECTED);     // Indicating an error or connection problem
    processSensorStatus(0);                       // Unrecognized status, falls into default
    processSensorStatus(500);                     // Unrecognized status, falls into default

    return 0;
}

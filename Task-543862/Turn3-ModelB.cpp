#include <iostream>
#include <string>

enum SensorStatus {
    STATUS_ACTIVE = 100,
    STATUS_IDLE = 200,
    STATUS_DISCONNECTED = 404,
    STATUS_ERROR = -1,
    STATUS_UNKNOWN = 999
};

std::string processSensorStatus(int statusCode) {
    std::string statusMessage;
    switch (statusCode) {
        case STATUS_ACTIVE:
            statusMessage = "Sensor Status: Active. Sensor is currently functioning.";
            break;
        case STATUS_IDLE:
            statusMessage = "Sensor Status: Idle. Sensor is ready but not in use.";
            break;
        case STATUS_DISCONNECTED:
            statusMessage = "Sensor Status: Disconnected. Sensor is not available.";
            break;
        default:
            // Handle unexpected status codes
            if (statusCode < 0) {
                statusMessage = "Error: Received a negative status code. This is invalid.";
            } else if (statusCode == STATUS_UNKNOWN) {
                statusMessage = "Warning: Received an unknown status code. Please check sensor configuration.";
            } else {
                statusMessage = "Warning: Received an unexpected status code: " + std::to_string(statusCode);
            }
            // Optionally, you can log the unexpected code here
            // logUnexpectedCode(statusCode);
            break;
    }
    return statusMessage;
}

int main() {
    int statusCode;
    std::cout << "Enter sensor status code: ";
    std::cin >> statusCode;

    std::string statusMessage = processSensorStatus(statusCode);
    std::cout << statusMessage << std::endl;

    return 0;
}

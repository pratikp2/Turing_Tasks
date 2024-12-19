#include <iostream>

enum SystemStatus {
    STATUS_OK = 1 << 0,       // 0001
    STATUS_WARNING = 1 << 1,  // 0010
    STATUS_FAULT = 1 << 2,    // 0100
    STATUS_UNKNOWN = 1 << 3    // 1000
};

// Function to check if a specific status is set
bool isStatusSet(int status, SystemStatus flag) {
    return (status & flag) != 0;
}

// Function to set a specific status
void setStatus(int &status, SystemStatus flag) {
    status |= flag;
}

// Function to clear a specific status
void clearStatus(int &status, SystemStatus flag) {
    status &= ~flag;
}

// Function to demonstrate usage
void demonstrateStatusManagement() {
    int systemStatus = 0; // Initial status: 0000

    // Set some statuses
    setStatus(systemStatus, STATUS_OK);
    setStatus(systemStatus, STATUS_WARNING);

    // Current status (expecting 0011)
    std::cout << "Current Status: " << std::bitset<4>(systemStatus) << std::endl;

    // Check statuses
    std::cout << "Is OK: " << isStatusSet(systemStatus, STATUS_OK) << std::endl;
    std::cout << "Is WARNING: " << isStatusSet(systemStatus, STATUS_WARNING) << std::endl;
    std::cout << "Is FAULT: " << isStatusSet(systemStatus, STATUS_FAULT) << std::endl;

    // Clear WARNING status
    clearStatus(systemStatus, STATUS_WARNING);
    std::cout << "After clearing WARNING: " << std::bitset<4>(systemStatus) << std::endl;
}

int main() {
    demonstrateStatusManagement();
    return 0;
}

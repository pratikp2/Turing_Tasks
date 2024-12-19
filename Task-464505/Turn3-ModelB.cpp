#include <iostream>
#include <assert.h>

enum SystemStatus {
    STATUS_OK = 1 << 0,
    STATUS_WARNING = 1 << 1,
    STATUS_FAULT = 1 << 2
};

void toggleStatus(int &status, SystemStatus flag) {
    status ^= flag;
}

void demonstrateToggleStatus() {
    int systemStatus = 0;

    std::cout << "Initial Status: " << std::bitset<4>(systemStatus) << std::endl;

    toggleStatus(systemStatus, STATUS_OK);
    std::cout << "Status after toggling OK: " << std::bitset<4>(systemStatus) << std::endl;

    toggleStatus(systemStatus, STATUS_WARNING);
    std::cout << "Status after toggling WARNING: " << std::bitset<4>(systemStatus) << std::endl;

    // Assertion to check if FAULT is still clear
    assert((systemStatus & STATUS_FAULT) == 0, "FAULT flag should be clear");
}

int main() {
    demonstrateToggleStatus();
    return 0;
}

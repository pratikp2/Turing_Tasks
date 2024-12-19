#include <iostream>
#include <cassert>
#include <bitset>

enum SystemStatus {
    STATUS_OK = 1 << 0,
    STATUS_WARNING = 1 << 1,
    STATUS_FAULT = 1 << 2,
};

class StatusManager {
private:
    int status;

public:
    StatusManager() : status(0) {}

    void setStatus(SystemStatus flag) {
        // Assert that STATUS_FAULT cannot be set if STATUS_OK is already set
        assert(!(flag & STATUS_FAULT && (status & STATUS_OK)));
        std::cout << "Setting status: " << std::bitset<3>(flag) << " Current status: " << std::bitset<3>(status) << std::endl;
        status |= flag;
    }

    void clearStatus(SystemStatus flag) {
        std::cout << "Clearing status: " << std::bitset<3>(flag) << " Current status: " << std::bitset<3>(status) << std::endl;
        status &= ~flag;
    }

    bool isSet(SystemStatus flag) {
        return (status & flag) != 0;
    }

    void displayStatus() {
        std::cout << "Current Status: " << std::bitset<3>(status) << std::endl;
    }
};

int main() {
    StatusManager sm;
    sm.setStatus(STATUS_OK);
    sm.setStatus(STATUS_WARNING);
    sm.displayStatus();
    sm.clearStatus(STATUS_WARNING);
    sm.displayStatus();

    // Uncommenting the following line will trigger an assertion
    // sm.setStatus(STATUS_FAULT);

    return 0;
}

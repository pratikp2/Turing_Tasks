#include <iostream>
#include <memory>
#include <unordered_map>

// Abstract State class
class DeviceState {
public:
    virtual ~DeviceState() = default;
    virtual void handleEvent(Device* device, const std::string& event) = 0;
};

// Concrete State classes
class IdleState : public DeviceState {
public:
    void handleEvent(Device* device, const std::string& event) override {
        if (event == "connect") {
            std::cout << "Device connected. Transitioning to ConnectedState." << std::endl;
            device->setState(ConnectedState::getInstance());
        }
    }
};

class ConnectedState : public DeviceState {
public:
    static ConnectedState* getInstance() {
        static ConnectedState instance;
        return &instance;
    }

    void handleEvent(Device* device, const std::string& event) override {
        if (event == "disconnect") {
            std::cout << "Device disconnected. Transitioning to IdleState." << std::endl;
            device->setState(IdleState::getInstance());
        } else if (event == "data_received") {
            std::cout << "Data received. Transitioning to DataProcessingState." << std::endl;
            device->setState(DataProcessingState::getInstance());
        }
    }
};

class DataProcessingState : public DeviceState {
public:
    static DataProcessingState* getInstance() {
        static DataProcessingState instance;
        return &instance;
    }
    
    void handleEvent(Device* device, const std::string& event) override {
        if (event == "data_processed") {
            std::cout << "Data processed. Transitioning to ConnectedState." << std::endl;
            device->setState(ConnectedState::getInstance());
        }
    }
};
 
class Device {
public:
    Device() {
        setState(IdleState::getInstance());
    }

    void handleEvent(const std::string& event) {
        currentState_->handleEvent(this, event);
    }

    void setState(DeviceState* newState) {
        currentState_ = newState;
    }

private:
    std::unique_ptr<DeviceState> currentState_;
};

 
int main() {
    Device device;

    device.handleEvent("connect");
    device.handleEvent("data_received");
    device.handleEvent("data_processed");
    device.handleEvent("disconnect");
    device.handleEvent("connect");
    return 0;
}
  
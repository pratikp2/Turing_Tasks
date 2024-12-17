#include <iostream>
#include <memory>

// Product Interface
class EdgeDevice {
public:
    virtual void operate() = 0; // Common operation
    virtual ~EdgeDevice() = default; // Virtual Destructor
};

// Concrete Product - Sensor
class Sensor : public EdgeDevice {
public:
    void operate() override {
        std::cout << "Operating Sensor" << std::endl;
    }
};

// Concrete Product - Router
class Router : public EdgeDevice {
public:
    void operate() override {
        std::cout << "Operating Router" << std::endl;
    }
};

// Creator - Factory Interface
class EdgeDeviceFactory {
public:
    virtual std::unique_ptr<EdgeDevice> createDevice() = 0; // Factory Method
    virtual ~EdgeDeviceFactory() = default; // Virtual Destructor
};

// Concrete Factory for Sensor
class SensorFactory : public EdgeDeviceFactory {
public:
    std::unique_ptr<EdgeDevice> createDevice() override {
        return std::make_unique<Sensor>();
    }
};

// Concrete Factory for Router
class RouterFactory : public EdgeDeviceFactory {
public:
    std::unique_ptr<EdgeDevice> createDevice() override {
        return std::make_unique<Router>();
    }
};

// Client Code
void clientCode(EdgeDeviceFactory& factory) {
    std::unique_ptr<EdgeDevice> device = factory.createDevice();
    device->operate(); // Use the created device
}

int main() {
    SensorFactory sensorFactory;
    RouterFactory routerFactory;

    std::cout << "Creating Sensor:" << std::endl;
    clientCode(sensorFactory); // Operate sensor

    std::cout << "Creating Router:" << std::endl;
    clientCode(routerFactory); // Operate router

    return 0;
}

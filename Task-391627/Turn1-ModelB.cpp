#include <iostream>
#include <string>
#include <memory>

class EdgeDevice {
public:
    virtual ~EdgeDevice() = default;
    virtual std::string getDeviceType() const = 0;
    virtual void operate() const = 0;
};

class Sensor : public EdgeDevice {
public:
    std::string getDeviceType() const override {
        return "Sensor";
    }
    void operate() const override {
        std::cout << "Sensor is operating." << std::endl;
    }
};

class Router : public EdgeDevice {
public:
    std::string getDeviceType() const override {
        return "Router";
    }
    void operate() const override {
        std::cout << "Router is operating." << std::endl;
    }
};

class EdgeDeviceFactory {
public:
    virtual ~EdgeDeviceFactory() = default;
    virtual std::unique_ptr<EdgeDevice> createDevice(const std::string& type) const = 0;
};

class SensorFactory : public EdgeDeviceFactory {
public:
    std::unique_ptr<EdgeDevice> createDevice(const std::string& type) const override {
        if (type == "Sensor") {
            return std::make_unique<Sensor>();
        } else {
            throw std::runtime_error("Invalid device type: " + type);
        }
    }
};

class RouterFactory : public EdgeDeviceFactory {
public:
    std::unique_ptr<EdgeDevice> createDevice(const std::string& type) const override {
        if (type == "Router") {
            return std::make_unique<Router>();
        } else {
            throw std::runtime_error("Invalid device type: " + type);
        }
    }
};

int main() {
    std::vector<std::unique_ptr<EdgeDevice>> devices;

    {
        std::unique_ptr<EdgeDeviceFactory> sensorFactory(new SensorFactory);
        devices.push_back(sensorFactory->createDevice("Sensor"));
        devices.push_back(sensorFactory->createDevice("Router"));  // This will throw an exception
    }

    {
        std::unique_ptr<EdgeDeviceFactory> routerFactory(new RouterFactory);
        devices.push_back(routerFactory->createDevice("Router"));
        devices.push_back(routerFactory->createDevice("Sensor"));  // This will throw an exception
    }

    for (const auto& device : devices) {
        std::cout << "Device Type: " << device->getDeviceType() << std::endl;
        device->operate();
    }

    return 0;
}

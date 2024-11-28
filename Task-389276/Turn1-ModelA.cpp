#include <iostream>
#include <vector>
#include <memory>

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;

    // Pure virtual method to update observers
    virtual void update() = 0;
};

// Concrete Observer class
class WeatherDisplay : public Observer {
private:
    double temperature;
    double humidity;

public:
    WeatherDisplay(double temp, double hum) : temperature(temp), humidity(hum) {}

    void setTemperature(double newTemperature) {
        if (temperature != newTemperature) {
            temperature = newTemperature;
            std::cout << "Temperature is: " << temperature << std::endl;
        }
    }

    void setHumidity(double newHumidity) {
        if (humidity != newHumidity) {
            humidity = newHumidity;
            std::cout << "Humidity is: " << humidity << std::endl;
        }
    }

    void update() override {
        setTemperature(subject->getTemperature());
        setHumidity(subject->getHumidity());
    }
};

// Subject class with observers
class Subject {
private:
    std::vector<std::unique_ptr<Observer>> observers; // Using unique_ptr for ownership

protected:
    virtual void notifyObservers() const {
        for (auto& observer : observers) {
            observer->update();
        }
    }

public:
    void attach(std::unique_ptr<Observer> observer) {
        observers.push_back(std::move(observer));
    }

    void detach(const Observer& observer) {
        if (std::find(observers.begin(), observers.end(), &observer) != observers.end()) {
            observers.erase(std::remove(observers.begin(), observers.end(), &observer), observers.end());
        }
    }

    void clear() {
        observers.clear();
    }

    virtual double getTemperature() const = 0;
    virtual double getHumidity() const = 0;
};

// Concrete Subject class
class WeatherData : public Subject {
private:
    double temperature;
    double humidity;

public:
    WeatherData(double temp, double hum) : temperature(temp), humidity(hum) {}

    void setTemperature(double newTemperature) {
        if (temperature != newTemperature) {
            temperature = newTemperature;
            notifyObservers();
        }
    }

    void setHumidity(double newHumidity) {
        if (humidity != newHumidity) {
            humidity = newHumidity;
            notifyObservers();
        }
    }

    double getTemperature() const override {
        return temperature;
    }

    double getHumidity() const override {
        return humidity;
    }
};

int main() {
    // Create a subject
    auto weatherData = std::make_unique<WeatherData>(75.0, 60.0);

    // Create observers
    auto weatherDisplay1 = std::make_unique<WeatherDisplay>(0.0, 0.0);
    auto weatherDisplay2 = std::make_unique<WeatherDisplay>(0.0, 0.0);

    // Attach observers
    weatherData->attach(std::move(weatherDisplay1));
    weatherData->attach(std::move(weatherDisplay2));

    // Update the subject's state
    weatherData->setTemperature(80.0);
    weatherData->setHumidity(70.0);

    return 0;
}
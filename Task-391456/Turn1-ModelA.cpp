#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <memory>
#include <algorithm>

// Forward declaration
class Observer;

// Subject class
class Subject {
public:
    void registerObserver(std::shared_ptr<Observer> observer);
    void unregisterObserver(std::shared_ptr<Observer> observer);
    void notifyObservers(const std::string& eventData);
    
private:
    std::vector<std::weak_ptr<Observer>> observers;
    std::mutex mtx;  // Mutex for thread safety
};

// Observer interface
class Observer {
public:
    virtual void update(const std::string& eventData) = 0;
};

// Implementation of Subject methods
void Subject::registerObserver(std::shared_ptr<Observer> observer) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock for thread safety
    observers.push_back(observer);
}

void Subject::unregisterObserver(std::shared_ptr<Observer> observer) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock for thread safety
    observers.erase(std::remove_if(observers.begin(), observers.end(),
        [&observer](const std::weak_ptr<Observer>& obs) {
            return obs.lock() == observer; 
        }), observers.end());
}

void Subject::notifyObservers(const std::string& eventData) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock for thread safety
    for (auto& obs : observers) {
        if (auto observer = obs.lock()) {
            observer->update(eventData);  // Notify the observer
        }
    }
}

// Sample Observer implementation
class ConcreteObserver : public Observer {
public:
    void update(const std::string& eventData) override {
        std::cout << "Received event: " << eventData << std::endl;
    }
};

// Usage
int main() {
    Subject subject;

    auto observer1 = std::make_shared<ConcreteObserver>();
    auto observer2 = std::make_shared<ConcreteObserver>();

    subject.registerObserver(observer1);
    subject.registerObserver(observer2);

    // Simulate event notification
    subject.notifyObservers("Sensitive event data");

    // Unregister observer1
    subject.unregisterObserver(observer1);

    // Notify again
    subject.notifyObservers("Another event data");

    return 0;
}

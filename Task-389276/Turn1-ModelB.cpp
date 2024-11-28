
#include <iostream>
#include <vector>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() {
        for (auto& observer : observers) {
            observer->update();
        }
    }
};

class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    ConcreteObserver(const std::string& name) : name(name) {}

    void update() override {
        std::cout << name << " was updated!" << std::endl;
    }
};

int main() {
    std::shared_ptr<Subject> subject = std::make_shared<Subject>();

    // Create observers using shared pointers
    std::shared_ptr<Observer> observer1 = std::make_shared<ConcreteObserver>("Observer 1");
    std::shared_ptr<Observer> observer2 = std::make_shared<ConcreteObserver>("Observer 2");

    // Attach observers to the subject
    subject->attach(observer1);
    subject->attach(observer2);

    // Subject makes a change and notifies all observers
    subject->notify();

    // Detach observer1
    subject->detach(observer1);

    subject->notify();
    
    return 0;
}
 
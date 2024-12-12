#include <iostream>
#include <vector>
#include <memory>

class Subject {
public:
    using ObserverPtr = std::shared_ptr<Observer>;

    explicit Subject(const std::string& name) : name_(name) {}

    void registerObserver(ObserverPtr observer) {
        if (std::find(observers_.begin(), observers_.end(), observer) == observers_.end()) {
            // Add access control checks here
            observers_.push_back(observer);
        }
    }

    void removeObserver(ObserverPtr observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void notifyObservers() const {
        for (const auto& observer : observers_) {
            observer->update(*this);
        }
    }

    const std::string& getName() const { return name_; }

private:
    std::vector<ObserverPtr> observers_;
    std::string name_;
};

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(const Subject& subject) = 0;
};

class ConcreteObserver : public Observer {
public:
    void update(const Subject& subject) override {
        std::cout << "ConcreteObserver notified: Subject " << subject.getName() << " updated." << std::endl;
    }
};

int main() {
    std::shared_ptr<Subject> subject = std::make_shared<Subject>("My Subject");
    std::shared_ptr<ConcreteObserver> observer1 = std::make_shared<ConcreteObserver>();
    std::shared_ptr<ConcreteObserver> observer2 = std::make_shared<ConcreteObserver>();

    subject->registerObserver(observer1);
    subject->registerObserver(observer2);

    subject->notifyObservers();  // Output: ConcreteObserver notified: Subject My Subject updated.
                                 //        ConcreteObserver notified: Subject My Subject updated.

    return 0;
}

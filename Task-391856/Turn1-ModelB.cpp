#include <iostream>
#include <vector>
#include <memory>

// Observer interface
class Observer {
public:
    virtual void onCreate(int id) = 0;
    virtual void onUpdate(int id) = 0;
    virtual void onDestroy(int id) = 0;
};

// Subject class
class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(std::shared_ptr<Observer> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    
    void notifyCreate(int id) {
        for (const auto& observer : observers) {
            observer->onCreate(id);
        }
    }
    
    void notifyUpdate(int id) {
        for (const auto& observer : observers) {
            observer->onUpdate(id);
        }
    }
    
    void notifyDestroy(int id) {
        for (const auto& observer : observers) {
            observer->onDestroy(id);
        }
    }
};

// Entity class
class Entity {
private:
    int id;
    static int counter;
    Subject& subject;
public:
    Entity(Subject& subj) : id(counter++), subject(subj) {
        subject.notifyCreate(id);
    }
    
    void update() {
        // Logic to update the entity
        subject.notifyUpdate(id);
    }
    
    ~Entity() {
        subject.notifyDestroy(id);
    }
    
    int getId() const {
        return id;
    }
};

int Entity::counter = 0;

// ConcreteObserver class
class ConsoleLogger : public Observer {
public:
    void onCreate(int id) override {
        std::cout << "Entity " << id << " created.\n";
    }
    
    void onUpdate(int id) override {
        std::cout << "Entity " << id << " updated.\n";
    }
    
    void onDestroy(int id) override {
        std::cout << "Entity " << id << " destroyed.\n";
    }
};

int main() {
    Subject subject;
    std::shared_ptr<Observer> logger = std::make_shared<ConsoleLogger>();
    
    subject.addObserver(logger);
    
    {
        Entity e1(subject);
        e1.update();

        Entity e2(subject);
        e2.update();
    } // Entities go out of scope and are destroyed here
   
    subject.removeObserver(logger);
    
    return 0;
}

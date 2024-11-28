// Incorrect implementation using raw pointers
class Subject {
private:
    Observer* observer;

public:
    void attach(Observer* obs) {
        observer = obs;
    }

    void detach(Observer* obs) {
        observer = nullptr;
    }
};

class Observer {
public:
    Observer() {}
    ~Observer() {}
    void update() {}
};

int main() {
    Subject subject;
    Observer* observer = new Observer;

    subject.attach(observer);

    // Memory leak occurs because the observer is not deleted
    // The observer will remain in memory until the subject is destroyed

    return 0;
}
// Correct implementation using shared_ptr
class Subject {
private:
    std::shared_ptr<Observer> observer;

public:
    void attach(std::shared_ptr<Observer> obs) {
        observer = obs;
    }

    void detach(std::shared_ptr<Observer> obs) {
        observer.reset();
    }
};

class Observer {
public:
    Observer() {}
    ~Observer() {}
    void update() {}
};

int main() {
    Subject subject;
    std::shared_ptr<Observer> observer = std::make_shared<Observer>();

    subject.attach(observer);

    // The observer will be automatically deleted when the last shared_ptr referencing it is destroyed

    return 0;
}

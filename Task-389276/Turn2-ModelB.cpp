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
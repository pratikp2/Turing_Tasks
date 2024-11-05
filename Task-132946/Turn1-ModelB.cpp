#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <atomic>

class Publisher {
public:
    Publisher(const std::string& name) : name_(name) {}
    virtual ~Publisher() = default;

    virtual void publish(const std::string& message) = 0;

    std::string getName() const { return name_; }

protected:
    std::string name_;
};

class Publisher1 : public Publisher {
public:
    Publisher1() : Publisher("Publisher1") {}

    void publish(const std::string& message) override {
        // Simulate publishing data
        std::cout << "Publisher1: " << message << std::endl;
        usleep(500000); // Delay of 0.5 seconds for demonstration purposes
    }
};

class Publisher2 : public Publisher {
public:
    Publisher2() : Publisher("Publisher2") {}
    void publish(const std::string& message) override {
        // Simulate publishing data (Same behavior as Publisher1)
        std::cout << "Publisher2: " << message << std::endl;
        usleep(500000);
    }
};

class Subscriber {
public:
    Subscriber(const std::string& name) : name_(name) {}
    virtual ~Subscriber() = default;

    virtual void receive(const std::string& message) = 0;

    std::string getName() const { return name_; }

protected:
    std::string name_;
};

class SubscriberImpl : public Subscriber {
public:
    SubscriberImpl() : Subscriber("Subscriber") {}

    void receive(const std::string& message) override {
        std::cout << "Subscriber: Received message - " << message << std::endl;
    }
};

// Global variables
std::vector<Publisher*> publishers;
std::vector<Subscriber*> subscribers;
std::atomic<bool> stop_flag{false};

// Function to simulate the fault
void simulateFault() {
    // Introduce a fault by deleting the first publisher
    delete publishers[0];
    publishers.erase(publishers.begin());

    // Simulate fault recovery logic here
    // For demonstration purposes, we will just add the second publisher as active.
    publishers.push_back(new Publisher2());

    std::cout << "Fault recovery initiated. Switching to the redundant publisher." << std::endl;
}

// Publisher thread function
void publishMessages(Publisher* publisher) {
    int message_id = 1;
    while (!stop_flag.load()) {
        std::string message = "Message " + std::to_string(message_id);
        publisher->publish(message);
        message_id++;
    }
}

// Subscriber thread function
void receiveMessages(Subscriber* subscriber) {
    while (!stop_flag.load()) {
        // Simulate message reception
        for (Publisher* publisher : publishers) {
            std::string message = publisher->getName() + " Message";
            subscriber->receive(message);
        }
    }
}

int main() {
    // Initialize publishers and subscribers
    publishers.push_back(new Publisher1());
    publishers.push_back(new Publisher2());
    subscribers.push_back(new SubscriberImpl());

    // Start publisher threads
    std::vector<std::thread> publisher_threads;
    for (Publisher* publisher : publishers) {
        publisher_threads.push_back(std::thread(publishMessages, publisher));
    }

    // Start subscriber threads
    std::vector<std::thread> subscriber_threads;
    for (Subscriber* subscriber : subscribers) {
        subscriber_threads.push_back(std::thread(receiveMessages, subscriber));
    }

    // Simulate the fault after 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    simulateFault();

    // Wait for threads to finish
    for (std::thread& thread : publisher_threads) {
        thread.join();
    }

    for (std::thread& thread : subscriber_threads) {
        thread.join();
    }

    // Clean up
    for (Publisher* publisher : publishers) {
        delete publisher;
    }

    for (Subscriber* subscriber : subscribers) {
        delete subscriber;
    }

    return 0;
}

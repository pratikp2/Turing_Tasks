#include <iostream>
#include <queue>
#include <functional>
#include <utility>

// Define a simple event structure with a priority
struct Event {
    int priority;
    std::function<void()> callback;

    Event(int p, const std::function<void()>& cb)
        : priority(p), callback(cb) {}

    // Overload operator< for priority_queue to sort by priority in descending order
    bool operator<(const Event& other) const {
        return priority > other.priority;
    }
};

class EventManager {
private:
    std::priority_queue<Event> eventQueue;

public:
    // Enqueue an event with a given priority
    void enqueueEvent(int priority, const std::function<void()>& callback) {
        eventQueue.push(Event(priority, callback));
    }

    // Dequeue and execute the next event
    void processEvent() {
        if (!eventQueue.empty()) {
            Event event = eventQueue.top();
            eventQueue.pop();
            event.callback();
        }
    }

    // Process all events in the queue
    void processAllEvents() {
        while (!eventQueue.empty()) {
            Event event = eventQueue.top();
            eventQueue.pop();
            event.callback();
        }
    }
};

int main() {
    // Create an EventManager instance
    EventManager eventManager;

    // Define some events with different priorities
    eventManager.enqueueEvent(2, []() { std::cout << "Event 2: Medium priority" << std::endl; });
    eventManager.enqueueEvent(5, []() { std::cout << "Event 5: High priority" << std::endl; });
    eventManager.enqueueEvent(1, []() { std::cout << "Event 1: Low priority" << std::endl; });
    eventManager.enqueueEvent(4, []() { std::cout << "Event 4: Medium priority" << std::endl; });
    eventManager.enqueueEvent(3, []() { std::cout << "Event 3: Medium priority" << std::endl; });

    // Process events one by one
    while (!eventManager.eventQueue.empty()) {
        eventManager.processEvent();
    }

    return 0;
}

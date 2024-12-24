#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

// Define types for easier understanding
using EventID = int;
using Callback = std::function<void()>;

struct Event {
    EventID id;
    std::vector<Callback> callbacks; // Vector to hold callbacks for the event

    void trigger() {
        for (auto &callback : callbacks) {
            callback(); // Call the registered callbacks
        }
    }
};

class EventManager {
private:
    std::unordered_map<EventID, Event*> eventMap; // Event storage

public:
    void registerEvent(EventID id) {
        if (eventMap.find(id) == eventMap.end()) {
            eventMap[id] = new Event{id}; // Allocate new Event instance
        }
    }

    void registerCallback(EventID id, Callback callback) {
        if (eventMap.find(id) != eventMap.end()) {
            eventMap[id]->callbacks.push_back(callback);
        }
    }

    void triggerEvent(EventID id) {
        if (eventMap.find(id) != eventMap.end()) {
            eventMap[id]->trigger(); // Trigger the event
        }
    }

    ~EventManager() {
        for (auto &pair : eventMap) {
            delete pair.second; // Free allocated memory
        }
    }
};

void onButtonClick() {
    std::cout << "Button Clicked!" << std::endl;
}

void onWindowOpen() {
    std::cout << "Window Opened!" << std::endl;
}

int main() {
    EventManager manager;

    // Create and register events
    manager.registerEvent(1); // Button Click
    manager.registerEvent(2); // Window Open

    // Register callbacks for events
    manager.registerCallback(1, onButtonClick); // For button click event
    manager.registerCallback(2, onWindowOpen);  // For window open event

    // Trigger events
    manager.triggerEvent(1);
    manager.triggerEvent(2);

    return 0;
}

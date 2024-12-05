#include <iostream>
#include <queue>
#include <vector>
#include <string>

// Define a structure for the game event
struct GameEvent {
    int priority;      // Priority of the event (higher numbers indicate higher priority)
    std::string name;  // Name of the event

    // Constructor
    GameEvent(int p, const std::string& n) : priority(p), name(n) {}

    // Overload the < operator to make the priority queue a max-heap
    // (the default behavior is a max-heap with the highest priority at the top)
    bool operator<(const GameEvent& other) const {
        return priority < other.priority;
    }
};

// Function to process an event
void processEvent(const GameEvent& event) {
    std::cout << "Processing event: " << event.name << " with priority: " << event.priority << std::endl;
}

int main() {
    // Create a priority queue to handle game events
    std::priority_queue<GameEvent> eventQueue;

    // Add some events with varying priorities
    eventQueue.emplace(1, "Low Priority Event");
    eventQueue.emplace(5, "High Priority Event");
    eventQueue.emplace(3, "Medium Priority Event");
    eventQueue.emplace(4, "Second Highest Priority Event");

    // Process events based on their priority
    while (!eventQueue.empty()) {
        GameEvent currentEvent = eventQueue.top();
        eventQueue.pop();
        processEvent(currentEvent);
    }

    return 0;
}

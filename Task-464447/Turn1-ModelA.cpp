#include <iostream>

enum class TrafficLight {
    Red,
    Yellow,
    Green
};

void respondToTrafficLight(TrafficLight light) {
    // Respond to the current state of the traffic light
    switch (light) {
        case TrafficLight::Red:
            // Stop the vehicle; Red light indicates no entry
            std::cout << "Stop! The light is red." << std::endl;
            break;

        case TrafficLight::Yellow:
            // Prepare to stop; Yellow light indicates caution
            std::cout << "Caution! The light is yellow." << std::endl;
            break;

        case TrafficLight::Green:
            // Proceed; Green light indicates go
            std::cout << "Go! The light is green." << std::endl;
            break;

        default:
            // Handle unexpected values; In this case, log an error
            // This should not happen if the switch is used correctly
            std::cerr << "Error: Unexpected traffic light state." << std::endl;
            break;
    }
}

int main() {
    respondToTrafficLight(TrafficLight::Red);     // Test with red light
    respondToTrafficLight(TrafficLight::Yellow);  // Test with yellow light
    respondToTrafficLight(TrafficLight::Green);   // Test with green light
    
    return 0;
}

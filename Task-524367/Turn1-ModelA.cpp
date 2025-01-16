#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

// This function simulates reading data from a sensor
void readSensorData(int sensorId, std::atomic<bool>& running) {
    while (running) {
        // Simulate a delay in reading sensor data
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Generate random sensor data (for example, a temperature reading)
        int sensorData = rand() % 100; // Just a mock-up value

        // Output the sensor data (consider replacing this with actual processing logic)
        std::cout << "Sensor " << sensorId << " read data: " << sensorData << std::endl;
    }
}

int main() {
    const int numberOfSensors = 5; // Number of sensor streams
    std::atomic<bool> running(true);
    std::vector<std::thread> threads;

    // Start detached threads for each sensor
    for (int i = 0; i < numberOfSensors; ++i) {
        // Create a thread that reads data from a sensor
        std::thread sensorThread(readSensorData, i, std::ref(running));
        // Detach the thread to allow it to run independently
        sensorThread.detach();
    }

    // Run the system for a short period to simulate processing
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Stop all threads
    running = false;

    // Give threads time to finish gracefully
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Shutting down sensor data reading." << std::endl;

    return 0;
}

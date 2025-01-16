#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

// Function to simulate a task processing sensor data
void processSensorData(int streamId, size_t numIterations) {
    std::cout << "Thread " << streamId << " started processing data." << std::endl;

    for (size_t i = 0; i < numIterations; ++i) {
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cout << "Thread " << streamId << " completed processing data." << std::endl;
}

// Class to manage cleanup of detached threads safely
class ThreadManager {
public:
    ~ThreadManager() {
        std::cout << "In ThreadManager destructor, joining all threads." << std::endl;
        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        std::cout << "All threads joined." << std::endl;
    }

    void startThread(std::thread thread) {
        threads.push_back(std::move(thread));
    }

private:
    std::vector<std::thread> threads;
};

int main() {
    ThreadManager threadManager;
    const int numDataStreams = 5;
    const size_t numIterationsPerStream = 10;

    // Create and detach threads to process sensor data concurrently
    for (int streamId = 0; streamId < numDataStreams; ++streamId) {
        std::thread sensorDataThread(processSensorData, streamId, numIterationsPerStream);
        threadManager.startThread(std::move(sensorDataThread));
        sensorDataThread.detach();
    }

    // The main thread continues executing without being blocked
    std::cout << "Main thread doing other tasks..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Main thread finished its tasks." << std::endl;

    return 0;
}

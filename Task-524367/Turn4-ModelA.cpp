#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <chrono>
#include <random>
#include <condition_variable>

std::vector<int> sharedVector; // Shared resource
std::mutex vectorMutex; // Mutex for synchronizing access to sharedVector
std::condition_variable cv; // Condition variable for signaling
std::atomic<int> activeThreads(0); // Counter for active threads
std::atomic<bool> running(true); // Control flag for threads

// Function for processing data by adding numbers to the shared vector
void addData(int threadId) {
    std::default_random_engine generator(threadId); // Random generator seeded with the thread ID
    std::uniform_int_distribution<int> distribution(1, 100);

    // Increment the active thread counter
    activeThreads.fetch_add(1);

    while (running) {
        // Generate random value to add
        int valueToAdd = distribution(generator);
        
        // Lock the mutex before modifying the shared vector
        {
            std::lock_guard<std::mutex> lock(vectorMutex);
            sharedVector.push_back(valueToAdd);
            std::cout << "Thread " << threadId << " added: " << valueToAdd << std::endl;
        }
        
        // Sleep to simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Decrement the active thread counter on exit
    activeThreads.fetch_sub(1);
    cv.notify_one(); // Notify the main thread that a thread has finished execution
}

int main() {
    const int numberOfThreads = 5; // Number of worker threads
    std::vector<std::thread> threads;

    // Start detached threads
    for (int i = 0; i < numberOfThreads; ++i) {
        std::thread worker(addData, i);
        worker.detach(); // Detach the thread to allow independent execution
    }

    // Let the threads run for a short duration
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Signal threads to stop
    running = false;

    // Wait until all threads are finished
    while (activeThreads.load() > 0) {
        // Wait for notification from threads
        std::unique_lock<std::mutex> lock(vectorMutex);
        cv.wait(lock); // Wait until notified
    }

    std::cout << "All worker threads have finished." << std::endl;

    // Print contents of shared vector
    {
        std::lock_guard<std::mutex> lock(vectorMutex);
        std::cout << "Final contents of shared vector:\n";
        for (const int &value : sharedVector) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

std::vector<int> sharedVector; // Shared resource
std::mutex vectorMutex; // Mutex for synchronizing access to sharedVector
std::condition_variable allDone; // Condition variable for thread completion
std::atomic<bool> running(true); // Control flag for threads
std::atomic<int> completedThreads(0); // Counter for completed threads
const int numberOfThreads = 5; // Number of worker threads

void addData(int threadId) {
    std::default_random_engine generator(threadId); // Random generator seeded with thread ID
    std::uniform_int_distribution<int> distribution(1, 100);

    while (running) {
        // Generate random value to add
        int valueToAdd = distribution(generator);
        
        {
            std::lock_guard<std::mutex> lock(vectorMutex);
            sharedVector.push_back(valueToAdd);
            std::cout << "Thread " << threadId << " added: " << valueToAdd << std::endl;
        }

        // Sleep to simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::lock_guard<std::mutex> lock(vectorMutex);
        ++completedThreads;
        if (completedThreads == numberOfThreads) {
            allDone.notify_all(); // Signal that all threads are done
        }
    }
}

int main() {
    std::vector<std::thread> threads;

    // Start detached threads
    for (int i = 0; i < numberOfThreads; ++i) {
        std::thread worker(addData, i);
        worker.detach(); // Detach the thread
    }

    // Let the threads run for a short duration
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Signal threads to stop
    running = false;

    {
        std::unique_lock<std::mutex> lock(vectorMutex);
        allDone.wait(lock, []{ return completedThreads == numberOfThreads; });
    }

    std::cout << "Shutting down worker threads." << std::endl;

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

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding rand()

std::mutex mtx;  // Mutex for thread synchronization
std::vector<int> sharedVector; // Shared data structure

// Function to increment a random element in the shared vector
void incrementElement() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (sharedVector.empty()) {
                continue;
            }
            size_t randomIndex = rand() % sharedVector.size();
            sharedVector[randomIndex]++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// Function to decrement a random element in the shared vector
void decrementElement() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (sharedVector.empty()) {
                continue;
            }
            size_t randomIndex = rand() % sharedVector.size();
            if (sharedVector[randomIndex] > 0) {
                sharedVector[randomIndex]--;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// Function to insert a random element into the shared vector
void insertRandomElement() {
    while (true) {
        int randomValue = rand() % 100;
        {
            std::lock_guard<std::mutex> lock(mtx);
            sharedVector.push_back(randomValue);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed the random number generator
    int numberOfThreads = 6; // Total number of threads
    std::atomic<bool> running(true);
    std::vector<std::thread> threads;

    // Create and detach threads
    for (int i = 0; i < numberOfThreads; ++i) {
        int operationType = rand() % 3; // 0: increment, 1: decrement, 2: insert
        switch (operationType) {
            case 0:
                threads.emplace_back(incrementElement);
                break;
            case 1:
                threads.emplace_back(decrementElement);
                break;
            default:
                threads.emplace_back(insertRandomElement);
        }
        threads.back().detach();
    }

    // Run the system for a short period
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Signal threads to stop
    running = false;

    std::cout << "Shutting down, waiting for threads to complete." << std::endl;

    // Main thread waits for others to finish (since they are detached, this could take a while)
    for (auto& thread : threads) {
        thread.join(); // This can be commented out, but it ensures main will wait for other threads to complete
    }

    // Output the final state of the shared vector
    {
        std::lock_guard<std::mutex> lock(mtx);
        for (int element : sharedVector) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

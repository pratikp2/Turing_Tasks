#include <iostream>
#include <thread>
#include <vector>

// Define a thread function that takes a priority and an ID as arguments
void thread_function(int priority, int id) {
    std::cout << "Thread " << id << " started with priority " << priority << std::endl;
    // Simulate work by sleeping for a random amount of time
    std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000));
    std::cout << "Thread " << id << " finished" << std::endl;
}

int main() {
    // Set up the priorities for the two threads
    int priority_high = 2;
    int priority_low = 1;

    // Create two threads
    std::vector<std::thread> threads;
    threads.push_back(std::thread(thread_function, priority_high, 1));
    threads.push_back(std::thread(thread_function, priority_low, 2));

    // Check the status of both threads before proceeding with each thread's execution
    for (auto& thread : threads) {
        while (!thread.joinable()) {
            // If the thread is not joinable, yield the current thread's time slice
            std::this_thread::yield();
        }

        // Once the thread is joinable, set its priority
        if (thread.get_id() == threads[0].get_id()) {
            thread.native_handle()->set_priority(priority_high);
        } else {
            thread.native_handle()->set_priority(priority_low);
        }
    }

    // Wait for both threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}

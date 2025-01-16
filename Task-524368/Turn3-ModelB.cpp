#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <chrono>
#include <memory>
#include <vector>

// ... (Previous code remains the same)

void benchmark(const std::string& label, int numMessages, SharedBuffer& buffer, std::function<void()> producerFunction, std::function<void()> consumerFunction) {
    std::cout << "\nRunning " << label << " benchmark with " << numMessages << " messages:\n";

    std::thread prodThread(producerFunction);
    std::thread consThread(consumerFunction);

    auto startTime = std::chrono::high_resolution_clock::now();

    prodThread.join();
    consThread.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Execution time: " << duration.count() << " ms\n";
}

int main() {
    int numMessagesList[] = { 1000, 10000, 100000 };

    for (int numMessages : numMessagesList) {
        SharedBuffer buffer;

        // Benchmark deep copying
        benchmark("Deep Copy", numMessages, buffer,
                [&]() { producer(buffer); },
                [&]() { consumer(buffer); });

        // We could implement shallow copying as follows
        // class ShallowLogMessage {
        //     std::shared_ptr<std::string> message_;
        //     // Implement copy and move operations as shallow copies
        //     // ...
        // };

        //  Note: In this implementation, the buffer holds deep copies of LogMessage even in the shallow copy scenario. 
        //  To properly benchmark shallow copies, we would need to modify the buffer to hold ShallowLogMessage instances. 
        //  For the scope of this demonstration, we'll leave it as is to focus on the impact of deep copying in the buffer management.
    }

    return 0;
}

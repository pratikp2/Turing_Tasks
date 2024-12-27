#include <iostream>
#include <thread>
#include <future>
#include <memory>
#include <chrono>
#include <vector>

class ResourceIntensiveClass {
public:
    ResourceIntensiveClass() {
        std::cout << "Constructing ResourceIntensiveClass...\n";
        // Simulate resource allocation
        data = std::make_unique<std::vector<char>>(100 * 1024 * 1024); // 100 MB
    }

    ~ResourceIntensiveClass() {
        std::cout << "Destructing ResourceIntensiveClass...\n";
    }

    void heavyOperation() {
        std::cout << "Running heavy operation...\n";
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate 5 seconds of work
    }

private:
    std::unique_ptr<std::vector<char>> data;
};

void executeHeavyOperation(std::unique_ptr<ResourceIntensiveClass> obj) {
    obj->heavyOperation();
}

int main() {
    // Regular execution
    std::cout << "Regular execution:\n";
    {
        auto obj = std::make_unique<ResourceIntensiveClass>();
        obj->heavyOperation();
    }

    // Asynchronous execution using std::async
    std::cout << "\nAsynchronous execution using std::async:\n";
    {
        std::future<void> task;
        auto obj = std::make_unique<ResourceIntensiveClass>();
        task = std::async(std::launch::async, executeHeavyOperation, std::move(obj));

        task.wait(); // Wait for the task to complete
    }

    return 0;
}

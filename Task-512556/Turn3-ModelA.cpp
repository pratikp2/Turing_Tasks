#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;

// Observer interface
class IObserver {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~IObserver() = default;
};

// Subject interface
class ISubject {
public:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify(const std::string& message) = 0;
    virtual ~ISubject() = default;
};

// Concrete Subject
class Compiler : public ISubject {
private:
    std::vector<IObserver*> observers;
    std::mutex mtx; // To protect observer manipulation

public:
    void attach(IObserver* observer) override {
        std::lock_guard<std::mutex> guard(mtx);
        observers.push_back(observer);
    }

    void detach(IObserver* observer) override {
        std::lock_guard<std::mutex> guard(mtx);
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& message) override {
        std::lock_guard<std::mutex> guard(mtx);
        for (IObserver* observer : observers) {
            observer->update(message);
        }
    }

    void optimizeMemoryUsage(const std::string& code) {
        std::cout << "Starting memory optimization for: " << code << std::endl;

        // Simulate memory optimization work
        std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Simulate work

        // In a real scenario, determine if any diagnostic messages are required
        bool errorOccurred = false; // For demonstration purposes, we hardcode this value
        if (errorOccurred) {
            notify("Memory optimization failed for: " + code);
        } else {
            notify("Memory optimization completed successfully for: " + code);
        }

        // Further memory optimization logic could go here…
    }
};

// Concrete Observer for Memory Usage
class MemoryUsageMonitor : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Memory Usage Monitor: " << message << std::endl;
    }
};

// Concrete Observer for Error Diagnostics
class DiagnosticsTool : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Diagnostics Tool: " << message << std::endl;
    }
};

// Main function showcasing usage
int main() {
    Compiler compiler;

    MemoryUsageMonitor memoryMonitor;
    DiagnosticsTool diagnostics;

    compiler.attach(&memoryMonitor);
    compiler.attach(&diagnostics);

    std::string codeExample = "int exampleFunc() { return 42; }";
    
    // Run memory optimization
    compiler.optimizeMemoryUsage(codeExample);

    return 0;
}

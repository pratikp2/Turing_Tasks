#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>
#include <memory>

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

// Observer for Memory Usage
class MemoryUsageMonitor : public IObserver {
public:
    void update(const std::string& message) override {
        cout << "Memory Usage Monitor: " << message << endl;
    }
};

// Singleton Observer for Diagnostics
class DiagnosticsTool : public IObserver {
private:
    DiagnosticsTool() = default;  // Private constructor

public:
    // Delete copy constructor and assignment operator
    DiagnosticsTool(const DiagnosticsTool&) = delete;
    DiagnosticsTool& operator=(const DiagnosticsTool&) = delete;

    static DiagnosticsTool& getInstance() {
        static DiagnosticsTool instance;  // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    void update(const std::string& message) override {
        cout << "Diagnostics Tool: " << message << endl;
    }
};

// Factory Pattern for creating observers
class ObserverFactory {
public:
    static unique_ptr<IObserver> createMemoryMonitor() {
        return make_unique<MemoryUsageMonitor>();
    }

    static unique_ptr<IObserver> createDiagnosticsTool() {
        return nullptr; // Returning nullptr because DiagnosticsTool is a Singleton
    }
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
        std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Simulate work

        // Simulated successful optimization
        notify("Memory optimization completed successfully for: " + code);
    }
};

// Main function
int main() {
    Compiler compiler;

    // Create a memory usage monitor using the factory
    auto memoryMonitor = ObserverFactory::createMemoryMonitor();
    compiler.attach(memoryMonitor.get());

    // Attach the diagnostics tool singleton
    compiler.attach(&DiagnosticsTool::getInstance());

    std::string codeExample = "int main() { return 0; }";
    
    // Run memory optimization
    compiler.optimizeMemoryUsage(codeExample);

    return 0;
}

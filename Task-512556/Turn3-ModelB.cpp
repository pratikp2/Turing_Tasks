#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

class Compiler : public ISubject {
private:
    std::vector<IObserver*> observers;

public:
    void attach(IObserver* observer) override {
        observers.push_back(observer);
    }

    void detach(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& message) override {
        for (IObserver* observer : observers) {
            observer->update(message);
        }
    }

    void optimizeMemoryUsage(const std::string& functionName, size_t memorySaved) {
        // Simulate memory optimization in the compiler
        std::cout << "Optimized memory usage in " << functionName << " by " << memorySaved << " bytes." << std::endl;
        notify("Memory optimization: " + functionName + ", " + std::to_string(memorySaved) + " bytes saved");
    }

    void handleError(const std::string& errorMessage) {
        // Simulate detecting an error in the compiler
        std::cout << "Compiler Error: " << errorMessage << std::endl;
        notify("Compiler Error: " + errorMessage);
    }
};

class MemoryOptimizationLogger : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Memory Optimization Logger: " << message << std::endl;
    }
};

class ErrorDiagnosticsHandler : public IObserver {
public:
    void update(const std::string& message) override {
        // Handle errors, such as logging to a file or triggering alerts
        std::cout << "Error Diagnostics Handler: " << message << std::endl;
    }
};

int main() {
    Compiler compiler;

    MemoryOptimizationLogger memoryOptimizer;
    ErrorDiagnosticsHandler errorHandler;

    compiler.attach(&memoryOptimizer);
    compiler.attach(&errorHandler);

    compiler.optimizeMemoryUsage("main", 2048);
    compiler.optimizeMemoryUsage("calculate_traffic_data", 4096);
    compiler.handleError("Invalid pointer access detected in process_ui_update");
    
    return 0;
}

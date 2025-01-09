#include <iostream>
#include <vector>
#include <string>
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
    Compiler() = default; // Disable direct instantiation
    static Compiler* instance;

    std::vector<IObserver*> observers;
    std::mutex mtx; // To protect observer manipulation

public:
    static Compiler& getInstance() {
        if (instance == nullptr) {
            instance = new Compiler;
        }
        return *instance;
    }

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
        // ... (Same implementation as before)
    }

    ~Compiler() {
        // Ensure observers are cleaned up (this is optional and depends on your context)
        for (auto* observer : observers) {
            delete observer;
        }
        observers.clear();
    }
};

// Concrete Observer - Management via Singleton
class MemoryUsageMonitor : public IObserver {
private:
    MemoryUsageMonitor() = default; // Disable direct instantiation
    static MemoryUsageMonitor* instance;

public:
    static MemoryUsageMonitor& getInstance() {
        if (instance == nullptr) {
            instance = new MemoryUsageMonitor;
        }
        return *instance;
    }

    void update(const std::string& message) override {
        std::cout << "Memory Usage Monitor: " << message << std::endl;
    }

    ~MemoryUsageMonitor() {
    }
};

// Concrete Observer - Management via Singleton
class DiagnosticsTool : public IObserver {
private:
    DiagnosticsTool() = default;
    static DiagnosticsTool* instance;

public:
    static DiagnosticsTool& getInstance() {
        if (instance == nullptr) {
            instance = new DiagnosticsTool;
        }
        return *instance;
    }

    void update(const std::string& message) override {
        std::cout << "Diagnostics Tool: " << message << std::endl;
    }

    ~DiagnosticsTool() {
    }
};

// Main function showcasing usage
int main() {
    // Attach singleton observers to the compiler
    Compiler& compiler = Compiler::getInstance();
    compiler.attach(&MemoryUsageMonitor::getInstance());
    compiler.attach(&DiagnosticsTool::getInstance());

    std::string codeExample = "int exampleFunc() { return 42; }";

    // Run memory optimization
    compiler.optimizeMemoryUsage(codeExample);

    return 0;
}

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

    void analyzeCode(const std::string& code) {
        // Simulate code analysis
        std::cout << "Analyzing code: " << code << std::endl;
        notify("Code analysis completed for: " + code);
        
        // Simulate optimization
        optimizeCode(code);
    }

    void optimizeCode(const std::string& code) {
        // Simulate optimization process
        std::cout << "Optimizing code: " << code << std::endl;
        notify("Code optimized for: " + code);
    }
};

class DiagnosticsTool : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Diagnostics Tool: " << message << std::endl;
    }
};

class PerformanceMonitor : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Performance Monitor: " << message << std::endl;
    }
};

int main() {
    Compiler compiler;

    DiagnosticsTool diagnostics;
    PerformanceMonitor performanceMonitor;

    compiler.attach(&diagnostics);
    compiler.attach(&performanceMonitor);

    compiler.analyzeCode("int main() { return 0; }");
    
    return 0;
}

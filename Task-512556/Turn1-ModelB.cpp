#include <iostream>
#include <vector>

class Subject {
public:
    void attach(Observer* observer) { observers.push_back(observer); }
    void notifyAllObservers() {
        for (auto observer : observers) {
            observer->update();
        }
    }
    void setChanged() { changed = true; }
    bool isChanged() { return changed; }
    void clearChanged() { changed = false; }

protected:
    std::vector<Observer*> observers;
    bool changed = false;
};

class Observer {
public:
    virtual void update() = 0;
};

class CodeAnalyzer : public Observer {
public:
    CodeAnalyzer(Subject* subject) : subject(subject) { subject->attach(this); }
    void update() override {
        analyzeCode();
    }
    void analyzeCode() {
        std::cout << "CodeAnalyzer: Performing real-time code analysis..." << std::endl;
    }

private:
    Subject* subject;
};

class OptimizationPass : public Observer {
public:
    OptimizationPass(Subject* subject) : subject(subject) { subject->attach(this); }
    void update() override {
        runOptimization();
    }
    void runOptimization() {
        std::cout << "OptimizationPass: Running real-time optimization..." << std::endl;
    }

private:
    Subject* subject;
};

int main() {
    Subject* compilerState = new Subject();

    CodeAnalyzer* codeAnalyzer = new CodeAnalyzer(compilerState);
    OptimizationPass* optimizationPass = new OptimizationPass(compilerState);

    compilerState->setChanged();
    compilerState->notifyAllObservers();

    delete codeAnalyzer;
    delete optimizationPass;
    delete compilerState;

    return 0;
}

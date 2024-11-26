#include <iostream>
#include <vector>
#include <queue>

class Task {
public:
    virtual void run() = 0;
    int priority;
    Task(int priority_) : priority(priority_) {}
};

class HighPriorityTask : public Task {
public:
    void run() override {
        std::cout << "Running HighPriorityTask" << std::endl;
    }
};

class LowPriorityTask : public Task {
public:
    void run() override {
        std::cout << "Running LowPriorityTask" << std::endl;
    }
};

class Scheduler {
private:
    std::queue<Task*> readyQueue;

public:
    void enqueueTask(Task* task) {
        readyQueue.push(task);
        std::sort(readyQueue.begin(), readyQueue.end(), [](Task* a, Task* b) {
            return a->priority > b->priority;
        });
    }

    void dequeueAndRunTask() {
        if (!readyQueue.empty()) {
            Task* task = readyQueue.front();
            readyQueue.pop();
            task->run();
            delete task;
        }
    }
};

void contextSwitch(Scheduler* scheduler) {
    // Simulate context switch - in real systems, ISRs would handle this.
    scheduler->dequeueAndRunTask();
}

int main() {
    Scheduler scheduler;

    // Create tasks and enqueue them
    HighPriorityTask* highTask = new HighPriorityTask(1);
    LowPriorityTask* lowTask = new LowPriorityTask(0);
    
    scheduler.enqueueTask(highTask);
    scheduler.enqueueTask(lowTask);

    // Simulate a run loop with context switching
    for (int i = 0; i < 5; ++i) {
        // High priority task runs first
        contextSwitch(&scheduler);
        
        // Low priority task runs after
        contextSwitch(&scheduler);
    }

    return 0;
}
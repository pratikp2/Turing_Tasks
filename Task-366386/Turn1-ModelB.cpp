 #include <iostream>
 #include <thread>
 #include <atomic>
 #include <chrono>
 
 using namespace std;
 
 constexpr size_t TASK_COUNT = 4;
 constexpr size_t TASK_PERIOD = 100;  // in milliseconds
 
 atomic<bool> tasks_running{true};
 
 void task1() {
    while (tasks_running) {
        // Do some work
        this_thread::sleep_for(chrono::milliseconds(TASK_PERIOD));
    }
 }
 
 void task2() {
    while (tasks_running) {
        // Do some work
        this_thread::sleep_for(chrono::milliseconds(TASK_PERIOD));
    }
 }
 
 void task3() {
    while (tasks_running) {
        // Do some work
        this_thread::sleep_for(chrono::milliseconds(TASK_PERIOD));
    }
 }
 
 void task4() {
    while (tasks_running) {
        // Do some work
        this_thread::sleep_for(chrono::milliseconds(TASK_PERIOD));
    }
 }
 
 int main() {
    // Create threads for each task
    thread tasks[TASK_COUNT];
    tasks[0] = thread(task1);
    tasks[1] = thread(task2);
    tasks[2] = thread(task3);
    tasks[3] = thread(task4);
 
    // Run tasks for a specified duration
    this_thread::sleep_for(chrono::seconds(5));
    tasks_running = false;
 
    // Join threads to ensure clean exit
    for (auto& task : tasks) {
        task.join();
    }
 
    return 0;
 }
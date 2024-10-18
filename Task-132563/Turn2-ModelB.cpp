
#include <iostream>
#include <chrono>
#include <unordered_map>

// Function 1 to be measured
void compute_heavy_task1(int n) {
    // Simulate heavy computation
    for (int i = 0; i < n; i++) {
        double a = 1.23, b = 4.56, c = 7.89;
        a = a * b + c;
        b = b / a * c;
    }
}

// Function 2 to be measured
void compute_heavy_task2(int n) {
    // Simulate some more heavy computation
    for (int i = 0; i < n; i++) {
        // ... more computation here
    }
}

int main() {
    int task_size = 100000; // Adjust this as needed
    std::unordered_map<std::string, double> execution_times;

    // Use steady_clock for precise timing
    std::chrono::steady_clock::time_point start, end;

    // Start timing Function 1
    start = std::chrono::steady_clock::now();
    compute_heavy_task1(task_size);
    end = std::chrono::steady_clock::now();
    execution_times["compute_heavy_task1"] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Start timing Function 2
    start = std::chrono::steady_clock::now();
    compute_heavy_task2(task_size);
    end = std::chrono::steady_clock::now();    
    execution_times["compute_heavy_task2"] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Display the execution times for each function
    for (const auto& entry : execution_times) {
        std::cout << "Function: " << entry.first << ", Execution time: " << entry.second << " milliseconds" << std::endl;
    }

    return 0;
}  

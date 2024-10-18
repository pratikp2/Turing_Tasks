#include <iostream>
#include <chrono>

// Function to be measured
void compute_heavy_task(int n) {
    for (int i = 0; i < n; i++) {
        // Simulate heavy computation by doing some dummy arithmetic
        for (int j = 0; j < 10000; j++) {
            double a = 1.23, b = 4.56, c = 7.89;
            a = a * b + c;
            b = b / a * c;
        }
    }
}

int main() {
    int task_size = 100000; // Adjust this as needed

    // Use steady_clock for precise timing
    std::chrono::steady_clock::time_point start, end;

    // Measure the time taken by the heavy task
    start = std::chrono::steady_clock::now();
    compute_heavy_task(task_size);
    end = std::chrono::steady_clock::now();

    // Calculate the execution time in milliseconds
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Execution time: " << time_taken << " milliseconds" << std::endl;

    // Print the result to analyze the performance
    return 0;
}

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Simulate a critical financial calculation function
double criticalCalculation(double input) {
    // Sleep for a random duration to simulate calculation time
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500));
    return input * 2.0;
}

// Failover function that takes over when the primary calculation fails
double failoverCalculation(double input) {
    // Simulate a slower failover calculation
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return input * 1.8;
}

// Monitoring thread function
void monitorSystemHealth(std::atomic<bool>& stopFlag, std::atomic<bool>& calculationFailed) {
    while (!stopFlag) {
        // Simulate monitoring check every 500 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Check for any condition that indicates calculation failure (e.g., high error rate, timeout)
        // For this example, we'll just randomly set the flag
        calculationFailed = (rand() % 10 == 0);
    }
}

int main() {
    std::atomic<bool> stopFlag(false);
    std::atomic<bool> calculationFailed(false);

    // Launch the monitoring thread
    std::thread monitorThread(monitorSystemHealth, std::ref(stopFlag), std::ref(calculationFailed));

    double inputValue = 100.0;
    double result;

    while (!stopFlag) {
        if (!calculationFailed) {
            // Primary calculation
            result = criticalCalculation(inputValue);
        } else {
            // Failover calculation
            std::cout << "Failover activated..." << std::endl;
            result = failoverCalculation(inputValue);
        }

        // Process the result
        std::cout << "Result: " << result << std::endl;

        // Simulate some work and then check again
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    // Stop the monitoring thread
    stopFlag = true;
    monitorThread.join();

    return 0;
}
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <vector>
#include <algorithm> // for sort
#include <unistd.h> // for usleep (only for Unix-like systems)

const int NUM_ITERATIONS = 1000000; // Number of iterations for performance testing

// ... (Other functions remain the same)

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Performance profiling section
    std::cout << "\nPerformance Profiling:\n";

    // Measure the time taken for environmental condition checks
    clock_t start, end;
    double time_spent;

    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        // Gather readings from multiple sensors (redundancy)
        std::vector<int> temperatureReadings(3);
        std::vector<int> humidityReadings(3);

        for (int j = 0; j < 3; ++j) {
            temperatureReadings[j] = getTemperatureReading();
            humidityReadings[j] = getHumidityReading();
        }

        int temperature = getMedian(temperatureReadings);
        int humidity = getMedian(humidityReadings);

        int conditionFlags = checkEnvironmentalConditions(temperature, humidity);
    }
    end = clock();

    time_spent = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken for " << NUM_ITERATIONS << " iterations: " 
              << time_spent << " seconds" << std::endl;

    // Simulate real-time execution delay for demonstration
    usleep(200000); // Sleep for 200 microseconds

    return 0;
}

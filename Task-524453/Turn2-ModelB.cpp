#include <iostream>
#include <ctime>
#include <random>

#define NUM_SENSORS 1000
#define NUM_TIMESTEPS 10000
#define DATA_SIZE (NUM_SENSORS * NUM_TIMESTEPS)

int main() {
    MemoryPool pool(DATA_SIZE * 16); // 16 bytes per data point (assuming float + padding)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    float* temperatures = static_cast<float*>(pool.allocate(DATA_SIZE * sizeof(float)));
    float* pressures = static_cast<float*>(pool.allocate(DATA_SIZE * sizeof(float)));
    float* humidities = static_cast<float*>(pool.allocate(DATA_SIZE * sizeof(float)));

    if (temperatures == nullptr || pressures == nullptr || humidities == nullptr) {
        std::cout << "Memory allocation failed." << std::endl;
        return 1;
    }

    // Generate random data
    std::cout << "Generating random meteorological data..." << std::endl;
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        temperatures[i] = dist(gen);
        pressures[i] = dist(gen);
        humidities[i] = dist(gen);
    }

    // ... Perform simulations and analyses here ...

    // Deallocate memory
    std::cout << "Deallocating memory..." << std::endl;
    pool.deallocate(static_cast<void*>(temperatures));
    pool.deallocate(static_cast<void*>(pressures));
    pool.deallocate(static_cast<void*>(humidities));

    return 0;
}

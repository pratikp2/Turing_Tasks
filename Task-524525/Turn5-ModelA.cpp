#include <iostream>
#include <iomanip>
#include <cstdlib>

// Functions to handle 3D array creation, population, summation, and deallocation

float* createAndPopulateWeatherData(int numCities, int numDays, int numMeasurements) {
    int totalSize = numCities * numDays * numMeasurements;
    float* data = new float[totalSize];

    // Populate the array with sample data
    for (int city = 0; city < numCities; ++city) {
        for (int day = 0; day < numDays; ++day) {
            // Example data: 
            // Temperature between 20 to 30 degrees
            // Humidity between 30% to 50%
            // Wind Speed between 5 to 15 km/h
            *(data + (city * numDays * numMeasurements + day * numMeasurements + 0)) = 20.0f + static_cast<float>(rand() % 11); // Temperature
            *(data + (city * numDays * numMeasurements + day * numMeasurements + 1)) = 30.0f + static_cast<float>(rand() % 21); // Humidity
            *(data + (city * numDays * numMeasurements + day * numMeasurements + 2)) = 5.0f + static_cast<float>(rand() % 11); // Wind Speed
        }
    }

    return data;  // Return pointer to allocated memory
}

void deallocateWeatherData(float* data) {
    delete[] data;  // Deallocate memory
}

float calculateSumOfWeatherData(float* data, int numCities, int numDays, int numMeasurements) {
    if (data == nullptr) {
        std::cerr << "Error: Null pointer passed to calculateSumOfWeatherData." << std::endl;
        return 0.0f;  // Return 0 or handle as needed
    }

    float sum = 0.0f;
    int totalSize = numCities * numDays * numMeasurements;

    for (int i = 0; i < totalSize; ++i) {
        sum += *(data + i);  // Access elements using pointer arithmetic
    }

    return sum;
}

void printWeatherData(float* data, int numCities, int numDays, int numMeasurements) {
    const char* measurementNames[] = {"Temperature (°C)", "Humidity (%)", "Wind Speed (km/h)"};

    for (int city = 0; city < numCities; ++city) {
        std::cout << "City " << (city + 1) << " Weather Data:" << std::endl;
        for (int day = 0; day < numDays; ++day) {
            std::cout << "  Day " << (day + 1) << ": ";
            for (int measure = 0; measure < numMeasurements; ++measure) {
                std::cout << std::fixed << std::setprecision(2)
                          << measurementNames[measure] << " = "
                          << *(data + (city * numDays * numMeasurements + day * numMeasurements + measure)) << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    const int numCities = 3;     // Number of cities
    const int numDays = 7;       // Number of days (one week)
    const int numMeasurements = 3; // 3 types of weather data (temperature, humidity, wind speed)

    // Create and populate the weather data array
    float* weatherData = createAndPopulateWeatherData(numCities, numDays, numMeasurements);

    // Print the populated weather data
    printWeatherData(weatherData, numCities, numDays, numMeasurements);

    // Calculate sums of each measurement type across all cities and days
    float totalTemperature = 0.0f;
    float totalHumidity = 0.0f;
    float totalWindSpeed = 0.0f;

    for (int measure = 0; measure < numMeasurements; ++measure) {
        totalTemperature += calculateSumOfWeatherData(weatherData + measure, numCities, numDays, numMeasurements);
        // Recalculate the right position for humidity and wind speed in the flattened array
        if (measure == 1) {
            totalHumidity = calculateSumOfWeatherData(weatherData + 1, numCities, numDays, numMeasurements);
        } else if (measure == 2) {
            totalWindSpeed = calculateSumOfWeatherData(weatherData + 2, numCities, numDays, numMeasurements);
        }
    }

    // Print the total sums
    std::cout << "\nTotal Weather Data for the week for all cities:" << std::endl;
    std::cout << "Total Temperature: " << totalTemperature << " °C" << std::endl;
    std::cout << "Total Humidity: " << totalHumidity << " %" << std::endl;
    std::cout << "Total Wind Speed: " << totalWindSpeed << " km/h" << std::endl;

    // Deallocate the memory
    deallocateWeatherData(weatherData);

    return 0;
}

#include <iostream>
#include <iomanip>

float* createAndPopulate3DArray(int cities, int days, int weatherDataTypes) {
    int totalSize = cities * days * weatherDataTypes;
    float* data = new float[totalSize];

    // Sample weather data: temperature, humidity, wind speed
    const float averageTemperature = 25.0f;
    const float averageHumidity = 60.0f;
    const float averageWindSpeed = 10.0f;

    for (int i = 0; i < cities; ++i) {
        for (int j = 0; j < days; ++j) {
            for (int k = 0; k < weatherDataTypes; ++k) {
                float randomFactor = (static_cast<float>(rand()) / RAND_MAX) * 5.0f - 2.5f;  // Add random variation
                switch (k) {
                    case 0:  // Temperature
                        *(data + (i * days * weatherDataTypes + j * weatherDataTypes + k)) = averageTemperature + randomFactor;
                        break;
                    case 1:  // Humidity
                        *(data + (i * days * weatherDataTypes + j * weatherDataTypes + k)) = averageHumidity + randomFactor;
                        break;
                    case 2:  // Wind speed
                        *(data + (i * days * weatherDataTypes + j * weatherDataTypes + k)) = averageWindSpeed + randomFactor;
                        break;
                    default:
                        std::cerr << "Invalid weather data type index." << std::endl;
                        return nullptr;
                }
            }
        }
    }

    return data;  // Return the pointer to the allocated memory
}

void deallocate3DArray(float* data) {
    delete[] data;  // Deallocate the memory
}

float calculateSumOf3DArray(float* data, int cities, int days, int weatherDataTypes) {
    if (data == nullptr) {
        std::cerr << "Error: Null pointer passed to calculateSumOf3DArray." << std::endl;
        return 0.0f;
    }

    float sum = 0.0f;
    int totalSize = cities * days * weatherDataTypes;

    for (int i = 0; i < totalSize; ++i) {
        sum += *(data + i);
    }

    return sum;
}

void print3DArray(float* data, int cities, int days, int weatherDataTypes) {
    std::cout << "Weather Data:" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    for (int i = 0; i < cities; ++i) {
        std::cout << "City " << i + 1 << ":" << std::endl;
        for (int j = 0; j < days; ++j) {
            std::cout << "  Day " << j + 1 << ":" << std::endl;
            for (int k = 0; k < weatherDataTypes; ++k) {
                switch (k) {
                    case 0:
                        std::cout << "    Temperature: ";
                        break;
                    case 1:
                        std::cout << "    Humidity: ";
                        break;
                    case 2:
                        std::cout << "    Wind Speed: ";
                        break;
                    default:
                        std::cerr << "Invalid weather data type index." << std::endl;
                        return;
                }
                std::cout << std::fixed << std::setprecision(2)
                          << *(data + (i * days * weatherDataTypes + j * weatherDataTypes + k)) << " °C" << std::endl;
            }
        }
    }
    std::cout << "-----------------------------------" << std::endl;
}

int main() {
    const int numCities = 3;
    const int numDays = 5;
    const int numWeatherDataTypes = 3;  // Temperature, Humidity, Wind Speed

    // Create and populate the 3D array with weather data
    float* weatherData = createAndPopulate3DArray(numCities, numDays, numWeatherDataTypes);

    if (weatherData == nullptr) {
        std::cerr << "Error creating weather data array." << std::endl;
        return 1;
    }

    // Print the populated weather data
    print3DArray(weatherData, numCities, numDays, numWeatherDataTypes);

    // Calculate the sum of all weather data elements
    float totalWeatherDataSum = calculateSumOf3DArray(weatherData, numCities, numDays, numWeatherDataTypes);

    std::cout << "\nTotal sum of all weather data elements: " << totalWeatherDataSum << std::endl;

    // Deallocate the memory
    deallocate3DArray(weatherData);

    return 0;
}

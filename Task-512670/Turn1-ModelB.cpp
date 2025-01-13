#include <iostream>
#include <bitset>


using namespace std;

// Define the bit structure for holding environmental data
struct EnvironmentalData {
    bitset<4> temperature_coarse;
    bitset<3> humidity_coarse;
    bitset<4> air_quality_fine;

    // Fine resolution quality can be stored like this if it is of 4 bits
    unsigned int air_quality_coarse: 2; 
};

//Function to store data
EnvironmentalData storeEnvironmentalData(short temperature, char humidity, char airQuality)
{
    EnvironmentalData data;

    // Input data ranges and corresponding coarse bit positions:
    const int temp_min = 0;
    const int temp_max = 15;
    const int hum_min = 0;
    const int hum_max = 7;
    const int air_qual_fine_min = 0;
    const int air_qual_fine_max = 15;
    const int air_qual_coarse_min = 0;
    const int air_qual_coarse_max = 3;


    if (temperature < temp_min || temperature > temp_max) {
        cerr << "Temperature is out of range (" << temp_min << "-" << temp_max << "): " << temperature << endl;
        return data; // Or you can handle the error more gracefully
    }
    
    data.temperature_coarse = temperature - temp_min;

    if (humidity < hum_min || humidity > hum_max) {
        cerr << "Humidity is out of range (" << hum_min << "-" << hum_max << "): " << humidity << endl;
        return data; // Or you can handle the error more gracefully.
    }
 
    data.humidity_coarse = humidity - hum_min;
    
    if (airQuality < air_qual_fine_min || airQuality > air_qual_fine_max) {
        cerr << "Air quality (fine) is out of range (" << air_qual_fine_min << "-" << air_qual_fine_max << "): " << airQuality << endl;
        return data; // Or you can handle the error more gracefully.
    }

    data.air_quality_fine = airQuality - air_qual_fine_min;
    
    //  Obtain the coarse air quality from the fine one
    data.air_quality_coarse = (airQuality >> 2) & 0x03;
   
    return data;
}

// Function to retrieve data
void retrieveEnvironmentalData(const EnvironmentalData& data)
{
   cout << "Temperature Coarse: " << static_cast<int>(data.temperature_coarse.to_ulong()) + temp_min << endl;
    cout << "Humidity Coarse: " << static_cast<int>(data.humidity_coarse.to_ulong()) + hum_min << endl; 
    cout << "Air Quality Fine: " << static_cast<int>(data.air_quality_fine.to_ulong()) + air_qual_fine_min << endl; 
    cout << "Air Quality Coarse: " << static_cast<int>(data.air_quality_coarse) + air_qual_coarse_min << endl;
}

int main()
{
    short temperature = 10;
    char humidity = 5;
    char airQuality = 12;

    EnvironmentalData envData = storeEnvironmentalData(temperature, humidity, airQuality);

    retrieveEnvironmentalData(envData);

    return 0;
}

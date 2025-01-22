// Function to check the status of multiple sensors using bitwise operations
//
// The status of each sensor is encoded into a single integer using its position in the integer as its bit index.
// The lower bits correspond to the status of lower numbered sensors.
//
// This method can reduce memory usage compared to storing the status of each sensor in a separate variable.
// It can also reduce the number of read operations needed to check the status of multiple sensors.

// Example: If the status integer is 0x05, this means that the 0th and the 2nd sensors (the least significant bit and the third bit from the least significant bit) are set (active), and all the other sensors are off.

#include <stdint.h>

#define SENSOR_COUNT 8

uint8_t sensor_status = 0;


void update_sensor_status(uint8_t sensor_index, uint8_t status)
{
    // Set or clear the corresponding bit in the sensor_status integer based on the status

    // Ensure that sensor_index is valid
    if (sensor_index >= SENSOR_COUNT)
    {
        // Implement appropriate error handling, such as logging an error or using an assertion.
        // For example:
        
        //Assert in debug builds
        #ifdef NDEBUG
        return;
        #else
        static_assert(sensor_index >= SENSOR_COUNT, "Sensor index is out of range");
        return;
        #endif

        
        //return;
    }

    const uint8_t sensor_mask = (1U << sensor_index);

    if (status)
    {
        // Set the bit
        sensor_status |= sensor_mask;
    }
    else
    {
        // Clear the bit
        sensor_status &= ~sensor_mask;
    }
}

uint8_t get_sensor_status(uint8_t sensor_index)
{
    // Ensure that sensor_index is valid
    if (sensor_index >= SENSOR_COUNT)
    {
        // Assert in debug builds
        #ifdef NDEBUG
        return 0;
        #else
        static_assert(sensor_index < SENSOR_COUNT, "Sensor index is out of range");
        return 0;
        #endif
        
        
        //return 0;
    }

    const uint8_t sensor_mask = (1U << sensor_index);
    return (sensor_status & sensor_mask) != 0;
}

// Example usage:
int main() {
    update_sensor_status(0, 1); // Set sensor 0 as active
    update_sensor_status(3, 1); // Set sensor 3 as active
    update_sensor_status(5, 0); // Set sensor 5 as inactive

    // Check sensor status
    if (get_sensor_status(0)) {
        // Sensor 0 is active
    }

    if (get_sensor_status(3)) {
        // Sensor 3 is active
    }

    if (get_sensor_status(5)) {
        // Sensor 5 is inactive
    }

    return 0;
}

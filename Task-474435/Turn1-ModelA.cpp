#include <stdio.h>

#define MAX_SPEED_KMH 80      // Maximum speed in km/h
#define DISTANCE_UNIT_METERS 1000  // Distance unit in meters
#define TIME_INTERVAL_MINUTES 30    // Time interval for scheduling in minutes

// Function to calculate the time needed to cover a certain distance
double calculate_time(double distance) {
    // Using the MAX_SPEED_KMH constant for calculations
    return distance / (MAX_SPEED_KMH / 60.0); // Convert speed to minutes
}

// Function to convert distance to the number of time intervals
int calculate_intervals(double distance) {
    // Using DISTANCE_UNIT_METERS to convert distance
    return (int)(distance / DISTANCE_UNIT_METERS) + 1; // +1 for partial intervals
}

int main() {
    double distance = 23500; // Distance in meters

    double time_needed = calculate_time(distance);
    int intervals = calculate_intervals(distance);

    printf("Time needed to cover %.0f meters: %.2f minutes\n", distance, time_needed);
    printf("Number of time intervals needed: %d\n", intervals);

    return 0;
}

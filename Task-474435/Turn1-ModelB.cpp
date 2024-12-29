#include <stdio.h>

// Define constants using #define
#define HIGHWAY_WEIGHT 1.0
#define CITY_ROAD_WEIGHT 1.5
#define RESIDENTIAL_ROAD_WEIGHT 2.0
#define MAX_DISTANCE_THRESHOLD 1000.0  // Maximum distance allowed for a route

double calculateDistance(double x1, double y1, double x2, double y2, char roadType) {
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    // Apply weight based on road type
    switch (roadType) {
        case 'H':
            distance *= HIGHWAY_WEIGHT;
            break;
        case 'C':
            distance *= CITY_ROAD_WEIGHT;
            break;
        case 'R':
            distance *= RESIDENTIAL_ROAD_WEIGHT;
            break;
        default:
            printf("Invalid road type: %c\n", roadType);
            return -1.0;
    }

    return distance;
}

int main() {
    double x1, y1, x2, y2;
    char roadType;

    printf("Enter coordinates of location 1: ");
    scanf("%lf %lf", &x1, &y1);

    printf("Enter coordinates of location 2: ");
    scanf("%lf %lf", &x2, &y2);

    printf("Enter road type (H: Highway, C: City Road, R: Residential Road): ");
    scanf(" %c", &roadType);

    double distance = calculateDistance(x1, y1, x2, y2, roadType);

    if (distance != -1.0) {
        printf("Distance between locations: %.2lf\n", distance);

        // Check if the distance is within the threshold
        if (distance <= MAX_DISTANCE_THRESHOLD) {
            printf("Route is valid within the distance threshold.\n");
        } else {
            printf("Route exceeds the distance threshold.\n");
        }
    }

    return 0;
}

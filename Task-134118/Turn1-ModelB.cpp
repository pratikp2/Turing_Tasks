// Calculates the area of a circle based on the user-provided radius.

#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

// Function to calculate the area of a circle
double calculateArea(double radius) {
    // Check if the radius is negative
    if (radius < 0) {
        throw invalid_argument("Radius cannot be negative.");
    }

    const double pi = 3.14;
    return pi * radius * radius;
}

int main() {
    double radius;

    // User input for radius
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    // Input validation
    if (!cin) {
        cout << "Invalid input for radius. Please enter a numeric value." << endl;
        return 1;
    }

    try {
        // Calculate the area and display the result
        double area = calculateArea(radius);
        cout << "The area of the circle with a radius of " << radius << " is: " << area << endl;
    } catch (const invalid_argument& e) {
        // Handle negative radius exception
        cout << "Error: " << e.what() << endl;
    } catch (const exception& e) {
        // Handle any other unexpected exceptions
        cout << "An unexpected error occurred: " << e.what() << endl;
    }

    return 0;
}
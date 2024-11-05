#include <iostream>
#include <vector>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Function to generate the next state based on the current state and the transition matrix
int generateNextState(int currentState, const Matrix2d& transitionMatrix) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    double randomValue = dis(gen);

    double cumulativeProbability = 0.0;
    if (currentState == 0) {
        cumulativeProbability += transitionMatrix(0, 0);
        if (randomValue < cumulativeProbability) {
            return 0; // Stay sunny
        } else {
            return 1; // Become rainy
        }
    } else {
        cumulativeProbability += transitionMatrix(1, 0);
        if (randomValue < cumulativeProbability) {
            return 0; // Become sunny
        } else {
            return 1; // Stay rainy
        }
    }
}

int main() {
    // Transition probability matrix
    Matrix2d transitionMatrix = << 0.8, 0.2 >>,
                                 << 0.3, 0.7 >>;

    int numDays = 10; // Number of time steps (days)
    int initialState = 0; // Initial state: 0=Sunny, 1=Rainy

    vector<int> weatherStates;
    weatherStates.push_back(initialState);

    for (int day = 1; day < numDays; ++day) {
        int nextState = generateNextState(weatherStates.back(), transitionMatrix);
        weatherStates.push_back(nextState);
    }

    // Display the weather forecast
    cout << "Weather Forecast for " << numDays << " days:" << endl;
    for (size_t i = 0; i < weatherStates.size(); ++i) {
        cout << "Day " << i + 1 << ": " << (weatherStates[i] == 0 ? "Sunny" : "Rainy") << endl;
    }

    return 0;
}

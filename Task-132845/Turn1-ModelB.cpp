#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace std;
using Eigen::MatrixXd;

// Simple Markov Chain for data state transitions
class MarkovChain {
public:
    MarkovChain(const MatrixXd& transitionMatrix) : transitionMatrix(transitionMatrix) {
        // Check for stochasticity
        for (int i = 0; i < transitionMatrix.rows(); ++i) {
            assert(abs(transitionMatrix.row(i).sum() - 1.0) < 0.0001);
        }
    }

    int step(int currentState) {
        // Generate a random number based on the current state probabilities
        boost::random::random_device rd;
        boost::random::mt19937 gen(rd());
        boost::random::uniform_int_distribution<> dist(0, transitionMatrix.cols() - 1);

        double cumulativeSum = 0.0;
        for (int i = 0; i < transitionMatrix.cols(); ++i) {
            cumulativeSum += transitionMatrix(currentState, i);
            if (dist(gen) < cumulativeSum) {
                return i;
            }
        }

        // This should never be reached, but returning something anyway
        return transitionMatrix.cols() - 1;
    }

private:
    MatrixXd transitionMatrix;
};

// Function to generate a simulated time series of data states
vector<int> generateTimeSeries(MarkovChain& chain, int initialState, int numSteps) {
    vector<int> timeSeries;
    timeSeries.push_back(initialState);

    for (int i = 1; i < numSteps; ++i) {
        int newState = chain.step(timeSeries[i - 1]);
        timeSeries.push_back(newState);
    }

    return timeSeries;
}

int main() {
    // Example transition matrix for a simple 3-state system
    MatrixXd transitionMatrix = (MatrixXd<<
        0.8, 0.1, 0.1,
        0.2, 0.7, 0.1,
        0.1, 0.2, 0.7
    >>);

    MarkovChain chain(transitionMatrix);
    int initialState = 0;  // Starting state
    int numSteps = 100;     // Generate 100 time steps

    vector<int> timeSeries = generateTimeSeries(chain, initialState, numSteps);

    cout << "Generated Time Series: " << endl;
    for (int state : timeSeries) {
        cout << state << " ";
    }
    cout << endl;

    return 0;
}

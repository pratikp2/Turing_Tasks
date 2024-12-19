#include <iostream>
using namespace std;

// Number of features
const int NUM_FEATURES = 8;

// Define a struct to represent a sample with binary features
struct Sample {
    unsigned int features;
};

// Function to initialize a sample with given features
Sample initializeSample(const vector<bool>& features) {
    Sample sample;
    sample.features = 0;

    // Set the corresponding bits in 'features' based on the input array
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (features[i]) {
            sample.features |= (1 << i);
        }
    }
    return sample;
}

// Function to check if a sample contains a specific set of features using bitwise AND
bool containsFeatures(const Sample& sample, unsigned int requiredFeatures) {
    return (sample.features & requiredFeatures) == requiredFeatures;
}

int main() {
    vector<bool> sampleFeatures1 = {true, false, true, false, true, false, false, true};
    vector<bool> sampleFeatures2 = {false, true, false, true, false, true, true, false};

    Sample sample1 = initializeSample(sampleFeatures1);
    Sample sample2 = initializeSample(sampleFeatures2);

    // Define a set of required features for a prediction
    const unsigned int requiredFeaturesForPrediction = (1 << 0) | (1 << 2) | (1 << 4) | (1 << 7);

    cout << "Sample 1 Features: ";
    for (int i = 0; i < NUM_FEATURES; i++) {
        if ((sample1.features & (1 << i)) != 0) {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }
    cout << endl;

    cout << "Sample 2 Features: ";
    for (int i = 0; i < NUM_FEATURES; i++) {
        if ((sample2.features & (1 << i)) != 0) {
            cout << "1 ";
        } else {
            cout << "0 ";
        }
    }
    cout << endl;

    cout << "Prediction for Sample 1: " << (containsFeatures(sample1, requiredFeaturesForPrediction) ? "True" : "False") << endl;
    cout << "Prediction for Sample 2: " << (containsFeatures(sample2, requiredFeaturesForPrediction) ? "True" : "False") << endl;

    return 0;
}

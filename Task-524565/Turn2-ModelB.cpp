#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef unsigned char Pixel;

// Define a struct to represent a pixel and its feature (in this case, the feature will be the pixel value itself)
struct PixelFeature {
    Pixel value;
    Pixel feature;
};

// Distance calculation function for nearest neighbor
double euclideanDistance(const PixelFeature& p1, const PixelFeature& p2) {
    return std::sqrt(static_cast<double>(p1.feature - p2.feature) * static_cast<double>(p1.feature - p2.feature));
}

void gaussianBlur(const std::vector<std::vector<Pixel>>& inputImage, std::vector<std::vector<Pixel>>& outputImage) {
    // Gaussian blur implementation
    // ... (Same as before, but using vectors)
}

void supervisedRestoration(
    const std::vector<std::vector<Pixel>>& damagedInput,
    const std::vector<std::vector<Pixel>>& correspondingRestored,
    std::vector<std::vector<Pixel>>& outputRestored,
    int k = 1
) {
    int width = damagedInput.size();
    int height = damagedInput[0].size();

    // Generate features for the damaged input image
    std::vector<PixelFeature> features;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            features.push_back({damagedInput[y][x], damagedInput[y][x]});
        }
    }

    // Flatten the restored images to make them suitable for NN search
    std::vector<Pixel> restoredValues;
    for (const auto& row : correspondingRestored) {
        restoredValues.insert(restoredValues.end(), row.begin(), row.end());
    }

    // Now, restore the new image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            PixelFeature nearestNeighbor = {0, 0};
            double minDistance = std::numeric_limits<double>::max();

            // Find the nearest neighbor in the feature space
            for (const auto& feature : features) {
                double distance = euclideanDistance({damagedInput[y][x], damagedInput[y][x]}, feature);
                if (distance < minDistance) {
                    nearestNeighbor = feature;
                    minDistance = distance;
                }
            }

            // Predict the restored pixel value using the nearest neighbor
            int index = static_cast<int>(nearestNeighbor.value);
            outputRestored[y][x] = restoredValues[index];
        }
    }
}

int main() {
    // Example: assume we have the following training pairs
    int width = 5, height = 5;

    // Sample training data
    std::vector<std::vector<Pixel>> damagedTrainingImages{
        {{0, 10, 20, 30, 40}, {50, 60, 70, 80, 90}, {100, 110, 120, 130, 140}, {150, 160, 170, 180, 190}, {200, 210, 220, 230, 240}},
        {{10, 20, 30, 40, 50}, {60, 70, 80, 90, 100}, {110, 120, 130, 140, 150}, {160, 170, 180, 190, 200}, {210, 220, 230, 240, 255}}
    };

    std::vector<std::vector<Pixel>> restoredTrainingImages{
        {{10, 15, 20, 25, 30}, {40, 50, 60, 70, 80}, {90, 100, 110, 120, 130}, {140, 150, 160, 170, 180}, {190, 200, 210, 220, 230}},
        {{20, 30, 40, 50, 60}, {70, 80, 90, 100, 110}, {120, 130, 140, 150, 160}, {170, 180, 190, 200, 210}, {220, 230, 240, 250, 255}}
    };
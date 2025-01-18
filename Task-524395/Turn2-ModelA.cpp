#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to apply a basic median filter
void applyMedianFilter(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            vector<int> neighbors;

            for (int k = -offset; k <= offset; ++k) {
                for (int l = -offset; l <= offset; ++l) {
                    int ni = i + k;
                    int nj = j + l;

                    // Collect neighbor values if within bounds
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
            }

            // Apply the median filter
            sort(neighbors.begin(), neighbors.end());
            outputImage[i][j] = neighbors[neighbors.size() / 2]; 
        }
    }
}

// Function to apply an Adaptive Median Filter
void applyAdaptiveMedianFilter(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int maxFilterSize) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();

    // Max filter sizes can be regulated (e.g., 3, 5, 7)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outputImage[i][j] = inputImage[i][j]; // Default copy
            for (int s = 1; s <= maxFilterSize / 2; s += 1) {
                int left = max(i - s, 0);
                int right = min(i + s, rows - 1);
                int top = max(j - s, 0);
                int bottom = min(j + s, cols - 1);
                
                vector<int> neighbors;
                for (int ni = left; ni <= right; ++ni) {
                    for (int nj = top; nj <= bottom; ++nj) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
                sort(neighbors.begin(), neighbors.end());
                int median = neighbors[neighbors.size() / 2];

                // Check for noise and adapt
                int A1 = neighbors[0];
                int A2 = neighbors[neighbors.size() - 1];
                
                if (A1 < median && median < A2) {
                    outputImage[i][j] = median; // Set pixel to median value if condition satisfies
                    break; // Stop with this filter size
                }
            }
        }
    }
}

// Function to read a grayscale image (simple format assumed)
void readImage(const string& filename, vector<vector<int>>& image, int height, int width) {
    image.resize(height, vector<int>(width));
    ifstream file(filename);
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> image[i][j]; // Assuming space-separated values
        }
    }
}

// Function to write the image back to a file
void writeImage(const string& filename, const vector<vector<int>>& image) {
    ofstream file(filename);
    for (const auto& row : image) {
        copy(row.begin(), row.end(), ostream_iterator<int>(file, " "));
        file << endl;
    }
}

// Main execution program
int main() {
    const string inputFilename = "input.txt";
    const string basicOutputFilename = "output_basic_median.txt";
    const string adaptiveOutputFilename = "output_adaptive_median.txt";
    const int filterSize = 3; // For basic median filter
    const int adaptiveFilterSize = 7; // Max size for Adaptive Filter
    
    // Load the grayscale image
    vector<vector<int>> inputImage;
    readImage(inputFilename, inputImage, 256, 256); // Example dimensions

    // Output image initializations
    vector<vector<int>> outputImageBasic(inputImage.size(), vector<int>(inputImage[0].size(), 0));
    vector<vector<int>> outputImageAdaptive(inputImage.size(), vector<int>(inputImage[0].size(), 0));

    // Apply basic median filter and time it
    auto start = high_resolution_clock::now();
    applyMedianFilter(inputImage, outputImageBasic, filterSize);
    auto end = high_resolution_clock::now();
    auto durationBasic = duration_cast<microseconds>(end - start);
    writeImage(basicOutputFilename, outputImageBasic);
    cout << "Basic Median Filter completed in " << durationBasic.count() << " microseconds." << endl;

    // Apply adaptive median filter and time it
    start = high_resolution_clock::now();
    applyAdaptiveMedianFilter(inputImage, outputImageAdaptive, adaptiveFilterSize);
    end = high_resolution_clock::now();
    auto durationAdaptive = duration_cast<microseconds>(end - start);
    writeImage(adaptiveOutputFilename, outputImageAdaptive);
    cout << "Adaptive Median Filter completed in " << durationAdaptive.count() << " microseconds." << endl;

    return 0;
}

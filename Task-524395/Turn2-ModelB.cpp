#include <iostream>
#include <vector>
#include <algorithm>
#include <heap>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <memory>
#include <chrono>

using namespace std;

// Improved median filter using a max heap (priority queue)
void applyEfficientMedianFilter(const vector<vector<int>>& inputImage,
                                   vector<vector<int>>& outputImage, int filterSize) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            priority_queue<int, vector<int>, greater<int>> neighbors;

            // Collect neighbor values into the max heap
            for (int k = -offset; k <= offset; ++k) {
                for (int l = -offset; l <= offset; ++l) {
                    int ni = i + k;
                    int nj = j + l;

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        if (neighbors.size() < filterSize * filterSize) {
                            neighbors.push(inputImage[ni][nj]);
                        } else if (inputImage[ni][nj] > neighbors.top()) {
                            neighbors.pop();
                            neighbors.push(inputImage[ni][nj]);
                        }
                    }
                }
            }

            // Median is either the top element or the average of the top two
            int median;
            if (neighbors.size() % 2 == 0) {
                median = (neighbors.top() + neighbors.front()) / 2;
                neighbors.pop();
            } else {
                median = neighbors.top();
            }

            outputImage[i][j] = median;
        }
    }
}

// Function to compare performance of different containers
template <typename Container2D>
void runComparison(const string& inputFilename, const string& outputFilename, int filterSize) {
    // Read input image into chosen container
    vector<unique_ptr<Container2D[]>> inputImage;
    readImage<Container2D>(inputFilename, inputImage, 256, 256);

    vector<unique_ptr<Container2D[]>> outputImage(inputImage.size(), make_unique<Container2D[]>(inputImage[0]->size()));

    auto startTime = chrono::high_resolution_clock::now();

    applyEfficientMedianFilter(reinterpret_cast<const vector<vector<int>>&>(inputImage), 
                                   reinterpret_cast<vector<vector<int>>&>(outputImage), filterSize);

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

    cout << "Processing completed in " << duration.count() << " microseconds using " << typeid(Container2D).name() << endl;

    // Write the output image (not needed for benchmarking but kept for demonstration)
    writeImage(outputFilename, outputImage);
}

void readImage<Container2D>(const string& filename, vector<unique_ptr<Container2D[]>>& image, int height, int width) {
    image.resize(height);
    ifstream file(filename);
    for (int i = 0; i < height; ++i) {
        image[i] = make_unique<Container2D[]>(width);
        for (int j = 0; j < width; ++j) {
            file >> image[i][j]; // Assuming space-separated values
        }
    }
}

void writeImage(const string& filename, const vector<unique_ptr<int[]>>& image) {
    ofstream file(filename);
    for (const auto& row : image) {
        copy(row.get(), row.get() + image[0].size(), ostream_iterator<int>(file, " "));
        file << endl;
    }
}

int main() {
    const string inputFilename = "input.txt";
    const string outputFilename = "output.txt";
    const int filterSize = 3; // Size of the median filter

    // Benchmark both vectors and raw arrays
    cout << "\n-- Performance Comparison --\n";
    runComparison<int>(inputFilename, outputFilename, filterSize);
    
    // You can add another test for raw array:
    // runComparison<int[]>(inputFilename, outputFilename, filterSize);

    return 0;
}

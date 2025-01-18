#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <chrono>

using namespace std;
using namespace std::chrono;

void applyMedianFilterSection(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize, int startRow, int endRow) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < cols; ++j) {
            vector<int> neighbors;

            for (int k = -offset; k <= offset; ++k) {
                for (int l = -offset; l <= offset; ++l) {
                    int ni = i + k;
                    int nj = j + l;

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
            }

            sort(neighbors.begin(), neighbors.end());
            outputImage[i][j] = neighbors[neighbors.size() / 2]; // Assign the median value
        }
    }
}

void applyMedianFilterMultithreaded(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize) {
    int numThreads = thread::hardware_concurrency(); // Get the number of available threads
    vector<thread> threads;
    int rows = inputImage.size();
    int rowsPerThread = rows / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? rows : startRow + rowsPerThread; // Handle the last section

        threads.emplace_back(applyMedianFilterSection, ref(inputImage), ref(outputImage), filterSize, startRow, endRow);
    }

    for (auto& th : threads) {
        th.join(); // Wait for all threads to complete
    }
}

void readImage(const string& filename, vector<vector<int>>& image, int height, int width) {
    image.resize(height, vector<int>(width));
    ifstream file(filename);
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> image[i][j]; // Assuming space-separated values
        }
    }
}

void writeImage(const string& filename, const vector<vector<int>>& image) {
    ofstream file(filename);
    for (const auto& row : image) {
        copy(row.begin(), row.end(), ostream_iterator<int>(file, " "));
        file << endl;
    }
}

int main() {
    const string inputFilename = "input.txt";
    const string outputFilename = "output_multithreaded.txt";
    const int filterSize = 3;

    // Load the input grayscale image
    vector<vector<int>> inputImage;
    readImage(inputFilename, inputImage, 256, 256); // Example dimensions

    // Output image initialization
    vector<vector<int>> outputImage(inputImage.size(), vector<int>(inputImage[0].size(), 0));

    // Apply multithreaded median filter and time it
    auto start = high_resolution_clock::now();
    applyMedianFilterMultithreaded(inputImage, outputImage, filterSize);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    
    // Write the output image
    writeImage(outputFilename, outputImage);
    cout << "Multithreaded Median Filter completed in " << duration.count() << " microseconds." << endl;

    return 0;
}

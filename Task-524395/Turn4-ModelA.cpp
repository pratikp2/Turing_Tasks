#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <thread>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <chrono>
#include <memory>

using namespace std;
using namespace std::chrono;

template <typename Container>
void applyMedianFilterSection(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize, int startRow, int endRow) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < cols; ++j) {
            Container neighbors;

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

            sort(neighbors.begin(), neighbors.end());
            outputImage[i][j] = neighbors[neighbors.size() / 2]; // Assign the median value
        }
    }
}

template <typename Container>
void applyMedianFilterMultithreaded(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize) {
    int numThreads = thread::hardware_concurrency(); // Get the number of available threads
    vector<thread> threads;
    int rows = inputImage.size();
    int rowsPerThread = rows / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? rows : startRow + rowsPerThread; // Handle the last section

        threads.emplace_back(applyMedianFilterSection<Container>, ref(inputImage), ref(outputImage), filterSize, startRow, endRow);
    }

    for (auto& th : threads) {
        th.join(); // Wait for all threads to complete
    }
}

void readImage(const string& filename, vector<vector<int>>& image, int& height, int& width) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open the file!");
    }

    file >> height >> width; // Read height and width from the first line
    image.resize(height, vector<int>(width));

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

template <typename Container>
void benchmarkMedianFilter(const vector<vector<int>>& inputImage, int filterSize) {
    int height = inputImage.size();
    int width = inputImage[0].size();
    vector<vector<int>> outputImage(height, vector<int>(width, 0));

    auto start = high_resolution_clock::now();
    applyMedianFilterMultithreaded<Container>(inputImage, outputImage, filterSize);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Median Filter with " << typeid(Container).name() << " completed in " << duration.count() << " microseconds." << endl;
}

int main() {
    const string inputFilename = "input.txt"; // Input file should have dimensions in the first line
    const int filterSize = 3;

    int height, width;
    vector<vector<int>> inputImage;

    try {
        // Load the grayscale image
        readImage(inputFilename, inputImage, height, width);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Benchmarking different STL containers
    benchmarkMedianFilter<vector<int>>(inputImage, filterSize);
    benchmarkMedianFilter<deque<int>>(inputImage, filterSize);
    benchmarkMedianFilter<list<int>>(inputImage, filterSize);

    return 0;
}

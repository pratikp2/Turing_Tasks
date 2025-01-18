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

enum class ContainerType { VECTOR, DEQUE, LIST };

template <typename Container>
void applyMedianFilterSection(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize, int startRow, int endRow, Container& neighbors) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < cols; ++j) {
            neighbors.clear();

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

template <typename Container>
void applyMedianFilterMultithreaded(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize, Container& neighborsContainer) {
    int numThreads = thread::hardware_concurrency();
    vector<thread> threads;
    int rows = inputImage.size();
    int rowsPerThread = rows / numThreads;

    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? rows : startRow + rowsPerThread;
        auto neighbors = make_shared<Container>(neighborsContainer); // Pass a shared pointer to neighbors

        threads.emplace_back([inputImage, outputImage, filterSize, startRow, endRow, neighbors]() {
            applyMedianFilterSection<Container>(inputImage, outputImage, filterSize, startRow, endRow, *neighbors);
        });
    }

    for (auto& th : threads) {
        th.join();
    }
}

void benchmarkFilter(const vector<vector<int>>& inputImage, int filterSize) {
    cout << "Benchmarking Performance:" << endl;
    for (int i = 0; i < 3; ++i) {
        auto start = high_resolution_clock::now();
        vector<vector<int>> outputImage(inputImage.size(), vector<int>(inputImage[0].size(), 0));

        vector<deque<int>> neighborsDeque;
        applyMedianFilterMultithreaded<deque<int>>(inputImage, outputImage, filterSize, neighborsDeque);

        auto end = high_resolution_clock::now();
        auto durationDeque = duration_cast<microseconds>(end - start);

        cout << "deque: " << durationDeque.count() << " microseconds." << endl;
    }

    cout << endl;
}

void readImageFromFile(const string& filename, vector<vector<int>>& image) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int height, width;
    getline(file, line); // Read the header line assuming height and width are space separated
    istringstream ss(line);
    ss >> height >> width;

    image.resize(height, vector<int>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> image[i][j];
        }
    }

    file.close();
}

void writeImageToFile(const string& filename, const vector<vector<int>>& image) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    file << image.size() << " " << image[0].size() << endl;
    for (const auto& row : image) {
        copy(row.begin(), row.end(), ostream_iterator<int>(file, " "));
        file << endl;
    }

    file.close();
}

int main() {
    const string inputFilename = "input.txt";
    const string outputFilename = "output_multithreaded.txt";
    const int filterSize = 3;

    // Load the grayscale image from file
    vector<vector<int>> inputImage;
    readImageFromFile(inputFilename, inputImage);

    // Benchmark filter performance using deque
    benchmarkFilter(inputImage, filterSize);

    // Apply multithreaded median filter using deque
    auto start = high_resolution_clock::now();
    vector<vector<int>> outputImage(inputImage.size(), vector<int>(inputImage[0].size(), 0));
    vector<deque<int>> neighborsDeque;
    applyMedianFilterMultithreaded<deque<int>>(inputImage, outputImage, filterSize, neighborsDeque);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Write the output image to file
    writeImageToFile(outputFilename, outputImage);

    cout << "Multithreaded Median Filter completed in " << duration.count() << " microseconds." << endl;

    return 0;
}

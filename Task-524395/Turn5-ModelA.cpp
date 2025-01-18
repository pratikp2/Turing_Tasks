#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <thread>
#include <chrono>

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

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
            }

            // Convert to vector for sorting if the container is not random-access
            vector<int> sortedNeighbors(neighbors.begin(), neighbors.end());
            sort(sortedNeighbors.begin(), sortedNeighbors.end());
            outputImage[i][j] = sortedNeighbors[sortedNeighbors.size() / 2]; // Assign the median value
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
    const int filterSize = 3;

    // Create a fixed 5x5 image
    vector<vector<int>> inputImage = {
        { 10, 10, 10, 10, 10 },
        { 10, 50, 50, 50, 10 },
        { 10, 50, 90, 50, 10 },
        { 10, 50, 50, 50, 10 },
        { 10, 10, 10, 10, 10 }
    };

    // Benchmarking different STL containers
    cout << "Benchmarking Median Filter on 5x5 image:" << endl;
    benchmarkMedianFilter<vector<int>>(inputImage, filterSize);
    benchmarkMedianFilter<deque<int>>(inputImage, filterSize);
    benchmarkMedianFilter<list<int>>(inputImage, filterSize);

    return 0;
}

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

using namespace std;
using namespace std::chrono;

void applyMedianFilterVector(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize) {
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

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
            }

            sort(neighbors.begin(), neighbors.end());
            outputImage[i][j] = neighbors[neighbors.size() / 2];
        }
    }
}

void applyMedianFilterDeque(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            deque<int> neighbors;

            for (int k = -offset; k <= offset; ++k) {
                for (int l = -offset; l <= offset; ++l) {
                    int ni = i + k;
                    int nj = j + l;

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
            }

            neighbors.sort();
            outputImage[i][j] = neighbors[neighbors.size() / 2];
        }
    }
}

void applyMedianFilterList(const vector<vector<int>>& inputImage, vector<vector<int>>& outputImage, int filterSize) {
    int rows = inputImage.size();
    int cols = inputImage[0].size();
    int offset = filterSize / 2;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            list<int> neighbors;

            for (int k = -offset; k <= offset; ++k) {
                for (int l = -offset; l <= offset; ++l) {
                    int ni = i + k;
                    int nj = j + l;

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        neighbors.push_back(inputImage[ni][nj]);
                    }
                }
            }

            neighbors.sort();
            outputImage[i][j] = *(neighbors.begin() + neighbors.size() / 2);
        }
    }
}

void readImage(const string& filename, vector<vector<int>>& image) {
    image.resize(5, vector<int>(5));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            image[i][j] = (i * 5 + j) % 256; // Demo data for a 5x5 image
        }
    }
}

void benchmarkMedianFilter(const function<void(const vector<vector<int>>&, vector<vector<int>>&, int)>& filterFunction) {
    int filterSize = 3;
    vector<vector<int>> inputImage;
    readImage("input.txt", inputImage);

    vector<vector<int>> outputImage(inputImage.size(), vector<int>(inputImage[0].size(), 0));

    auto start = high_resolution_clock::now();
    filterFunction(inputImage, outputImage, filterSize);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << filterFunction << " completed in " << duration.count() << " microseconds." << endl;
}

int main() {
    benchmarkMedianFilter(applyMedianFilterVector);
    benchmarkMedianFilter(applyMedianFilterDeque);
    benchmarkMedianFilter(applyMedianFilterList);

    return 0;
}

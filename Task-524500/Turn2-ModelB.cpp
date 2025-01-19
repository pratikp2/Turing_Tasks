#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>

using namespace std;

// Constants
const int CODEBOOK_SIZE = 16;
const int VECTOR_SIZE = 3; // Assuming RGB pixels
const int WIDTH = 256;
const int HEIGHT = 256;
const int IMAGE_COUNT = 10; // Number of images to process

// Function to calculate the Euclidean distance
double euclideanDistance(const double* vec1, const double* vec2) {
    double distance = 0.0;
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        distance += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    }
    return sqrt(distance);
}

// Function to find the nearest codeword using pointers
int findNearestCodeword(const double* vector, const double* codebook) {
    double minDistance = numeric_limits<double>::max();
    int nearestIndex = -1;

    for (int i = 0; i < CODEBOOK_SIZE; ++i) {
        double distance = euclideanDistance(vector, codebook + i * VECTOR_SIZE);
        if (distance < minDistance) {
            minDistance = distance;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}

// Function to perform compression using pointers
void compressImage(const double* imageData, int width, int height, const double* codebook, vector<int>& indices) {
    auto startTime = chrono::high_resolution_clock::now();

    indices.clear();
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            double* pixelBlock = const_cast<double*>(imageData + (j * width + i) * VECTOR_SIZE);
            int index = findNearestCodeword(pixelBlock, codebook);
            indices.push_back(index);
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Compression time: " << duration.count() << " microseconds" << endl;
}

// Function to decompress the image using pointers
void decompressImage(const vector<int>& indices, double* decompressedData, const double* codebook) {
    auto startTime = chrono::high_resolution_clock::now();

    for (int i = 0; i < IMAGE_COUNT; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            for (int k = 0; k < WIDTH; ++k) {
                int index = indices[i * HEIGHT * WIDTH + j * WIDTH + k];
                double* targetPixel = decompressedData + (i * HEIGHT * WIDTH + j * WIDTH + k) * VECTOR_SIZE;
                const double* codeword = codebook + index * VECTOR_SIZE;
                for (int d = 0; d < VECTOR_SIZE; ++d) {
                    targetPixel[d] = codeword[d];
                }
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Decompression time: " << duration.count() << " microseconds" << endl;
}

int main() {
    // Initialize image data array - Assuming random values
    double imageData[IMAGE_COUNT * HEIGHT * WIDTH * VECTOR_SIZE];
    for (int i = 0; i < IMAGE_COUNT * HEIGHT * WIDTH * VECTOR_SIZE; ++i) {
        imageData[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Codebook (just an example, in real case, generate it with K-means)
    double codebook[CODEBOOK_SIZE * VECTOR_SIZE] = {
        0.1, 0.2, 0.3, 0.4, 0.5, 0.6, // Placeholder values for RGB
        0.7, 0.8, 0.9, 0.1, 0.2, 0.3, // Continue with more values...
        // ...
    };

    // For compression, we'll store the indices here
    vector<int> indices;

    // Perform compression on multiple images
    for (int i = 0; i < IMAGE_COUNT; ++i) {
        cout << "Compressing image " << i + 1 << "..." << endl;
        compressImage(imageData + i * HEIGHT * WIDTH * VECTOR_SIZE, WIDTH, HEIGHT, codebook, indices);
    }

    // Decompression setup
    double decompressedData[IMAGE_COUNT * HEIGHT * WIDTH * VECTOR_SIZE];

    // Decompress the data
    decompressImage(indices, decompressedData, codebook);

    return 0;
}

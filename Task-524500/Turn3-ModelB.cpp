#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstring>
#include <stdexcept>

using namespace std;

// Constants
const int CODEBOOK_SIZE = 16; // Number of codewords
const int VECTORS_PER_IMAGE = 1024; // Number of vectors to process
const int DIMENSIONS = 3; // RGB channels

// Function to calculate the Euclidean distance
double euclideanDistance(const double* vec1, const double* vec2) {
    double distance = 0.0;
    
    if (vec1 == nullptr || vec2 == nullptr) {
        throw runtime_error("Null pointer error in euclideanDistance function.");
    }
    
    for (int i = 0; i < DIMENSIONS; ++i) {
        distance += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    }
    return sqrt(distance);
}

// Function to find the nearest codeword
int findNearestCodeword(const double* vector, const double* codebook) {
    if (vector == nullptr || codebook == nullptr) {
        throw runtime_error("Null pointer error in findNearestCodeword function.");
    }

    double minDistance = numeric_limits<double>::max();
    int nearestIndex = -1;

    for (int i = 0; i < CODEBOOK_SIZE; ++i) {
        double distance = euclideanDistance(vector, &codebook[i * DIMENSIONS]);
        if (distance < minDistance) {
            minDistance = distance;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}

// Function to process the image (compression and decompression)
void processImage(const double* imageData, double* codebook, vector<int>& indices, double* decompressedData, int width, int height) {
    if (imageData == nullptr || codebook == nullptr || decompressedData == nullptr) {
        throw runtime_error("Null pointer error in processImage function.");
    }
    
    if (width <= 0 || height <= 0) {
        throw runtime_error("Invalid image dimensions in processImage function.");
    }

    // Compress the image using vector quantization
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            const double* pixelBlock = &imageData[(j * width + i) * DIMENSIONS];
            int index = findNearestCodeword(pixelBlock, codebook);
            indices.push_back(index);
        }
    }

    // Decompress the image using the codebook
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int index = indices[j * width + i];
            if (index < 0 || index >= CODEBOOK_SIZE) {
                throw runtime_error("Invalid codeword index in processImage function.");
            }

            double* targetPixel = &decompressedData[(j * width + i) * DIMENSIONS];
            const double* codeword = &codebook[index * DIMENSIONS];
            memcpy(targetPixel, codeword, DIMENSIONS * sizeof(double));
        }
    }
}

int main() {
    // Example dimensions
    const int width = 32;
    const int height = 32;

    // Example image data (width, height, channels)
    double imageData[width * height * DIMENSIONS]; // Your image data

    // Initialize your image data with some sample values here.
    for (int i = 0; i < width * height * DIMENSIONS; ++i) {
        imageData[i] = static_cast<double>(rand()) / RAND_MAX; // Random values for demonstration
    }

    // Codebook (just an example; in a real case, generate it with K-means)
    double codebook[CODEBOOK_SIZE * DIMENSIONS] = {
        0.5, 0.5, 0.5,
        0.1, 0.2, 0.3,
        // Additional codewords would be defined here...
    };

    // For compression, we'll store the indices here
    vector<int> indices;
    
    // Prepare the decompressed data array
    double decompressedData[width * height * DIMENSIONS];

    try {
        // Process the image (compress and decompress)
        processImage(imageData, codebook, indices, decompressedData, width, height);

        // Print codebook indices for demonstration
        cout << "Compressed indices: ";
        for (auto index : indices) {
            cout << index << " ";
        }
        cout << endl;

        // For demonstration, you may want to print some decompressed data values
        cout << "Decompressed data (first pixel): ";
        for (int d = 0; d < DIMENSIONS; ++d) {
            cout << decompressedData[0 * DIMENSIONS + d] << " ";
        }
        cout << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

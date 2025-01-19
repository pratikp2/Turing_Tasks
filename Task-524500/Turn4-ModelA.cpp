#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstring>
#include <stdexcept>
#include <thread>
#include <mutex>

using namespace std;

// Constants
const int CODEBOOK_SIZE = 16; // Number of codewords
const int DIMENSIONS = 3; // RGB channels

// Function to calculate the Euclidean distance
double euclideanDistance(const double* vec1, const double* vec2) {
    if (!vec1 || !vec2) {
        throw invalid_argument("Input vectors must not be null");
    }
    
    double distance = 0.0;
    for (int i = 0; i < DIMENSIONS; ++i) {
        distance += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    }
    return sqrt(distance);
}

// Function to find the nearest codeword
int findNearestCodeword(const double* vector, const double* codebook) {
    if (!vector || !codebook) {
        throw invalid_argument("Input vector and codebook must not be null");
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

// Function to compress image segment
void compressSegment(const double* imageData, const double* codebook, vector<int>& indices, int width, int height, int startRow, int endRow, mutex& indicesMutex) {
    for (int j = startRow; j < endRow; ++j) {
        for (int i = 0; i < width; ++i) {
            const double* pixelBlock = &imageData[(j * width + i) * DIMENSIONS];
            int index = findNearestCodeword(pixelBlock, codebook);
            
            // Lock mutex to safely add index to shared vector
            {
                lock_guard<mutex> lock(indicesMutex);
                indices.push_back(index);
            }
        }
    }
}

// Function to process the image (compression and decompression)
void processImage(const double* imageData, const double* codebook, vector<int>& indices, double* decompressedData, int width, int height) {
    if (!imageData || !codebook || !decompressedData) {
        throw invalid_argument("Image data, codebook, and decompressed data must not be null");
    }
    if (width <= 0 || height <= 0) {
        throw invalid_argument("Image width and height must be greater than zero");
    }

    int numThreads = thread::hardware_concurrency(); // Get number of hardware threads
    vector<thread> threads;
    mutex indicesMutex; // Mutex for protecting shared indices vector

    // Divide work among available threads
    int rowsPerThread = height / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? height : (t + 1) * rowsPerThread;
        threads.emplace_back(compressSegment, imageData, codebook, ref(indices), width, height, startRow, endRow, ref(indicesMutex));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Decompress the image using the codebook
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int index = indices[j * width + i];
            if (index < 0 || index >= CODEBOOK_SIZE) {
                throw out_of_range("Index processed during decompression is out of codebook bounds");
            }
            double* targetPixel = &decompressedData[(j * width + i) * DIMENSIONS];
            const double* codeword = &codebook[index * DIMENSIONS];
            memcpy(targetPixel, codeword, DIMENSIONS * sizeof(double)); // Use memcpy for efficiency
        }
    }
}

int main() {
    try {
        // Example dimensions
        const int width = 32;
        const int height = 32;

        // Example image data (width, height, channels)
        double imageData[width * height * DIMENSIONS]; // Your image data initialized previously

        // Initialize your image data with some sample values for demonstration
        for (int i = 0; i < width * height * DIMENSIONS; ++i) {
            imageData[i] = static_cast<double>(rand()) / RAND_MAX; // Random values for demonstration
        }

        // Codebook (initialization for example purposes)
        double codebook[CODEBOOK_SIZE * DIMENSIONS] = {
            0.5, 0.5, 0.5,
            0.1, 0.2, 0.3,
            // More codewords can be added based on your requirements...
        };

        // For compression, we'll store the indices here
        vector<int> indices(height * width); // Pre-allocate space for indices
        
        // Prepare the decompressed data array
        double decompressedData[width * height * DIMENSIONS];

        // Process the image (compress and decompress)
        processImage(imageData, codebook, indices, decompressedData, width, height);

        // Print codebook indices for demonstration
        cout << "Compressed indices: ";
        for (auto index : indices) {
            cout << index << " ";
        }
        cout << endl;

        // For demonstration, print some decompressed data values
        cout << "Decompressed data (first pixel): ";
        for (int d = 0; d < DIMENSIONS; ++d) {
            cout << decompressedData[0 * DIMENSIONS + d] << " ";
        }
        cout << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

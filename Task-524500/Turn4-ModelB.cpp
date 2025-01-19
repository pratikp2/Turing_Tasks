#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <limits>
#include <cstring>
#include <stdexcept>
#include <mutex>

using namespace std;

// Constants
const int CODEBOOK_SIZE = 16; // Number of codewords
const int DIMENSIONS = 3; // RGB channels
const int BLOCK_SIZE = 128; // Width of each thread's processing block

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
int findNearestCodeword(const double* vector, const double* codebook, mutex& codebookMutex) {
    if (!vector || !codebook) {
        throw invalid_argument("Input vector and codebook must not be null");
    }

    codebookMutex.lock(); // Lock the codebook for reading

    double minDistance = numeric_limits<double>::max();
    int nearestIndex = -1;

    for (int i = 0; i < CODEBOOK_SIZE; ++i) {
        double distance = euclideanDistance(vector, &codebook[i * DIMENSIONS]);
        if (distance < minDistance) {
            minDistance = distance;
            nearestIndex = i;
        }
    }
    
    codebookMutex.unlock(); // Unlock the codebook
    return nearestIndex;
}

// Thread function to process a sub-block of the image
void processImageBlock(const double* imageData, const double* codebook, vector<int>& indices, int startWidth, int endWidth, int height, mutex& codebookMutex) {
    for (int j = 0; j < height; ++j) {
        for (int i = startWidth; i < endWidth; ++i) {
            const double* pixelBlock = &imageData[(j * (endWidth - startWidth) + i) * DIMENSIONS];
            int index = findNearestCodeword(pixelBlock, codebook, codebookMutex);
            indices.push_back(index);
        }
    }
}

// Function to process the image (compression) with multithreading
void processImageMultithreaded(const double* imageData, const double* codebook, vector<int>& indices, int width, int height) {
    if (!imageData || !codebook) {
        throw invalid_argument("Image data or codebook must not be null");
    }

    // Determine the number of threads based on available cores or your preference
    const int numThreads = thread::hardware_concurrency();
    int threadWidth = (width + numThreads - 1) / numThreads; // Width per thread

    vector<thread> threads;
    mutex codebookMutex; // Mutex for safe codebook access

    // Create threads to process image blocks concurrently
    for (int threadIdx = 0; threadIdx < numThreads; ++threadIdx) {
        int startWidth = threadIdx * threadWidth;
        int endWidth = min((threadIdx + 1) * threadWidth, width);
        threads.emplace_back([&imageData, &codebook, &indices, startWidth, endWidth, height, &codebookMutex]() {
            processImageBlock(imageData, codebook, indices, startWidth, endWidth, height, codebookMutex);
        });
    }

    // Join all threads
    for (thread& t : threads) {
        t.join();
    }
}

int main() {
    try {
        // Example dimensions
        const int width = 1024;
        const int height = 1024;

        // Example image data (width, height, channels)
        double imageData[width * height * DIMENSIONS]; // Initialize your image data here
        
        // Codebook (initialization for example purposes)
        double codebook[CODEBOOK_SIZE * DIMENSIONS] = {
            // Codebook values should be initialized here...
        };

        // For compression, we'll store the indices here
        vector<int> indices;
        
        // Process the image with multithreading
        processImageMultithreaded(imageData, codebook, indices, width, height);

        // Continue with decompression or other tasks...
        // ...

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

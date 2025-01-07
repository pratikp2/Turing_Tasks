
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

#define ROWS 1000
#define COLS 1000

// Matrix multiplication function with nested loops
void matrixMultiplySingleThreaded(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B, std::vector<std::vector<double>>& C) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double sum = 0;
            for (int k = 0; k < COLS; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// Multithreaded matrix multiplication function
void matrixMultiplyMultiThreaded(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B, std::vector<std::vector<double>>& C, int numThreads) {
    const int chunkSize = ROWS / numThreads;

    std::thread threads[numThreads];

    for (int threadId = 0; threadId < numThreads; threadId++) {
        int startRow = threadId * chunkSize;
        int endRow = std::min((threadId + 1) * chunkSize, ROWS);

        threads[threadId] = std::thread([startRow, endRow, &A, &B, &C] {
            for (int i = startRow; i < endRow; i++) {
                for (int j = 0; j < COLS; j++) {
                    double sum = 0;
                    for (int k = 0; k < COLS; k++) {
                        sum += A[i][k] * B[k][j];
                    }
                    C[i][j] = sum;
                }
            }
        });
    }

    // Join all threads
    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }
}

int main() {
    // Generate random matrices
    std::vector<std::vector<double>> A(ROWS, std::vector<double>(COLS, 0.0));
    std::vector<std::vector<double>> B(COLS, std::vector<double>(COLS, 0.0));
    std::vector<std::vector<double>> C(ROWS, std::vector<double>(COLS, 0.0));

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            A[i][j] = static_cast<double>(std::rand()) / RAND_MAX;
            B[i][j] = static_cast<double>(std::rand()) / RAND_MAX;
        }
    }

    //Single Threaded Execution
    std::cout << "Single Threaded Execution:\n";
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        matrixMultiplySingleThreaded(A, B, C);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
    }


    // Multi-Threaded Execution
    const int numThreads = 4;
    std::cout << "Multi-Threaded Execution with " << numThreads << " threads:\n";
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        matrixMultiplyMultiThreaded(A, B, C, numThreads);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
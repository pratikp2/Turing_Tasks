#include <chrono>
#include <iostream>
#include <vector>
#include <iostream>
#include <vector>

void optimizedMatrixMultiply(const std::vector<std::vector<int>>& A, 
                              const std::vector<std::vector<int>>& B, 
                              std::vector<std::vector<int>>& C) {
    int n = A.size();
    
    // Track which rows in A and columns in B are necessary
    std::vector<bool> necessaryRowA(n, false);
    std::vector<bool> necessaryColB(n, false);

    // Identify necessary rows and columns
    for (int i = 0; i < n; i++) {
        if (std::any_of(A[i].begin(), A[i].end(), [](int x) { return x != 0; })) {
            necessaryRowA[i] = true;
        }
    }
    
    for (int j = 0; j < n; j++) {
        if (std::any_of(B.begin(), B.end(), [&](const std::vector<int>& row) { return row[j] != 0; })) {
            necessaryColB[j] = true;
        }
    }

    // Perform multiplication only if necessary rows and columns are valid
    for (int i = 0; i < n; i++) {
        if (!necessaryRowA[i]) continue; // Skip unnecessary rows
        
        for (int j = 0; j < n; j++) {
            if (!necessaryColB[j]) continue; // Skip unnecessary columns
            
            C[i][j] = 0; // Initialize C[i][j]
            
            // Loop only through necessary columns
            for (int k = 0; k < n; k++) {
                if (necessaryColB[k]) { 
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
}

void matrixMultiply(const std::vector<std::vector<int>>& A, 
                    const std::vector<std::vector<int>>& B, 
                    std::vector<std::vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0; // Initialize C[i][j]
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void benchmark(int size, int trials) {
    std::vector<std::vector<int>> A(size, std::vector<int>(size, 0));
    std::vector<std::vector<int>> B(size, std::vector<int>(size, 0));
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    // Initialize A and B with values...

    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < trials; i++) {
        optimizedMatrixMultiply(A, B, C);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Optimized duration: " << duration.count() << " seconds" << std::endl;
}

int main() {
    benchmark(100, 10);  // For instance, size 100 and 10 trials
    return 0;
}

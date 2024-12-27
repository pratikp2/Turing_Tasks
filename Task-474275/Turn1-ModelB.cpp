#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

using namespace std;

void matrixMultiply(const vector<vector<double>>& A, const vector<vector<double>>& B, vector<vector<double>>& C) {
    const int rowsA = A.size();
    const int colsA = A[0].size();
    const int rowsB = B.size();
    const int colsB = B[0].size();

    assert(colsA == rowsB);

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            double sum = 0;
            for (int k = 0; k < colsA; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void parallelMatrixMultiply(const vector<vector<double>>& A, const vector<vector<double>>& B, vector<vector<double>>& C) {
    const int rowsA = A.size();
    const int colsA = A[0].size();
    const int rowsB = B.size();
    const int colsB = B[0].size();

    assert(colsA == rowsB);

    for (int i = 0; i < rowsA; ++i) {
        std::for_each(std::execution::par, std::begin(C[i]), std::end(C[i]), [&](double& cij) {
            double sum = 0;
            for (int k = 0; k < colsA; ++k) {
                sum += A[i][k] * B[k][j];
            }
            cij = sum;
        });
    }
}

int main() {
    const int size = 1000;
    vector<vector<double>> A(size, vector<double>(size, 1.0));
    vector<vector<double>> B(size, vector<double>(size, 1.0));
    vector<vector<double>> C(size, vector<vector<double>>(size, 0.0));

    // Serial execution
    matrixMultiply(A, B, C);

    // Parallel execution
    parallelMatrixMultiply(A, B, C);

    return 0;
}

#include <iostream>
#include <cmath>

const int N = 1000000;

double dotProduct(const double* x, const double* y) {
    double result = 0.0;

    // Example of loop unrolling with 4 iterations
    for (int i = 0; i < N; i += 4) {
        result += x[i] * y[i] + x[i+1] * y[i+1] + x[i+2] * y[i+2] + x[i+3] * y[i+3];
    }

    return result;
}

int main() {
    double x[N], y[N];

    // Initialize arrays with some data
    for (int i = 0; i < N; i++) {
        x[i] = std::sin(i);
        y[i] = std::cos(i);
    }

    double dot = dotProduct(x, y);

    std::cout << "Dot product: " << dot << std::endl;

    return 0;
}
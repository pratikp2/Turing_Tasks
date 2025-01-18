#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to apply mean filtering on a 3x3 neighbourhood
unsigned char meanFilter(const vector<vector<unsigned char>>& image, int x, int y) {
    // Define the kernel size (3x3)
    const int kernelSize = 3;
    unsigned char sum = 0;

    // Check for boundary conditions
    if (x < kernelSize / 2 || x >= static_cast<int>(image.size()) - kernelSize / 2 ||
        y < kernelSize / 2 || y >= static_cast<int>(image[0].size()) - kernelSize / 2) {
        return image[x][y]; // Return the original pixel for boundary pixels
    }

    for (int i = x - kernelSize / 2; i <= x + kernelSize / 2; ++i) {
        for (int j = y - kernelSize / 2; j <= y + kernelSize / 2; ++j) {
            sum += image[i][j];
        }
    }

    return static_cast<unsigned char>(sum / (kernelSize * kernelSize));
}

int main() {
    // Example grayscale X-ray image data (replace this with your actual image data)
    const vector<vector<unsigned char>> imageData = {
        {100, 110, 120, 115, 105},
        {120, 130, 145, 135, 125},
        {115, 140, 160, 150, 135},
        {105, 125, 140, 130, 115},
        {100, 110, 120, 115, 105}
    };

    int rows = static_cast<int>(imageData.size());
    int cols = static_cast<int>(imageData[0].size());

    // Create a vector to store the filtered image data
    vector<vector<unsigned char>> filteredImage(rows, vector<unsigned char>(cols));

    // Apply mean filtering to each pixel using STL for_each algorithm
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            filteredImage[x][y] = meanFilter(imageData, x, y);
        }
    }

    // Output the filtered image
    cout << "Filtered Image:" << endl;
    for (const auto& row : filteredImage) {
        for (const auto& pixel : row) {
            cout << static_cast<int>(pixel) << " ";
        }
        cout << endl;
    }

    return 0;
}

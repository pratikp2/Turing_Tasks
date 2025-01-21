#include <iostream>
#include <cmath>
#include <vector>

typedef unsigned char Pixel;

class ImageRestorer {
private:
    // ... (Previous code remains the same)

    void edgePreservingSmoothing(Pixel** inputImage, Pixel** outputImage, int width, int height) {
        const float sobelX[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
        };

        const float sobelY[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
        };

        // Detect edges using Sobel operator
        Pixel** edgeMap = new Pixel*[height];
        for (int i = 0; i < height; ++i) {
            edgeMap[i] = new Pixel[width];
        }

        // Compute gradient magnitude
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                float gradientX = 0.0f;
                float gradientY = 0.0f;

                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        gradientX += sobelX[ky + 1][kx + 1] * static_cast<float>(inputImage[y + ky][x + kx]);
                        gradientY += sobelY[ky + 1][kx + 1] * static_cast<float>(inputImage[y + ky][x + kx]);
                    }
                }

                float gradientMagnitude = sqrt(gradientX * gradientX + gradientY * gradientY);
                edgeMap[y][x] = static_cast<Pixel>(gradientMagnitude);
            }
        }

        // Apply Gaussian smoothing only to non-edge areas
        const float gaussianKernel[3][3] = {
            {1/16.0f, 2/16.0f, 1/16.0f},
            {2/16.0f, 4/16.0f, 2/16.0f},
            {1/16.0f, 2/16.0f, 1/16.0f}
        };

        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                if (edgeMap[y][x] < 128) { // Threshold to determine non-edge areas (you can adjust this)
                    float sum = 0.0f;

                    for (int ky = -1; ky <= 1; ++ky) {
                        for (int kx = -1; kx <= 1; ++kx) {
                            sum += (gaussianKernel[ky + 1][kx + 1] * inputImage[y + ky][x + kx]);
                        }
                    }

                    outputImage[y][x] = static_cast<Pixel>(std::min(std::max(int(sum), 0), 255));
                } else {
                    outputImage[y][x] = inputImage[y][x]; // Preserve edges
                }
            }
        }

        // Free the edge map
        for (int i = 0; i < height; ++i) {
            delete[] edgeMap[i];
        }
        delete[] edgeMap;
    }

public:
    // ... (Previous public methods remain the same)

    void restoreWithEdgePreservation(Pixel** inputImage, Pixel** outputImage, int width, int height) {
        // First, apply Gaussian blur for preprocessing
        gaussianBlur(inputImage, inputImage, width, height);

        // Then, apply edge-preserving smoothing
        edgePreservingSmoothing(inputImage, outputImage, width, height);
    }
};

int main() {
    // ... (Previous main code remains the same)

    // Restore the image with edge preservation
    restorer.restoreWithEdgePreservation(inputImage, outputImage, width, height);

    // Output the result
    std::cout << "Restored Image with Edge Preservation:" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << static_cast<int>(outputImage[y][x]) << " ";
        }
        std::cout << std::endl;
    }

    // ... (Previous free memory code remains the same)

    return 0;
}

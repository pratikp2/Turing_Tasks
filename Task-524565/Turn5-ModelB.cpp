#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef unsigned char Pixel; // Pixel type for clarity

class ImageRestorer {
private:
    float** gaussianKernel;
    int kernelSize;

    void createGaussianKernel(int size, float sigma) {
        kernelSize = size;
        gaussianKernel = new float*[size];
        float sum = 0.0f;
        int halfSize = size / 2;

        // Create Gaussian kernel
        for (int x = -halfSize; x <= halfSize; ++x) {
            gaussianKernel[x + halfSize] = new float[size];
            for (int y = -halfSize; y <= halfSize; ++y) {
                gaussianKernel[x + halfSize][y + halfSize] =
                    exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * 3.14159f * sigma * sigma);
                sum += gaussianKernel[x + halfSize][y + halfSize];
            }
        }

        // Normalize the kernel
        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                gaussianKernel[x][y] /= sum;
            }
        }
    }

    void convertToGrayscale(Pixel*** inputImage, int width, int height) {
        // Perform grayscale conversion using pointers
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Pixel grayscale = static_cast<Pixel>(
                    0.2126f * inputImage[y][x][0] +
                    0.7152f * inputImage[y][x][1] +
                    0.0722f * inputImage[y][x][2]
                );
                // Overwrite RGB channels with grayscale value
                inputImage[y][x][0] = grayscale;
                inputImage[y][x][1] = grayscale;
                inputImage[y][x][2] = grayscale;
            }
        }
    }

    void applyGaussianFilter(Pixel*** inputImage, Pixel*** outputImage, int width, int height) {
        int halfSize = kernelSize / 2;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                for (int channel = 0; channel < 1; ++channel) { // Loop over grayscale channel (now single channel)
                    float sum = 0.0f;

                    for (int ky = -halfSize; ky <= halfSize; ++ky) {
                        for (int kx = -halfSize; kx <= halfSize; ++kx) {
                            int imgX = std::clamp(x + kx, 0, width - 1);
                            int imgY = std::clamp(y + ky, 0, height - 1);
                            sum += gaussianKernel[ky + halfSize][kx + halfSize] * inputImage[imgY][imgX][channel];
                        }
                    }
                    outputImage[y][x][channel] = static_cast<Pixel>(std::min(std::max(int(sum), 0), 255));
                }
            }
        }
    }

public:
    ImageRestorer() {
        createGaussianKernel(5, 1.0f); // Create a 5x5 Gaussian kernel with a standard deviation of 1.0
    }

    ~ImageRestorer() {
        for (int i = 0; i < kernelSize; ++i) {
            delete[] gaussianKernel[i];
        }
        delete[] gaussianKernel;
    }

    void restore(Pixel*** inputImage, Pixel*** outputImage, int width, int height) {
        // Convert RGB to grayscale
        convertToGrayscale(inputImage, width, height);

        // Apply Gaussian filter to the grayscale image
        applyGaussianFilter(inputImage, outputImage, width, height);
    }
};

int main() {
    // Define image dimensions
    int width = 5;
    int height = 5;

    // Allocate memory for input and output images (3 channels for RGB)
    Pixel*** inputImage = new Pixel**[height];
    Pixel*** outputImage = new Pixel**[height];

    for (int i = 0; i < height; ++i) {
        inputImage[i] = new Pixel*[width];
        outputImage[i] = new Pixel*[width];
        for (int j = 0; j < width; ++j) {
            inputImage[i][j] = new Pixel[3]; // Initialize 3 channels for RGB
            outputImage[i][j] = new Pixel[3];
        }
    }

    // Initialize input image with some test values for RGB channels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            inputImage[y][x][0] = static_cast<Pixel>(y * width + x) * 20; // Red channel
            inputImage[y][x][1] = static_cast<Pixel>(y * width + x * 2) * 20; // Green channel
            inputImage[y][x][2] = static_cast<Pixel>(y * width + x * 3) * 20; // Blue channel
        }
    }

    // Create an instance of ImageRestorer
    ImageRestorer restorer;

    // Restore the image
    restorer.restore(inputImage, outputImage, width, height);

    // Output the result (grayscale after restoration)
    std::cout << "Restored Image:" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << static_cast<int>(outputImage[y][x][0]) << " ";
        }
        std::cout << std::endl;
    }

    // Free allocated memory
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete[] inputImage[i][j];
            delete[] outputImage[i][j];
        }
        delete[] inputImage[i];
        delete[] outputImage[i];
    }
    delete[] inputImage;
    delete[] outputImage;

    return 0;
}

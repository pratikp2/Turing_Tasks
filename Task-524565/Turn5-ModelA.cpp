#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef unsigned char Pixel; // Define a Pixel type for clarity

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

    void convertToGrayscale(Pixel*** inputImage, Pixel** grayImage, int width, int height) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Convert RGB to grayscale using the weighted average method
                grayImage[y][x] = static_cast<Pixel>(
                    0.299f * inputImage[y][x][0] +
                    0.587f * inputImage[y][x][1] +
                    0.114f * inputImage[y][x][2]
                );
            }
        }
    }

    void applyGaussianFilter(Pixel** grayImage, Pixel** outputImage, int width, int height) {
        int halfSize = kernelSize / 2;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float sum = 0.0f;

                for (int ky = -halfSize; ky <= halfSize; ++ky) {
                    for (int kx = -halfSize; kx <= halfSize; ++kx) {
                        int imgX = std::clamp(x + kx, 0, width - 1);
                        int imgY = std::clamp(y + ky, 0, height - 1);
                        sum += gaussianKernel[ky + halfSize][kx + halfSize] * grayImage[imgY][imgX];
                    }
                }
                outputImage[y][x] = static_cast<Pixel>(std::min(std::max(int(sum), 0), 255));
            }
        }
    }

public:
    ImageRestorer() {
        createGaussianKernel(5, 1.0f); // Create a 5x5 Gaussian kernel
    }

    ~ImageRestorer() {
        for (int i = 0; i < kernelSize; ++i) {
            delete[] gaussianKernel[i];
        }
        delete[] gaussianKernel;
    }

    void restore(Pixel*** inputImage, Pixel** outputImage, int width, int height) {
        // Step 1: Convert RGB to Grayscale
        Pixel** grayImage = new Pixel*[height];
        for (int i = 0; i < height; ++i) {
            grayImage[i] = new Pixel[width];
        }
        convertToGrayscale(inputImage, grayImage, width, height);

        // Step 2: Apply Gaussian filter to the grayscale image
        applyGaussianFilter(grayImage, outputImage, width, height);

        // Free memory used for gray image
        for (int i = 0; i < height; ++i) {
            delete[] grayImage[i];
        }
        delete[] grayImage;
    }
};

int main() {
    // Define image dimensions
    int width = 5;
    int height = 5;

    // Allocate memory for input RGB image (3 channels)
    Pixel*** inputImage = new Pixel**[height];
    for (int i = 0; i < height; ++i) {
        inputImage[i] = new Pixel*[width];
        for (int j = 0; j < width; ++j) {
            inputImage[i][j] = new Pixel[3]; // 3 channels for RGB
        }
    }

    // Initialize input image with some test RGB values (e.g., a gradient)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            inputImage[y][x][0] = static_cast<Pixel>((y * width + x) * 10); // R
            inputImage[y][x][1] = static_cast<Pixel>((y * width + x) * 20); // G
            inputImage[y][x][2] = static_cast<Pixel>((y * width + x) * 30); // B
        }
    }

    // Allocate memory for output grayscale image
    Pixel** outputImage = new Pixel*[height];
    for (int i = 0; i < height; ++i) {
        outputImage[i] = new Pixel[width];
    }

    // Create an instance of ImageRestorer
    ImageRestorer restorer;

    // Restore the image (convert to grayscale + apply Gaussian filter)
    restorer.restore(inputImage, outputImage, width, height);

    // Output the result
    std::cout << "Restored Grayscale Image:" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << static_cast<int>(outputImage[y][x]) << " ";
        }
        std::cout << std::endl;
    }

    // Free allocated memory for input image
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete[] inputImage[i][j]; // Free each RGB pixel
        }
        delete[] inputImage[i]; // Free the row
    }
    delete[] inputImage; // Free the array of rows

    // Free allocated memory for output image
    for (int i = 0; i < height; ++i) {
        delete[] outputImage[i];
    }
    delete[] outputImage;

    return 0;
}

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

    void applyGaussianFilterToChannel(Pixel* channel, int width, int height) {
        int halfSize = kernelSize / 2;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float sum = 0.0f;

                for (int ky = -halfSize; ky <= halfSize; ++ky) {
                    for (int kx = -halfSize; kx <= halfSize; ++kx) {
                        int imgX = std::clamp(x + kx, 0, width - 1);
                        int imgY = std::clamp(y + ky, 0, height - 1);
                        sum += gaussianKernel[ky + halfSize][kx + halfSize] * static_cast<float>(channel[imgY * width + imgX]);
                    }
                }
                channel[y * width + x] = static_cast<Pixel>(std::min(std::max(int(sum), 0), 255));
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

    void restore(Pixel** inputImage, Pixel** outputImage, int width, int height) {
        // Ensure both input and output images have the same size
        assert(inputImage[0] != nullptr && outputImage[0] != nullptr);

        // Apply Gaussian filter to each channel (R, G, B)
        applyGaussianFilterToChannel(inputImage[0], width, height); // Red channel
        applyGaussianFilterToChannel(inputImage[1], width, height); // Green channel
        applyGaussianFilterToChannel(inputImage[2], width, height); // Blue channel

        // Copy the filtered channels to the output image
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                outputImage[0][y * width + x] = inputImage[0][y * width + x];
                outputImage[1][y * width + x] = inputImage[1][y * width + x];
                outputImage[2][y * width + x] = inputImage[2][y * width + x];
            }
        }
    }
};

int main() {
    // Define image dimensions
    int width = 5;
    int height = 5;

    // Allocate memory for input and output RGB images (3 channels each)
    Pixel** inputImage = new Pixel*[3];
    Pixel** outputImage = new Pixel*[3];

    for (int i = 0; i < 3; ++i) {
        inputImage[i] = new Pixel[width * height];
        outputImage[i] = new Pixel[width * height];
    }

    // Initialize input image with some test values (e.g., different values for each channel)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            inputImage[0][index] = static_cast<Pixel>(y * 20); // Red channel
            inputImage[1][index] = static_cast<Pixel>(x * 10); // Green channel
            inputImage[2][index] = static_cast<Pixel>(y * x * 15); // Blue channel
        }
    }

    // Create an instance of ImageRestorer
    ImageRestorer restorer;

    // Restore the image
    restorer.restore(inputImage, outputImage, width, height);

    // Output the result (you can visualize this by saving to a file or displaying it)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << "R: " << static_cast<int>(outputImage[0][y * width + x]) << ", G: " << static_cast<int>(outputImage[1][y * width + x]) << ", B: " << static_cast<int>(outputImage[2][y * width + x]) << " ";
        }
        std::cout << std::endl;
    }

    // Free allocated memory
    for (int i = 0; i < 3; ++i) {
        delete[] inputImage[i];
        delete[] outputImage[i];
    }
    delete[] inputImage;
    delete[] outputImage;

    return 0;
}

#include <iostream>
#include <vector>

typedef unsigned char Pixel; // Define a Pixel type for clarity

void gaussianBlur(Pixel** inputImage, Pixel** outputImage, int width, int height) {
    const float kernel[3][3] = {
        {1/16.0f, 2/16.0f, 1/16.0f},
        {2/16.0f, 4/16.0f, 2/16.0f},
        {1/16.0f, 2/16.0f, 1/16.0f}
    };

    // Loop through each pixel in the image
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float sum = 0.0f;

            // Apply the Gaussian kernel
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    sum += (kernel[ky + 1][kx + 1] * inputImage[y + ky][x + kx]);
                }
            }

            // Set the output pixel value as the computed sum (clamped to 0-255)
            outputImage[y][x] = static_cast<Pixel>(std::min(std::max(int(sum), 0), 255));
        }
    }
}

int main() {
    // Example of creating a simple 5x5 test image
    int width = 5;
    int height = 5;
    
    // Allocate memory for the input and output images
    Pixel** inputImage = new Pixel*[height];
    Pixel** outputImage = new Pixel*[height];
    
    for (int i = 0; i < height; ++i) {
        inputImage[i] = new Pixel[width];
        outputImage[i] = new Pixel[width];
    }

    // Initialize input image with some test values
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            inputImage[y][x] = static_cast<Pixel>(y * width + x) * 10; // Simple gradient
        }
    }

    // Apply Gaussian blur
    gaussianBlur(inputImage, outputImage, width, height);

    // Output the result
    std::cout << "Output Image:" << std::endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << static_cast<int>(outputImage[y][x]) << " ";
        }
        std::cout << std::endl;
    }

    // Free allocated memory
    for (int i = 0; i < height; ++i) {
        delete[] inputImage[i];
        delete[] outputImage[i];
    }
    delete[] inputImage;
    delete[] outputImage;

    return 0;
}

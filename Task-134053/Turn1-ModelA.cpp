#include <iostream>
#include <opencv2/opencv.hpp>

// Function to apply Gaussian blur
cv::Mat applyGaussianBlur(const cv::Mat& inputImage, int kernelSize) {
	cv::Mat blurredImage;
	cv::GaussianBlur(inputImage, blurredImage, cv::Size(kernelSize, kernelSize), 0, 0);
	return blurredImage;
}

int main() {
	// Maintainability Tip: Use meaningful variable names and comments

	// Read the input image
	std::string imagePath = "input.jpg";
	cv::Mat inputImage = cv::imread(imagePath);

	if (inputImage.empty()) {
		std::cerr << "Error: Cannot read input image!" << std::endl;
		return 1;
	}

	// Apply Gaussian blur (Maintainability Tip: Use const references for parameters)
	int blurKernelSize = 5;
	cv::Mat blurredImage = applyGaussianBlur(inputImage, blurKernelSize);

	// Display the blurred image
	std::string windowName = "Blurred Image";
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cv::imshow(windowName, blurredImage);

	// Wait for user input to close the window
	cv::waitKey(0);

	// Maintainability Tip: Properly release resources
	cv::destroyAllWindows();

	return 0;
}
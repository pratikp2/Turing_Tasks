#include <iostream>
using namespace std;

const int MRIScanSizeX = 128;
const int MRIScanSizeY = 128;
const int MRIScanSizeZ = 64;

// Function to perform some analysis on a sliced MRI section
void AnalyzeMRISection(const float* slice, int sliceWidth, int sliceHeight) {
    cout << "Analyzing MRI section with size: " << sliceWidth << " x " << sliceHeight << endl;
    // Perform your analysis here
    // For simplicity, we'll just print the average value of the slice
    float sum = 0.0f;
    for (int y = 0; y < sliceHeight; y++) {
        for (int x = 0; x < sliceWidth; x++) {
            sum += slice[y * sliceWidth + x];
        }
    }
    float average = sum / (sliceWidth * sliceHeight);
    cout << "Average value of the slice: " << average << endl;
}

int main() {
    // Allocate memory for the 3D MRI scan data array
    float* MRIscanData = new float[MRIScanSizeX * MRIScanSizeY * MRIScanSizeZ];

    // Initialize the MRI scan data with random values (for demonstration purposes)
    for (int z = 0; z < MRIScanSizeZ; z++) {
        for (int y = 0; y < MRIScanSizeY; y++) {
            for (int x = 0; x < MRIScanSizeX; x++) {
                MRIscanData[z * MRIScanSizeX * MRIScanSizeY + y * MRIScanSizeX + x] = float(rand()) / RAND_MAX;
            }
        }
    }

    // Slicing the MRI scan data to analyze a specific section
    const int sliceXStart = 32;
    const int sliceXEnd = 96;
    const int sliceYStart = 16;
    const int sliceYEnd = 80;
    const int sliceZ = 32;

    const int sliceWidth = sliceXEnd - sliceXStart + 1;
    const int sliceHeight = sliceYEnd - sliceYStart + 1;

    // Calculate the pointer to the start of the sliced section
    const float* slicedSection = &MRIscanData[sliceZ * MRIScanSizeX * MRIScanSizeY + sliceYStart * MRIScanSizeX + sliceXStart];

    // Perform analysis on the sliced section
    AnalyzeMRISection(slicedSection, sliceWidth, sliceHeight);

    // Remember to free the dynamically allocated memory
    delete[] MRIscanData;

    return 0;
}

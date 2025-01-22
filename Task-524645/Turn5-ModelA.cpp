#include <iostream>
#include <cstring>
#include <cctype>

// Function to normalize the text
char* normalizeText(const char* input) {
    size_t len = strlen(input);
    char* normalized = new char[len + 1];

    size_t j = 0; // Index for normalized string creation

    for (size_t i = 0; i < len; ++i) {
        char c = input[i];

        // Replace special characters with space
        if (!isalnum(c) && c != ' ' && c != '\n') { 
            normalized[j++] = ' ';
        } else {
            // Convert to lowercase when it's a valid character
            normalized[j++] = tolower(c);
        }
    }

    // Null-terminate the normalized string
    normalized[j] = '\0';

    // Remove leading and trailing spaces
    size_t start = 0;
    size_t end = (j > 0) ? j - 1 : 0; // Adjust end for empty string case

    // Find the first non-space character from the start
    while (start < j && normalized[start] == ' ') {
        start++;
    }

    // Find the last non-space character from the end
    while (end > start && normalized[end] == ' ') {
        end--;
    }

    // Check if the string is entirely spaces or empty
    if (start > end) {
        delete[] normalized; // Free intermediate buffer
        char* result = new char[1];
        result[0] = '\0'; // Return an empty string
        return result;
    }

    // Fill in the result excluding leading/trailing spaces
    size_t resultLength = end - start + 1;
    char* result = new char[resultLength + 1];
    for (size_t i = 0; i < resultLength; ++i) {
        result[i] = normalized[start + i];
    }

    // Null-terminate the result
    result[resultLength] = '\0';

    // Clean up intermediate normalized
    delete[] normalized;

    return result;
}

// Simulated OCR function
char* simulateOCR(const char* imageText) {
    // In a real scenario, this function would perform image processing
    // Here, we simulate it by just returning the input string
    return const_cast<char*>(imageText);
}

int main() {
    // Simulated OCR output from a historical document (raw input string)
    const char* rawOCRText = "   Historical Document:    18th Century Artifacts!!!    \nShall we consider the context?  ";

    // Simulate the OCR process
    char* ocrOutput = simulateOCR(rawOCRText);

    // Normalize the OCR output
    char* normalizedText = normalizeText(ocrOutput);

    // Display the results
    std::cout << "Raw OCR Output: '" << ocrOutput << "'\n";
    std::cout << "Normalized Text: '" << normalizedText << "'\n";

    // Clean up dynamically allocated memory
    delete[] normalizedText;

    return 0;
}

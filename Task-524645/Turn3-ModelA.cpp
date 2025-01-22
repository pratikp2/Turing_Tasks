#include <iostream>
#include <cstring>
#include <cctype>

// Function to normalize the text
char* normalizeText(const char* input) {
    // Calculate the length of the input string
    size_t len = strlen(input);
    
    // Allocate memory for the normalized string
    // +1 for the null terminator
    char* normalized = new char[len + 1];

    // Variables to track start and end of the useful text
    size_t start = 0;
    size_t end = len - 1;

    // Find the first non-space character from the start
    while (start < len && input[start] == ' ') {
        start++;
    }

    // Find the last non-space character from the end
    while (end > start && input[end] == ' ') {
        end--;
    }

    // If the string is made entirely of spaces
    if (start > end) {
        normalized[0] = '\0'; // Set as empty string
        return normalized;
    }

    // Normalize text: Copy and convert to lowercase
    size_t j = 0;

    for (size_t i = start; i <= end; ++i) {
        // Convert to lowercase and copy to normalized string
        normalized[j++] = tolower(input[i]);
    }

    // Add null terminator to the end of the normalized string
    normalized[j] = '\0';

    return normalized;
}

int main() {
    // Example text input from OCR
    const char* ocrText = "   Hello, World!  THIS is Example Text   ";

    // Normalize the extracted text
    char* normalizedText = normalizeText(ocrText);

    // Output the normalized text
    std::cout << "Normalized Text: '" << normalizedText << "'" << std::endl;

    // Clean up dynamically allocated memory
    delete[] normalizedText;

    return 0;
}

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
    char* result = new char[j + 1];
    size_t start = 0;
    size_t end = j - 1;

    // Find the first non-space character from the start
    while (start < j && normalized[start] == ' ') {
        start++;
    }

    // Find the last non-space character from the end
    while (end > start && normalized[end] == ' ') {
        end--;
    }

    // Fill in the result excluding leading/trailing spaces
    size_t resultIndex = 0;
    for (size_t i = start; i <= end; ++i) {
        result[resultIndex++] = normalized[i];
    }

    // Null-terminate the result
    result[resultIndex] = '\0';

    // Clean up intermediate normalized
    delete[] normalized;

    return result;
}

int main() {
    // Test cases for the normalization function
    const char* testCases[] = {
        "   Hello, World!  THIS is Example Text   ",
        "Historical Document:    18th Century Artifacts!!!    \nShall we consider the context?  ",
        "   OCR-Extracted Data @#$%!! with various <special> characters... \nNew line test case here.   ",
        "Spaces  in between \t various characters... and  symbols??",
        "!@#$%^&*()_+   ",
        "   Just normal text.   ",
        "   Another line\n with text   \n\t and special characters @@@",
        ""
    };

    // Process each test case and output the results
    for (const char* testCase : testCases) {
        char* normalizedText = normalizeText(testCase);
        std::cout << "Original: '" << testCase << "'\n";
        std::cout << "Normalized: '" << normalizedText << "'\n\n";
        delete[] normalizedText; // Clean up allocated memory
    }

    return 0;
}

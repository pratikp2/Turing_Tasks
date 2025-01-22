#include <cctype> // For tolower function
#include <cstring> // For strcpy and strlen functions

#define MAX_TEXT_LENGTH 1024 // Define maximum size of text to be processed

char* normalizeOCRText(const char* inputText) {
    // Store the normalized text result in this buffer
    char normalizedText[MAX_TEXT_LENGTH];
    size_t inputLength = strlen(inputText);

    // Check if the input string is empty
    if (inputLength == 0) {
        strcpy(normalizedText, "");
        return normalizedText;
    }

    // Find the index of the first non-space character
    size_t firstNonSpaceIndex = 0;
    for (; inputText[firstNonSpaceIndex] == ' '; ++firstNonSpaceIndex) {
        // If the entire input is spaces, return an empty string
        if (firstNonSpaceIndex == inputLength) {
            strcpy(normalizedText, "");
            return normalizedText;
        }
    }

    // Find the index of the last non-space character
    size_t lastNonSpaceIndex = inputLength - 1;
    while (inputText[lastNonSpaceIndex] == ' ' && lastNonSpaceIndex > firstNonSpaceIndex) {
        lastNonSpaceIndex--;
    }

    // Copy the trimmed and lowercased text to the result buffer
    size_t normalizedLength = lastNonSpaceIndex - firstNonSpaceIndex + 1;
    for (size_t i = 0; i < normalizedLength; ++i) {
        normalizedText[i] = tolower(inputText[firstNonSpaceIndex + i]);
    }

    normalizedText[normalizedLength] = '\0'; // Null terminate the string

    return normalizedText;
}

int main() {
    const char* inputOCRText = "  H e l l o  W o r l d  "; // Example input
    char* normalizedText = normalizeOCRText(inputOCRText);

    if (normalizedText) {
        printf("Normalized Text: %s\n", normalizedText);
        free(normalizedText); // Don't forget to free the dynamically allocated memory
    } else {
        perror("Error normalizing text.");
    }

    return 0;
}

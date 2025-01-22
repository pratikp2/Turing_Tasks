#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <algorithm>

// Function to normalize text
char* normalizeText(const char* input) {
    const char* specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?/";

    // Create a set of special characters for efficient lookups
    std::set<char> specialCharSet(specialChars);

    size_t len = strlen(input);
    char* normalized = new char[len + 1];
    size_t start = 0;
    size_t end = len - 1;

    while (start < len && input[start] == ' ') {
        start++;
    }

    while (end > start && input[end] == ' ') {
        end--;
    }

    if (start > end) {
        normalized[0] = '\0';
        return normalized;
    }

    size_t j = 0;

    for (size_t i = start; i <= end; ++i) {
        if (input[i] == ' ' || !specialCharSet.count(input[i])) {
            normalized[j++] = tolower(input[i]);
        } else {
            normalized[j++] = ' '; // Replace special characters with spaces
        }
    }

    normalized[j] = '\0';

    return normalized;
}

int main() {
    // Example historical OCR-extracted multi-line text
    const char* historicalText =
        "  The  quick  brown  fox  leaps  over  th'   lazy  dog.\n"
        "Intelligence  is  the  ability  to  adapt  to  change.   -  Stephen  Hawking\n"
        "  Sending  you  love  from  across  the  miles!  1776   was  a  momentous  year.";

    // Normalize the multi-line text
    char* normalizedText = new char[strlen(historicalText) + 1];
    std::strcpy(normalizedText, historicalText);

    // Split the input into lines
    char* line;
    char* saveptr;

    std::cout << "Original Text:\n" << historicalText << std::endl;
    std::cout << "\nNormalized Text:\n";

    for (line = strtok_r(normalizedText, "\n", &saveptr); line != nullptr; line = strtok_r(nullptr, "\n", &saveptr)) {
        char* normalizedLine = normalizeText(line);
        std::cout << normalizedLine << std::endl;
        delete[] normalizedLine;
    }

    // Clean up
    delete[] normalizedText;

    return 0;
}

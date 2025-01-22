#include <iostream>
#include <string>
#include <cctype>
#include <regex>

std::string preprocess(const std::string& input) {
    std::string output;
    bool lastCharSpace = false;

    for (char c : input) {
        // Remove non-alphanumeric characters (except for basic punctuation)
        if (!isalnum(c) && c != ' ' && c != '.' && c != ',' && c != '-') {
            continue;
        }

        // Convert to lowercase
        c = tolower(c);

        // Normalize spaces (only keep a single space between words)
        if (c == ' ') {
            if (!lastCharSpace) {
                output.push_back(c);
                lastCharSpace = true; // remember we've added a space
            }
        } else {
            output.push_back(c);
            lastCharSpace = false; // reset for the next word
        }
    }
    
    // Trim any leading or trailing spaces
    output = std::regex_replace(output, std::regex("^ +| +$|( ) +"), "$1");
    
    return output;
}

int main() {
    std::string inputText;
    
    // Example input; in a real scenario, this might come from a digitized document
    std::cout << "Enter text from manuscript: ";
    std::getline(std::cin, inputText);

    std::string processedText = preprocess(inputText);
    
    std::cout << "Processed text for OCR:\n" << processedText << std::endl;
    
    return 0;
}

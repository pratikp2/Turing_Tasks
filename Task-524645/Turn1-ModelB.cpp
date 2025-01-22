#include <iostream>
#include <string>
#include <algorithm>
#include <map>

void normalizeString(std::string& input) {
    // Remove consecutive spaces
    input.erase(std::unique(input.begin(), input.end(), [](char lhs, char rhs) {
        return lhs == ' ' && rhs == ' ';
    }), input.end());

    // Normalization of characters or patterns.
    std::map<char, std::string> replacements {
        {'ß', "ss"}, {'þ', "th"}, {'ð', "dh"},
        {'œ', "oe"}, {'æ', "ae"}
    };

    for (auto& it : replacements) {
        size_t pos = 0;
        while ((pos = input.find(it.first, pos)) != std::string::npos) {
            input.replace(pos, 1, it.second);
            pos += it.second.length();
        }
    }
}

int main() {
    std::cout << "Enter a line of text from the manuscript: ";
    std::string input;
    std::getline(std::cin, input);

    std::cout << "Original Text: " << input << std::endl;

    normalizeString(input);

    std::cout << "Normalized Text: " << input << std::endl;

    return 0;
}

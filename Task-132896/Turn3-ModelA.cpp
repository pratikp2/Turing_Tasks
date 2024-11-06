// Simple string rotation obfuscation
std::string obfuscateString(std::string input, int rotation) {
    std::string result = "";
    for (char ch : input) {
        result += static_cast<char>((ch - 'a' + rotation) % 26 + 'a');
    }
    return result;
}

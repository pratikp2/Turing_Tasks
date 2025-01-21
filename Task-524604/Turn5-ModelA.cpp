#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

class CodeAnalyzer {
public:
    explicit CodeAnalyzer(const std::string &filename) : filename(filename) {}

    void Analyze() {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open the file: " << filename << std::endl;
            return;
        }

        std::string line;
        size_t lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            AnalyzeLine(line, lineNumber);
        }
    }

    void PatchCode() {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open the file: " << filename << std::endl;
            return;
        }

        std::string patchedCode;
        std::string line;
        size_t lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            patchedCode += SuggestPatch(line, lineNumber) + "\n";
        }
        
        // Write patched code to a new file
        std::ofstream output("patched_" + filename);
        output << patchedCode;
        output.close();
        std::cout << "Patched code written to: patched_" << filename << std::endl;
    }

private:
    std::string filename;

    void AnalyzeLine(const std::string &line, size_t lineNumber) {
        if (line.find("strcpy") != std::string::npos) {
            std::cout << "Unsafe usage of strcpy detected at line "
                      << lineNumber << ": " << line << std::endl;
            std::cout << "Suggested fix: Use SafeStrCpy instead." << std::endl;
        }
        if (line.find("strlen") != std::string::npos) {
            std::cout << "Usage of strlen detected at line "
                      << lineNumber << ": " << line << std::endl;
            // Here you could also suggest using a safe wrapper
        }
    }

    std::string SuggestPatch(const std::string &line, size_t lineNumber) {
        // Replace unsafe strcpy with an example of SafeStrCpy (mock implementation)
        std::regex unsafeStrCpyRegex(R"(strcpy\s*\(([^,]*),\s*([^)]*)\))");
        if (std::regex_search(line, unsafeStrCpyRegex)) {
            return std::regex_replace(line, unsafeStrCpyRegex, "SafeStrCpy($1, sizeof($1), $2)");
        }
        return line; // No change
    }
};

int main() {
    CodeAnalyzer analyzer("example_code.cpp"); // Replace with your source code filename
    analyzer.Analyze();
    analyzer.PatchCode();

    return 0;
}

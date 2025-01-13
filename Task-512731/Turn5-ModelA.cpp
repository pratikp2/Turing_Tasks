#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip> // For std::setprecision
#include <stdexcept> // For std::runtime_error
#include <iterator> // For std::begin and std::end

template <typename SequenceType>
class SequenceAnalyzer {
public:
    // Constructor takes a sequence of any container type
    SequenceAnalyzer(const SequenceType& seq) : sequence(seq) {
        validateSequence();
    }

    // Count nucleotides
    std::unordered_map<char, int> countNucleotides() const {
        std::unordered_map<char, int> nucleotideCount;
        for (const auto& nucleotide : sequence) {
            if (isValidNucleotide(nucleotide)) {
                nucleotideCount[nucleotide]++;
            } else {
                throw std::runtime_error("Invalid nucleotide found in sequence.");
            }
        }
        return nucleotideCount;
    }

    // Calculate nucleotide percentages
    void calculateNucleotidePercentages() const {
        auto countMap = countNucleotides();
        int totalNucleotides = sequence.size();

        if (totalNucleotides == 0) {
            throw std::runtime_error("Empty sequence provided for analysis.");
        }

        std::cout << "Nucleotide Percentages:\n";
        for (const auto& [nucleotide, count] : countMap) {
            double percentage = (static_cast<double>(count) / totalNucleotides) * 100.0;
            std::cout << nucleotide << ": " << std::fixed << std::setprecision(2) << percentage << "%\n";
        }
        std::cout << "\n";
    }

private:
    SequenceType sequence; // The sequence of any type

    // Validate the sequence
    void validateSequence() const {
        for (const auto& nucleotide : sequence) {
            if (!isValidNucleotide(nucleotide)) {
                throw std::runtime_error("Invalid nucleotide found in input sequence.");
            }
        }
    }

    // Check if a character is a valid nucleotide
    bool isValidNucleotide(char nucleotide) const {
        return (nucleotide == 'A' || nucleotide == 'C' || nucleotide == 'G' || nucleotide == 'T');
    }
};

int main() {
    // Sample DNA sequences using different types
    std::vector<std::string> dnaSequences = {
        "AGCTAGCTAG",
        "CGTACGTACG",
        "TTAGCTAGGA",
        "AGCTAGCTTA"
    };

    // Processing each sequence using the generic SequenceAnalyzer
    for (const auto& seq : dnaSequences) {
        try {
            SequenceAnalyzer<std::string> analyzer(seq);
            analyzer.calculateNucleotidePercentages();
        } catch (const std::runtime_error& e) {
            std::cerr << "Runtime Error: " << e.what() << std::endl;
        }
    }

    // You can also process sequences of type std::vector<char>
    std::vector<char> charSequence = {'A', 'G', 'C', 'T', 'A', 'G', 'C', 'T'};
    try {
        SequenceAnalyzer<std::vector<char>> analyzer(charSequence);
        analyzer.calculateNucleotidePercentages();
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    }

    return 0;
}

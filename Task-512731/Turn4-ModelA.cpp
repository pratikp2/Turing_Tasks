#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip> // For std::setprecision
#include <stdexcept> // For std::invalid_argument

class InvalidNucleotideException : public std::invalid_argument {
public:
    explicit InvalidNucleotideException(const std::string& message) 
        : std::invalid_argument(message) {}
};

class DNASequence {
public:
    // Constructor to initialize the DNA sequence
    DNASequence(const std::string& seq) : sequence(seq) {
        validateSequence();
    }

    // Function to count nucleotides and return a frequency map
    std::unordered_map<char, int> countNucleotides() const {
        std::unordered_map<char, int> nucleotideCount;
        for (char nucleotide : sequence) {
            nucleotideCount[nucleotide]++;
        }
        return nucleotideCount;
    }

    // Function to calculate percentages of each nucleotide
    void calculateNucleotidePercentages() const {
        auto countMap = countNucleotides();
        int totalNucleotides = sequence.length();

        std::cout << "Nucleotide Percentages for Sequence: " << sequence << "\n";
        for (const auto& [nucleotide, count] : countMap) {
            double percentage = (static_cast<double>(count) / totalNucleotides) * 100.0;
            std::cout << nucleotide << ": " << std::fixed << std::setprecision(2) << percentage << "%\n";
        }
        std::cout << "\n"; // Newline for better readability
    }

    const std::string& getSequence() const {
        return sequence;
    }

private:
    std::string sequence; // The DNA sequence

    // Validate the DNA sequence for only valid nucleotides
    void validateSequence() {
        for (char nucleotide : sequence) {
            if (nucleotide != 'A' && nucleotide != 'T' && nucleotide != 'C' && nucleotide != 'G') {
                throw InvalidNucleotideException("Invalid nucleotide found: " + std::string(1, nucleotide));
            }
        }
    }
};

int main() {
    // Sample DNA sequences
    std::vector<DNASequence> dnaSequences;

    // Initialize with some sequence, including one invalid example
    std::vector<std::string> sequences = {
        "AGCTAGCTAG",
        "CGTACGTACG",
        "TTAGCTAGGA",
        "AGCTAGCTRTA" // Invalid nucleotide 'R'
    };

    // Try to create DNASequence objects and catch any validation exceptions
    for (const auto& seq : sequences) {
        try {
            dnaSequences.emplace_back(seq);
        } catch (const InvalidNucleotideException& e) {
            std::cerr << "Error: " << e.what() << "\n"; // Handle the error gracefully
        }
    }

    // Using std::for_each to apply the calculateNucleotidePercentages method to each valid DNASequence object
    std::for_each(dnaSequences.begin(), dnaSequences.end(), [](const DNASequence& seq) {
        seq.calculateNucleotidePercentages();
    });

    return 0;
}

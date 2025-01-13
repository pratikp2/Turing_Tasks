#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip> // For std::setprecision

class DNASequence {
public:
    // Constructor to initialize the DNA sequence
    DNASequence(const std::string& seq) : sequence(seq) {}

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
};

int main() {
    // Sample DNA sequences
    std::vector<DNASequence> dnaSequences = {
        DNASequence("AGCTAGCTAG"),
        DNASequence("CGTACGTACG"),
        DNASequence("TTAGCTAGGA"),
        DNASequence("AGCTAGCTTA")
    };

    // Using std::for_each to apply the calculateNucleotidePercentages method to each DNASequence object
    std::for_each(dnaSequences.begin(), dnaSequences.end(), [](const DNASequence& seq) {
        seq.calculateNucleotidePercentages();
    });

    return 0;
}

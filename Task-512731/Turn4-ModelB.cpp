#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip> // For std::setprecision
#include <stdexcept> // For std::runtime_error
#include <cassert> // For assertions

class DNASequence {
public:
    DNASequence(const std::string& seq) : sequence(seq) {
        // Validate the input sequence
        validateSequence();
    }

    std::unordered_map<char, int> countNucleotides() const {
        std::unordered_map<char, int> nucleotideCount;
        for (char nucleotide : sequence) {
            if (nucleotide == 'A' || nucleotide == 'C' || nucleotide == 'G' || nucleotide == 'T') {
                nucleotideCount[nucleotide]++;
            } else {
                throw std::runtime_error("Invalid nucleotide: '" + std::string(1, nucleotide) + "' found in sequence '" + sequence + "'");
            }
        }
        return nucleotideCount;
    }

    void calculateNucleotidePercentages() const {
        auto countMap = countNucleotides();
        int totalNucleotides = sequence.length();

        if (totalNucleotides == 0) {
            throw std::runtime_error("Empty DNA sequence provided for analysis.");
        }

        std::cout << "Nucleotide Percentages for Sequence: " << sequence << "\n";
        for (const auto& [nucleotide, count] : countMap) {
            double percentage = (static_cast<double>(count) / totalNucleotides) * 100.0;
            std::cout << nucleotide << ": " << std::fixed << std::setprecision(2) << percentage << "%\n";
        }
        std::cout << "\n";
    }

    const std::string& getSequence() const {
        return sequence;
    }

private:
    std::string sequence;

    void validateSequence() const {
        for (char nucleotide : sequence) {
            if (nucleotide != 'A' && nucleotide != 'C' && nucleotide != 'G' && nucleotide != 'T') {
                throw std::runtime_error("Invalid nucleotide: '" + std::string(1, nucleotide) + "' found in input sequence.");
            }
        }
    }
};

int main() {
    std::vector<DNASequence> dnaSequences = {
        DNASequence("AGCTAGCTAG"),
        DNASequence("CGTACGTACG"),
        DNASequence("TTAGCTAGGA"),
        DNASequence("AGCTAGCTTA"),
        DNASequence("InvalidSequence") // Test with an invalid sequence
    };

    try {
        std::for_each(dnaSequences.begin(), dnaSequences.end(), [](const DNASequence& seq) {
            seq.calculateNucleotidePercentages();
        });
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}

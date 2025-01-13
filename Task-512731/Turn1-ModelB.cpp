#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>

class GenomeAnalyzer {
    private:
        std::vector<std::string> sequences;
        std::unordered_map<char, int> kmerCounts;
    
    public:
        GenomeAnalyzer() = default;

        // Load DNA sequences from a file
        void loadGenomes(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Error: Cannot open file " << filePath << std::endl;
                return;
            }

            std::string sequence;
            while (std::getline(file, sequence)) {
                sequences.push_back(sequence);
            }
        }

        void analyze() {
            // Compute 4-mer counts using a hybrid approach
            for (const std::string& sequence : sequences) {
                if (sequence.size() < 4) {
                    continue;
                }

                for (size_t i = 0; i < sequence.size() - 3; ++i) {
                    const std::string kmer = std::string(sequence.begin() + i, sequence.begin() + i + 4);
                    auto it = kmerCounts.find(kmer.front());
                    if (it == kmerCounts.end()) {
                        kmerCounts[kmer.front()] = {kmer, 1};
                    } else {
                        ++it->second.second;
                    }
                }
            }

            // Sort kmers by their count in descending order
            std::vector<std::pair<std::string, int>> sortedKmers(kmerCounts.begin(), kmerCounts.end());
            std::sort(sortedKmers.begin(), sortedKmers.end(), [](const auto& lhs, const auto& rhs) {
                return lhs.second > rhs.second;
            });

            // Display the 10 most frequent 4-mers
            for (const auto& [kmer, count] : sortedKmers.begin()) {
                std::cout << kmer << " : " << count << std::endl;
                if (--sortedKmers.size() == 0) break;
            }
        }
};

int main() {
    GenomeAnalyzer analyzer;
    analyzer.loadGenomes("genomic_sequences.txt");  // Replace with your input file
    analyzer.analyze();

    return 0;
}

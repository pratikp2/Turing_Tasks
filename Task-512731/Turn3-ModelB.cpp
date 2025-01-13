#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <execution>
#include <thread>
#include <mutex>

std::mutex globalMutex;

class DNASequence {
public:
    DNASequence(const std::string& seq) : sequence(seq) {}

    const std::string& getSequence() const {
        return sequence;
    }

private:
    std::string sequence;
};

class NucleotidePairCounter {
public:
    void operator()(const DNASequence& seq, std::unordered_map<std::string, int>& localCount) {
        auto pairCount = seq.countNucleotidePairs();
        for (const auto& [pair, count] : pairCount) {
            localCount[pair] += count;
        }
    }
};

std::unordered_map<std::string, int> processDNARegions(const std::vector<DNASequence>& sequences) {
    std::unordered_map<std::string, int> localCount;

    // Using std::for_each with std::execution::par to parallelize processing
    std::for_each(std::execution::par, sequences.begin(), sequences.end(),
                  [&localCount](const auto& seq) {
                      NucleotidePairCounter counter;
                      counter(seq, localCount);
                  });

    return localCount;
}

int main() {
    // Sample DNA sequences
    std::vector<DNASequence> dnaSequences = {
        DNASequence("AGCTAGCTAG"),
        DNASequence("CGTACGTACG"),
        DNASequence("TTAGCTAGGA"),
        DNASequence("AGCTAGCTTA")
        // Add more sequences as needed
    };

    std::unordered_map<std::string, int> nucleotidePairCount;

    // Process sequences in parallel
    nucleotidePairCount = processDNARegions(dnaSequences);

    // Output the nucleotide pair counts
    for (const auto& [pair, count] : nucleotidePairCount) {
        std::cout << "Pair: " << pair << ", Count: " << count << std::endl;
    }

    return 0;
}

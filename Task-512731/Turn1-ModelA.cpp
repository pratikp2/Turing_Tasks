#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <thread>
#include <mutex>

class DNASequence {
public:
    DNASequence(const std::string& seq) : sequence(seq) {}

    // Function to get nucleotide pair counts
    std::unordered_map<std::string, int> countNucleotidePairs() const {
        std::unordered_map<std::string, int> pairCount;
        for (size_t i = 0; i < sequence.size() - 1; ++i) {
            std::string pair = sequence.substr(i, 2);
            pairCount[pair]++;
        }
        return pairCount;
    }

    const std::string& getSequence() const {
        return sequence;
    }

private:
    std::string sequence;
};

void mergeCounts(const std::unordered_map<std::string, int>& localCount, std::unordered_map<std::string, int>& globalCount) {
    std::lock_guard<std::mutex> guard(globalMutex);
    for (const auto& [pair, count] : localCount) {
        globalCount[pair] += count;
    }
}

std::mutex globalMutex;

void processDNARegions(const std::vector<DNASequence>& sequences, std::unordered_map<std::string, int>& globalCount) {
    for (const auto& seq : sequences) {
        auto localCount = seq.countNucleotidePairs();
        mergeCounts(localCount, globalCount);
    }
}

int main() {
    // Sample DNA sequences
    std::vector<DNASequence> dnaSequences = {
        DNASequence("AGCTAGCTAG"),
        DNASequence("CGTACGTACG"),
        DNASequence("TTAGCTAGGA"),
        DNASequence("AGCTAGCTTA")
    };

    std::unordered_map<std::string, int> nucleotidePairCount;

    // Create threads to process DNA sequences
    const size_t numThreads = std::thread::hardware_concurrency();
    size_t chunkSize = dnaSequences.size() / numThreads;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? dnaSequences.size() : start + chunkSize;

        threads.emplace_back(processDNARegions, std::vector<DNASequence>(dnaSequences.begin() + start, dnaSequences.begin() + end), std::ref(nucleotidePairCount));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Output the nucleotide pair counts
    for (const auto& [pair, count] : nucleotidePairCount) {
        std::cout << "Pair: " << pair << ", Count: " << count << std::endl;
    }

    return 0;
}

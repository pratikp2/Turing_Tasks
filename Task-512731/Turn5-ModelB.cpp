#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <memory>

template <typename T>
class DataProcessor {
public:
    using FunctionType = std::function<void(const T& element)>;

    DataProcessor(const std::vector<T>& data, const FunctionType& function)
        : data(data), function(function) {}

    void processData() const {
        if (data.empty()) {
            throw std::runtime_error("Cannot process empty data set.");
        }
        const int numThreads = std::thread::hardware_concurrency();
        size_t chunkSize = data.size() / numThreads + (data.size() % numThreads > 0 ? 1 : 0);

        std::vector<std::thread> threads;
        for (size_t i = 0; i < numThreads; ++i) {
            size_t start = i * chunkSize;
            size_t end = std::min((i + 1) * chunkSize, data.size());
            threads.emplace_back([start, end, &data, &function]() {
                for (size_t j = start; j < end; ++j) {
                    function(data[j]);
                }
            });
        }

        for (std::thread& thread : threads) {
            thread.join();
        }
    }

private:
    const std::vector<T>& data;
    FunctionType function;
};

class DNASequence {
public:
    DNASequence(const std::string& seq) : sequence(seq) {
        validateSequence();
    }

    // ... Previous methods remain the same ...

    friend void calculateNucleotidePercentages(const DNASequence& seq) {
        seq.calculateNucleotidePercentages();
    }

private:
    std::string sequence;

    void validateSequence() const {
        // ... Previous validation logic remains the same ...
    }
};

int main() {
    std::vector<DNASequence> dnaSequences = {
        DNASequence("AGCTAGCTAG"),
        DNASequence("CGTACGTACG"),
        DNASequence("TTAGCTAGGA"),
        DNASequence("AGCTAGCTTA"),
        DNASequence("InvalidSequence")
    };

    try {
        DataProcessor<DNASequence>(dnaSequences, calculateNucleotidePercentages)
            .processData();
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}

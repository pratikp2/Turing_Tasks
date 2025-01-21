#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class FeedbackRecorder {
public:
    void recordLoopIteration(int loopIndex) {
        loopCounts[loopIndex]++;
    }

    const std::unordered_map<int, int>& getLoopCounts() const {
        return loopCounts;
    }

    void reset() {
        loopCounts.clear();
    }

private:
    std::unordered_map<int, int> loopCounts; // Tracks iterations for each loop
};

void processTradeData(const std::vector<int>& tradeData, FeedbackRecorder& recorder) {
    // This user-defined threshold to decide how many times we want to adapt the loops
    const int THRESHOLD = 5;

    // Example nested loops
    for (int i = 0; i < tradeData.size(); ++i) {
        // Record the outer loop iteration
        recorder.recordLoopIteration(0); 

        for (int j = 0; j < tradeData.size(); ++j) {
            // Record the inner loop iteration
            recorder.recordLoopIteration(1); 

            // Simulate processing a trade
            std::cout << "Processing trade: " << tradeData[i] << " with related data: " << tradeData[j] << std::endl;
        }

        // Condition to dynamically adjust loop processing
        if (recorder.getLoopCounts().at(0) > THRESHOLD) {
            // Modify behavior: let's skip some iterations or change strategy for future runs
            std::cout << "Dynamically adjusting outer loop processing behavior after " 
                      << recorder.getLoopCounts().at(0) << " iterations." << std::endl;

            // For demonstration purpose, we increment the step by 2 instead of 1.
            // In reality, you could modify the trade processing strategy.
            i++; // Increment i to skip an iteration
        }
    }
}

int main() {
    // Sample trade data
    std::vector<int> tradeData = {10, 20, 30, 40, 50, 60, 70};

    // Create a feedback recorder instance
    FeedbackRecorder recorder;

    // Process the trade data with feedback monitoring
    processTradeData(tradeData, recorder);

    // Output the collected loop statistics after processing
    const auto& loopCounts = recorder.getLoopCounts();
    std::cout << "\nLoop execution counts:" << std::endl;
    for (const auto& pair : loopCounts) {
        std::cout << "Loop " << pair.first << ": " << pair.second << " iterations" << std::endl;
    }

    return 0;
}

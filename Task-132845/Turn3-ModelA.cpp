#include <thread>

void processRequest(MarkovChain& chain, int initialState) {
    // Generate time series for a single request
    vector<int> timeSeries = generateTimeSeries(chain, initialState, numSteps);
    // Handle the time series data
}

int main() {
    // ... Initialize Markov Chain ...
    int numThreads = std::thread::hardware_concurrency();
    vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(processRequest, std::ref(chain), i % chain.transitionMatrix.rows());
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    return 0;
}
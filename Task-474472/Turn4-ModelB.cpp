#include <future>

void processPartOfData(std::vector<int>& data, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        // ... process data[i]
    }
}

int main() {
    const int size = 1'000'000;
    std::vector<int> data(size);

    // ... (generate data)

    const int numThreads = 4;
    size_t chunkSize = size / numThreads + 1;

    std::vector<std::future<void>> futures;
    for (int threadId = 0; threadId < numThreads; ++threadId) {
        size_t start = threadId * chunkSize;
        size_t end = std::min((threadId + 1) * chunkSize, size);
        futures.emplace_back(std::async(std::launch::async, processPartOfData, std::ref(data), start, end));
    }

    for (auto& future : futures) {
        future.get();
    }

    return 0;
}

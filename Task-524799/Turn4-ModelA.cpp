#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <vector>

class ProtocolHandler {
public:
    virtual ~ProtocolHandler() = default;
    virtual void handle() = 0;
};

class HttpHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handle HTTP
    }
};

class FtpHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handle FTP
    }
};

class SmtpHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handle SMTP
    }
};

class UnknownProtocolHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handle unknown protocol
    }
};

std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocolStr) {
    if (protocolStr == "HTTP") {
        return std::make_unique<HttpHandler>();
    } else if (protocolStr == "FTP") {
        return std::make_unique<FtpHandler>();
    } else if (protocolStr == "SMTP") {
        return std::make_unique<SmtpHandler>();
    } else {
        return std::make_unique<UnknownProtocolHandler>();
    }
}

void handleWithSwitch(const std::string& protocolStr) {
    if (protocolStr == "HTTP") {
        HttpHandler().handle();
    } else if (protocolStr == "FTP") {
        FtpHandler().handle();
    } else if (protocolStr == "SMTP") {
        SmtpHandler().handle();
    } else {
        UnknownProtocolHandler().handle();
    }
}

void runBenchmark(bool usePolymorphism, int numRequests) {
    std::vector<std::string> protocols{"HTTP", "FTP", "SMTP", "UNKNOWN_PROTOCOL"};
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRequests; ++i) {
        // Here we will randomly select a protocol from the list to simulate a real-world situation
        std::string protocolStr = protocols[i % protocols.size()];

        if (usePolymorphism) {
            std::unique_ptr<ProtocolHandler> handler = createHandler(protocolStr);
            handler->handle();
        } else {
            handleWithSwitch(protocolStr);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken for " << (usePolymorphism ? "Polymorphism" : "Switch") 
              << " handling: " << duration.count() << " seconds." << std::endl;
}

int main() {
    const int numRequests = 1000000; // Number of requests to handle

    std::cout << "Benchmarking Switch Statement:" << std::endl;
    runBenchmark(false, numRequests);

    std::cout << "Benchmarking Polymorphic Approach:" << std::endl;
    runBenchmark(true, numRequests);

    return 0;
}

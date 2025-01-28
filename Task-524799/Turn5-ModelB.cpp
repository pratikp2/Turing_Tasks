#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
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
        std::cout << "Handling HTTP request." << std::endl;
    }
};

class FtpHandler : public ProtocolHandler {
public:
    void handle() override {
        std::cout << "Handling FTP request." << std::endl;
    }
};

class SmtpHandler : public ProtocolHandler {
public:
    void handle() override {
        std::cout << "Handling SMTP request." << std::endl;
    }
};

class UnknownProtocolHandler : public ProtocolHandler {
public:
    void handle() override {
        std::cout << "Unknown protocol." << std::endl;
    }
};

std::unordered_map<std::string, std::function<std::unique_ptr<ProtocolHandler>()>> protocolFactory;

void registerProtocol(const std::string& protocolStr, std::function<std::unique_ptr<ProtocolHandler>()> creator) {
    protocolFactory[protocolStr] = std::move(creator);
}

std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocolStr) {
    auto it = protocolFactory.find(protocolStr);
    if (it != protocolFactory.end()) {
        return it->second();
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
    std::vector<std::string> protocols{"HTTP", "FTP", "SMTP", "UNKNOWN_PROTOCOL", "POP3"};
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRequests; ++i) {
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
    const int numRequests = 1000000;

    // Register existing protocols
    registerProtocol("HTTP", [] { return std::make_unique<HttpHandler>(); });
    registerProtocol("FTP", [] { return std::make_unique<FtpHandler>(); });
    registerProtocol("SMTP", [] { return std::make_unique<SmtpHandler>(); });

    std::cout << "Benchmarking Switch Statement:" << std::endl;
    runBenchmark(false, numRequests);

    std::cout << "Benchmarking Polymorphic Approach:" << std::endl;
    runBenchmark(true, numRequests);

    // Add a new protocol dynamically without modifying existing code
    registerProtocol("POP3", [] { return std::make_unique<UnknownProtocolHandler>(); });

    return 0;
}

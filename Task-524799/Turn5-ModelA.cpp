#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <vector>
#include <functional>

// ProtocolHandler base class
class ProtocolHandler {
public:
    virtual ~ProtocolHandler() = default;
    virtual void handle() = 0;
};

// Concrete ProtocolHandler classes
class HttpHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handling HTTP
        std::cout << "Handling HTTP request." << std::endl;
    }
};

class FtpHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handling FTP
        std::cout << "Handling FTP request." << std::endl;
    }
};

class SmtpHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handling SMTP
        std::cout << "Handling SMTP request." << std::endl;
    }
};

class UnknownProtocolHandler : public ProtocolHandler {
public:
    void handle() override {
        // Simulated logic for handling unknown protocol
        std::cout << "Unknown protocol." << std::endl;
    }
};

// ProtocolFactory for registering and creating handlers
class ProtocolFactory {
public:
    using HandlerCreator = std::function<std::unique_ptr<ProtocolHandler>()>;

    // Register a handler function for a given protocol
    void registerHandler(const std::string& protocol, HandlerCreator creator) {
        handlers_[protocol] = creator;
    }

    // Create a handler for a given protocol
    std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocol) const {
        auto it = handlers_.find(protocol);
        if (it != handlers_.end()) {
            return it->second();
        }
        return std::make_unique<UnknownProtocolHandler>();
    }

private:
    std::unordered_map<std::string, HandlerCreator> handlers_;
};

// Global factory instance
ProtocolFactory factory;

// Function to register default handlers
void registerDefaultHandlers() {
    factory.registerHandler("HTTP", []() { return std::make_unique<HttpHandler>(); });
    factory.registerHandler("FTP", []() { return std::make_unique<FtpHandler>(); });
    factory.registerHandler("SMTP", []() { return std::make_unique<SmtpHandler>(); });
}

// Function to run performance benchmark
void runBenchmark(bool usePolymorphism, int numRequests) {
    std::vector<std::string> protocols{"HTTP", "FTP", "SMTP", "UNKNOWN_PROTOCOL"};
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numRequests; ++i) {
        std::string protocolStr = protocols[i % protocols.size()];

        if (usePolymorphism) {
            auto handler = factory.createHandler(protocolStr);
            handler->handle();
        } else {
            // Simulate handling with switch statement
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
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken for " << (usePolymorphism ? "Polymorphic" : "Switch") 
              << " handling: " << duration.count() << " seconds." << std::endl;
}

// Main function
int main() {
    // Register default handlers
    registerDefaultHandlers();

    // Benchmarking
    const int numRequests = 100000; // Number of requests to handle; can be adjusted for testing

    std::cout << "Benchmarking Switch Statement:" << std::endl;
    runBenchmark(false, numRequests);

    std::cout << "Benchmarking Polymorphic Approach:" << std::endl;
    runBenchmark(true, numRequests);

    // Example of dynamically registering a new protocol handler
    factory.registerHandler("CustomProtocol", []() {
        class CustomProtocolHandler : public ProtocolHandler {
        public:
            void handle() override {
                std::cout << "Handling Custom Protocol request." << std::endl;
            }
        };

        return std::make_unique<CustomProtocolHandler>();
    });

    // Testing new handler
    auto customHandler = factory.createHandler("CustomProtocol");
    customHandler->handle();

    return 0;
}

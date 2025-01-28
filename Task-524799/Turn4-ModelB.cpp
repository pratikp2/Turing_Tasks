#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <chrono>

class ProtocolHandler {
public:
    virtual ~ProtocolHandler() = default;
    virtual void handle() = 0;
};

class HttpHandler : public ProtocolHandler {
public:
    void handle() override {
    }
};

class FtpHandler : public ProtocolHandler {
public:
    void handle() override {
    }
};

class SmtpHandler : public ProtocolHandler {
public:
    void handle() override {
    }
};

class UnknownProtocolHandler : public ProtocolHandler {
public:
    void handle() override {
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

void dispatchRequestPolymorphism(const std::string& protocolStr) {
    std::unique_ptr<ProtocolHandler> handler = createHandler(protocolStr);
    handler->handle();
}

Protocol getProtocolFromString(const std::string& protocolStr)
{
    if (protocolStr == "HTTP") return Protocol::HTTP;
    if (protocolStr == "FTP") return Protocol::FTP;
    if (protocolStr == "SMTP") return Protocol::SMTP;
    return Protocol::UNKNOWN;
}

void handleHTTP()
{
}

void handleFTP()
{
}

void handleSMTP()
{
}

void handleUnknown()
{
}

void dispatchRequestSwitch(const std::string& protocolStr)
{
    Protocol protocol = getProtocolFromString(protocolStr);

    switch (protocol)
    {
        case Protocol::HTTP:
            handleHTTP();
            break;
        case Protocol::FTP:
            handleFTP();
            break;
        case Protocol::SMTP:
            handleSMTP();
            break;
        default:
            handleUnknown();
            break;
    }
}

double measure_throughput(const std::function<void(const std::string&)>& dispatchFunction, const std::vector<std::string>& protocols, int numIterations) {
    std::cout << "Measuring throughput..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numIterations; ++i) {
        for (const auto& protocol : protocols) {
            dispatchFunction(protocol);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    int totalRequests = numIterations * protocols.size();
    double throughput = totalRequests / (duration.count() / 1000.0); // Throughput in requests per second

    return throughput;
}

int main() {
    const std::vector<std::string> protocols = {
        "HTTP", "FTP", "SMTP", "UNKNOWN_PROTOCOL", "HTTP", "FTP", "SMTP", "UNKNOWN_PROTOCOL"
    };
    const int numIterations = 1000000;

    std::cout << "Benchmarking Protocol Handling:" << std::endl;

    double throughputSwitch = measure_throughput(dispatchRequestSwitch, protocols, numIterations);
    std::cout << "Throughput (switch statement): " << throughputSwitch << " requests per second" << std::endl;
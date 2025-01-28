#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

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

int main() {
    std::unordered_map<int, std::string> incomingRequests = {
        {1, "HTTP"}, {2, "FTP"}, {3, "SMTP"}, {4, "UNKNOWN_PROTOCOL"}
    };

    for (const auto& request : incomingRequests) {
        std::cout << "Request ID: " << request.first << ", Protocol: " << request.second << std::endl;
        std::unique_ptr<ProtocolHandler> handler = createHandler(request.second);
        handler->handle();
    }

    return 0;
}

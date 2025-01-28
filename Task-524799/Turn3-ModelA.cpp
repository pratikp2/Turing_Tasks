#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

// Base Protocol Handler class
class ProtocolHandler
{
public:
    virtual ~ProtocolHandler() = default; // Virtual Destructor
    virtual void handleRequest() = 0; // Pure virtual function to handle request
};

// HTTP Handler
class HttpHandler : public ProtocolHandler
{
public:
    void handleRequest() override
    {
        std::cout << "Handling HTTP request." << std::endl;
        // Implement HTTP processing logic
    }
};

// FTP Handler
class FtpHandler : public ProtocolHandler
{
public:
    void handleRequest() override
    {
        std::cout << "Handling FTP request." << std::endl;
        // Implement FTP processing logic
    }
};

// SMTP Handler
class SmtpHandler : public ProtocolHandler
{
public:
    void handleRequest() override
    {
        std::cout << "Handling SMTP request." << std::endl;
        // Implement SMTP processing logic
    }
};

// Protocol Factory
class ProtocolHandlerFactory
{
public:
    static std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocol)
    {
        if (protocol == "HTTP") {
            return std::make_unique<HttpHandler>();
        } else if (protocol == "FTP") {
            return std::make_unique<FtpHandler>();
        } else if (protocol == "SMTP") {
            return std::make_unique<SmtpHandler>();
        } else {
            return nullptr; // No handler for unknown protocols
        }
    }
};

// Example usage
int main()
{
    // Simulating incoming requests
    std::vector<std::string> incomingRequests = {"HTTP", "FTP", "SMTP", "UNKNOWN"};

    for (const auto& protocol : incomingRequests)
    {
        std::cout << "Request Protocol: " << protocol << std::endl;
        
        auto handler = ProtocolHandlerFactory::createHandler(protocol);
        if (handler) {
            handler->handleRequest();
        } else {
            std::cout << "No handler for this protocol." << std::endl;
        }
    }

    return 0;
}

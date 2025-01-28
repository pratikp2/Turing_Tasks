#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

enum class Protocol
{
    HTTP,
    FTP,
    SMTP,
    UNKNOWN
};

Protocol getProtocolFromString(const std::string& protocolStr)
{
    if (protocolStr == "HTTP") return Protocol::HTTP;
    if (protocolStr == "FTP") return Protocol::FTP;
    if (protocolStr == "SMTP") return Protocol::SMTP;
    return Protocol::UNKNOWN;
}

void handleHTTP()
{
    std::cout << "Handling HTTP request." << std::endl;
    // HTTP handling logic goes here
}

void handleFTP()
{
    std::cout << "Handling FTP request." << std::endl;
    // FTP handling logic goes here
}

void handleSMTP()
{
    std::cout << "Handling SMTP request." << std::endl;
    // SMTP handling logic goes here
}

void handleUnknown()
{
    std::cout << "Unknown protocol." << std::endl;
}

void dispatchRequest(const std::string& protocolStr)
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

int main()
{
    // Simulating incoming requests
    std::unordered_map<int, std::string> incomingRequests = {
        {1, "HTTP"},
        {2, "FTP"},
        {3, "SMTP"},
        {4, "UNKNOWN_PROTOCOL"}
    };

    for (const auto& request : incomingRequests)
    {
        std::cout << "Request ID: " << request.first << ", Protocol: " << request.second << std::endl;
        dispatchRequest(request.second);
    }

    return 0;
}

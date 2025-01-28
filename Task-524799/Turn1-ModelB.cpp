#include <iostream>
#include <string>
#include <unordered_map>

enum class Protocol {
    HTTP,
    FTP,
    SMTP,
    UNKNOWN
};

void handleHTTP(const std::string& request) {
    std::cout << "Handling HTTP request: " << request << std::endl;
}

void handleFTP(const std::string& request) {
    std::cout << "Handling FTP request: " << request << std::endl;
}

void handleSMTP(const std::string& request) {
    std::cout << "Handling SMTP request: " << request << std::endl;
}

void handleUnknownProtocol(const std::string& request) {
    std::cout << "Unknown protocol request: " << request << std::endl;
}

void processProtocol(const std::string& protocolStr, const std::string& request) {
    Protocol protocol;
    if (protocolStr == "HTTP") {
        protocol = Protocol::HTTP;
    } else if (protocolStr == "FTP") {
        protocol = Protocol::FTP;
    } else if (protocolStr == "SMTP") {
        protocol = Protocol::SMTP;
    } else {
        protocol = Protocol::UNKNOWN;
    }

    switch (protocol) {
        case Protocol::HTTP:
            handleHTTP(request);
            break;
        case Protocol::FTP:
            handleFTP(request);
            break;
        case Protocol::SMTP:
            handleSMTP(request);
            break;
        case Protocol::UNKNOWN:
            handleUnknownProtocol(request);
            break;
    }
}

int main() {
    std::string protocol, request;
    while (std::getline(std::cin, protocol, ' ') && std::getline(std::cin, request)) {
        processProtocol(protocol, request);
    }

    return 0;
}

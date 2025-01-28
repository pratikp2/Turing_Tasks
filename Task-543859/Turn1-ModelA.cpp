#include <iostream>
#include <string>

enum Protocol {
    TCP,
    UDP,
    ICMP,
    UNKNOWN
};

void handleTCP() {
    std::cout << "Handling TCP protocol." << std::endl;
    // Add TCP handling logic here
}

void handleUDP() {
    std::cout << "Handling UDP protocol." << std::endl;
    // Add UDP handling logic here
}

void handleICMP() {
    std::cout << "Handling ICMP protocol." << std::endl;
    // Add ICMP handling logic here
}

void handleUnknown() {
    std::cout << "Unknown protocol!" << std::endl;
}

Protocol getProtocolFromInput(const std::string& protocolStr) {
    if (protocolStr == "TCP") return TCP;
    else if (protocolStr == "UDP") return UDP;
    else if (protocolStr == "ICMP") return ICMP;
    else return UNKNOWN;
}

void processPacket(const std::string& protocolStr) {
    Protocol protocol = getProtocolFromInput(protocolStr);

    switch (protocol) {
        case TCP:
            handleTCP();
            break;
        case UDP:
            handleUDP();
            break;
        case ICMP:
            handleICMP();
            break;
        default:
            handleUnknown();
            break;
    }
}

int main() {
    std::string protocol;
    std::cout << "Enter the protocol (TCP, UDP, ICMP): ";
    std::cin >> protocol;

    processPacket(protocol);

    return 0;
}

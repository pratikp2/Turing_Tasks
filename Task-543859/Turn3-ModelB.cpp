#include <iostream>
#include <string>

enum Protocol {
    TCP,
    UDP,
    ICMP,
    UNKNOWN
};

// Logging class with predefined verbosity levels
class Logger {
public:
    enum Verbosity { DEBUG, INFO, WARNING, ERROR };
    Logger(Verbosity verbosity = INFO) : verbosity(verbosity) {}
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

private:
    Verbosity verbosity;
};

void Logger::debug(const std::string& message) {
    if (verbosity <= DEBUG) {
        std::cout << "[DEBUG] " << message << std::endl;
    }
}

void Logger::info(const std::string& message) {
    if (verbosity <= INFO) {
        std::cout << "[INFO] " << message << std::endl;
    }
}

void Logger::warning(const std::string& message) {
    if (verbosity <= WARNING) {
        std::cout << "[WARNING] " << message << std::endl;
    }
}

void Logger::error(const std::string& message) {
    std::cout << "[ERROR] " << message << std::endl;
}


void handleTCP(Logger& logger) {
    logger.debug("Entering handleTCP()");
    // Add TCP handling logic here
    logger.debug("Exiting handleTCP()");
}

void handleUDP(Logger& logger) {
    logger.debug("Entering handleUDP()");
    // Add UDP handling logic here
    logger.debug("Exiting handleUDP()");
}

void handleICMP(Logger& logger) {
    logger.debug("Entering handleICMP()");
    // Add ICMP handling logic here
    logger.error("Simulating ICMP error logic...");  // log error for demonstration
    logger.debug("Exiting handleICMP()");
}

void handleUnknown(Logger& logger) {
    logger.debug("Entering handleUnknown()");
    logger.error("Unknown protocol!");
    logger.debug("Exiting handleUnknown()");
}

Protocol getProtocolFromInput(const std::string& protocolStr) {
    if (protocolStr == "TCP") return TCP;
    else if (protocolStr == "UDP") return UDP;
    else if (protocolStr == "ICMP") return ICMP;
    else return UNKNOWN;
}

void processPacket(const std::string& protocolStr) {
    Logger logger(Logger::DEBUG);
    Protocol protocol = getProtocolFromInput(protocolStr);

    logger.info("Processing packet protocol: " + protocolStr);

    switch (protocol) {
        case TCP:
            handleTCP(logger);
            break;
        case UDP:
            handleUDP(logger);
            break;
        case ICMP:
            handleICMP(logger);
            break;
        default:
            handleUnknown(logger);
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

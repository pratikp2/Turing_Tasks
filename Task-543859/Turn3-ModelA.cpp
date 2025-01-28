#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

enum class LogLevel {
    INFO,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile) {
            std::cerr << "Failed to open log file!" << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(LogLevel level, const std::string& message) {
        if (logFile.is_open()) {
            std::string levelStr = (level == LogLevel::INFO) ? "INFO" : "ERROR";
            logFile << getCurrentTime() << " [" << levelStr << "] " << message << std::endl;
        }
    }

private:
    std::ofstream logFile;

    std::string getCurrentTime() {
        std::time_t now = std::time(0);
        char buf[80];
        std::tm tstruct = *std::localtime(&now);
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return buf;
    }
};

enum Protocol {
    TCP,
    UDP,
    ICMP,
    UNKNOWN
};

Logger logger("protocol_log.txt");

void handleTCP() {
    logger.log(LogLevel::INFO, "Entering handleTCP()");
    // Add TCP handling logic here
    // Simulating an operation
    logger.log(LogLevel::INFO, "Exiting handleTCP()");
}

void handleUDP() {
    logger.log(LogLevel::INFO, "Entering handleUDP()");
    // Add UDP handling logic here
    // Simulating an operation
    logger.log(LogLevel::INFO, "Exiting handleUDP()");
}

void handleICMP() {
    logger.log(LogLevel::INFO, "Entering handleICMP()");
    // Add ICMP handling logic here
    // Simulating an operation
    logger.log(LogLevel::INFO, "Exiting handleICMP()");
}

void handleUnknown() {
    logger.log(LogLevel::ERROR, "Unknown protocol handler invoked!");
}

Protocol getProtocolFromInput(const std::string& protocolStr) {
    if (protocolStr == "TCP") return TCP;
    else if (protocolStr == "UDP") return UDP;
    else if (protocolStr == "ICMP") return ICMP;
    else return UNKNOWN;
}

void processPacket(const std::string& protocolStr) {
    Protocol protocol = getProtocolFromInput(protocolStr);
    logger.log(LogLevel::INFO, "Processing packet with protocol: " + protocolStr);

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

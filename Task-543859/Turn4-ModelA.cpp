#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <functional>

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

// Protocol handler functions
void handleTCP() {
    logger.log(LogLevel::INFO, "Entering handleTCP()");
    // TCP handling logic
    logger.log(LogLevel::INFO, "Exiting handleTCP()");
}

void handleUDP() {
    logger.log(LogLevel::INFO, "Entering handleUDP()");
    // UDP handling logic
    logger.log(LogLevel::INFO, "Exiting handleUDP()");
}

void handleICMP() {
    logger.log(LogLevel::INFO, "Entering handleICMP()");
    // ICMP handling logic
    logger.log(LogLevel::INFO, "Exiting handleICMP()");
}

void handleUnknown() {
    logger.log(LogLevel::ERROR, "Unknown protocol handler invoked!");
}

// Global logger instance
Logger logger("protocol_log.txt");

// Create a type alias for the handler function pointer
using HandlerFunction = std::function<void()>;

// Mapping between protocol strings and handler functions
std::map<std::string, HandlerFunction> protocolHandlers = {
    {"TCP", handleTCP},
    {"UDP", handleUDP},
    {"ICMP", handleICMP}
};

void processPacket(const std::string& protocolStr) {
    logger.log(LogLevel::INFO, "Processing packet with protocol: " + protocolStr);
    
    auto it = protocolHandlers.find(protocolStr);
    if (it != protocolHandlers.end()) {
        it->second(); // Call the appropriate handler function
    } else {
        handleUnknown(); // Call the unknown handler if not found
    }
}

int main() {
    std::string protocol;
    
    std::cout << "Enter the protocol (TCP, UDP, ICMP): ";
    std::cin >> protocol;

    processPacket(protocol);

    return 0;
}

#include <iostream>

// Base class for LoggingPolicy
class LoggingPolicy {
public:
    virtual void logMessage(const std::string& message) const = 0;
    virtual ~LoggingPolicy() = default;
};

// Base class for AuthenticationPolicy
class AuthenticationPolicy {
public:
    virtual bool authenticate(const std::string& username, const std::string& password) const = 0;
    virtual ~AuthenticationPolicy() = default;
};

// Base class for DataCompressionPolicy
class DataCompressionPolicy {
public:
    virtual std::string compressData(const std::string& data) const = 0;
    virtual std::string decompressData(const std::string& compressedData) const = 0;
    virtual ~DataCompressionPolicy() = default;
};


// Concrete implementation of LoggingPolicy: ConsoleLoggingPolicy
class ConsoleLoggingPolicy : public LoggingPolicy {
public:
    void logMessage(const std::string& message) const override {
        std::cout << "Console: " << message << std::endl;
    }
};

// Concrete implementation of AuthenticationPolicy: SimpleAuthenticationPolicy
class SimpleAuthenticationPolicy : public AuthenticationPolicy {
public:
    bool authenticate(const std::string& username, const std::string& password) const override {
        // Simple authentication for demonstration purposes
        return username == "example" && password == "password";
    }
};

// Concrete implementation of DataCompressionPolicy: NoCompressionPolicy
class NoCompressionPolicy : public DataCompressionPolicy {
public:
    std::string compressData(const std::string& data) const override {
        return data;
    }

    std::string decompressData(const std::string& compressedData) const override {
        return compressedData;
    }
};


template <typename LoggingT, typename AuthenticationT, typename CompressionT>
class NetworkApplication {
public:
    NetworkApplication(const LoggingT& loggingPolicy, const AuthenticationT& authenticationPolicy, const CompressionT& compressionPolicy)
        : loggingPolicy(loggingPolicy), authenticationPolicy(authenticationPolicy), compressionPolicy(compressionPolicy) {}

    void processClientRequest(const std::string& username, const std::string& password, const std::string& data) {
        if (authenticationPolicy.authenticate(username, password)) {
            std::string compressedData = compressionPolicy.compressData(data);
            loggingPolicy.logMessage("Processing request from " + username + ": " + compressedData);
            // Further processing with the compressed data
            // ...
            std::string response = compressionPolicy.decompressData(compressedData);
            // Send response
        } else {
            loggingPolicy.logMessage("Authentication failed for " + username);
        }
    }

private:
    const LoggingT& loggingPolicy;
    const AuthenticationT& authenticationPolicy;
    const CompressionT& compressionPolicy;
};

int main() {
    // Create policy instances
    ConsoleLoggingPolicy loggingPolicy;
    SimpleAuthenticationPolicy authenticationPolicy;
    NoCompressionPolicy compressionPolicy;

    // Use the NetworkApplication with the selected policies
    NetworkApplication<ConsoleLoggingPolicy, SimpleAuthenticationPolicy, NoCompressionPolicy> app(
        loggingPolicy, authenticationPolicy, compressionPolicy
    );

    app.processClientRequest("example", "password", "Hello, this is a test message!");
    app.processClientRequest("invalid", "user", "Another test message");

    return 0;
}

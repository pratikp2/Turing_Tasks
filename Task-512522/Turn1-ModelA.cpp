#include <iostream>
#include <string>

// Policy Interface
template <typename T>
class LoggingPolicy {
public:
    virtual void log(const std::string& message) = 0;
};

template <typename T>
class AuthenticationPolicy {
public:
    virtual bool authenticate(const T& user) = 0;
};

template <typename T>
class CompressionPolicy {
public:
    virtual void compress(T& data) = 0;
};

// Default implementations for policies
template <typename T>
class ConsoleLogging : public LoggingPolicy<T> {
public:
    void log(const std::string& message) override {
        std::cout << "Log: " << message << std::endl;
    }
};

template <typename T>
class NoAuthentication : public AuthenticationPolicy<T> {
public:
    bool authenticate(const T&) override {
        return true; // No authentication
    }
};

template <typename T>
class NoCompression : public CompressionPolicy<T> {
public:
    void compress(T&) override {
        // No compression
    }
};

// NetworkApplication using policy templates
template <typename T, typename LogPolicy, typename AuthPolicy, typename CompPolicy>
class NetworkApplication {
public:
    NetworkApplication(LogPolicy logPolicy, AuthPolicy authPolicy, CompPolicy compPolicy)
        : logger(logPolicy), authenticator(authPolicy), compressor(compPolicy) {}

    void run(const T& user, T& data) {
        if (authenticator.authenticate(user)) {
            logger.log("User authenticated.");
            compressor.compress(data);
            logger.log("Data processed.");
        } else {
            logger.log("Authentication failed.");
        }
    }

private:
    LogPolicy logger;
    AuthPolicy authenticator;
    CompPolicy compressor;
};

// Example usage
int main() {
    ConsoleLogging<std::string> logger;
    NoAuthentication<std::string> auth;
    NoCompression<std::string> compressor;

    NetworkApplication<std::string, ConsoleLogging<std::string>, NoAuthentication<std::string>, NoCompression<std::string>> app(logger, auth, compressor);
    
    std::string user = "user123";
    std::string data = "Sensitive data";

    app.run(user, data);

    return 0;
}

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

template <typename T>
class EncryptionPolicy {
public:
    virtual void encrypt(T& data) = 0;
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

template <typename T>
class NoEncryption : public EncryptionPolicy<T> {
public:
    void encrypt(T&) override {
        // No encryption
    }
};

// New Encryption Policy
template <typename T>
class SimpleEncryption : public EncryptionPolicy<T> {
public:
    void encrypt(T& data) override {
        // Simple encryption: Reverse the string
        std::reverse(data.begin(), data.end());
    }
};

// NetworkApplication using policy templates
template <typename T, typename LogPolicy, typename AuthPolicy, typename CompPolicy, typename EncPolicy>
class NetworkApplication {
public:
    NetworkApplication(LogPolicy logPolicy, AuthPolicy authPolicy, CompPolicy compPolicy, EncPolicy encPolicy)
        : logger(logPolicy), authenticator(authPolicy), compressor(compPolicy), encryptor(encPolicy) {}

    void run(const T& user, T& data) {
        if (authenticator.authenticate(user)) {
            logger.log("User authenticated.");
            encryptor.encrypt(data);
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
    EncPolicy encryptor;
};

// Example usage
int main() {
    ConsoleLogging<std::string> logger;
    NoAuthentication<std::string> auth;
    NoCompression<std::string> compressor;
    SimpleEncryption<std::string> encryptor;

    NetworkApplication<std::string, ConsoleLogging<std::string>, NoAuthentication<std::string>, NoCompression<std::string>, SimpleEncryption<std::string>> app(logger, auth, compressor, encryptor);

    std::string user = "user123";
    std::string data = "Sensitive data";

    app.run(user, data);
    std::cout << "Encrypted and Compressed Data: " << data << std::endl;

    return 0;
}

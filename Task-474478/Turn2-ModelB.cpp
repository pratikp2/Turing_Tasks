#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// Implementor Interface
class FileHandler {
public:
    virtual ~FileHandler() = default;
    virtual void writeToFile(const std::string& content) = 0;
    virtual std::string readFromFile() = 0;
};

// Concrete Implementor for local file system
class LocalFileHandler : public FileHandler {
public:
    void writeToFile(const std::string& content) override {
        std::ofstream file("example.txt");
        if (file.is_open()) {
            file << content;
            file.close();
        } else {
            std::cerr << "Failed to open file." << std::endl;
        }
    }

    std::string readFromFile() override {
        std::ifstream file("example.txt");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    }
};

// Concrete Implementor for cloud storage
class CloudFileHandler : public FileHandler {
public:
    void writeToFile(const std::string& content) override {
        std::cout << "Writing to cloud storage." << std::endl;
        // Implementation for cloud storage write
    }

    std::string readFromFile() override {
        std::cout << "Reading from cloud storage." << std::endl;
        // Implementation for cloud storage read
        return "";
    }
};

// Abstraction
class FileManager {
protected:
    std::unique_ptr<FileHandler> handler;

public:
    FileManager(std::unique_ptr<FileHandler> handler) : handler(std::move(handler)) {}

    void writeContent(const std::string& content) {
        handler->writeToFile(content);
    }

    std::string readContent() {
        return handler->readFromFile();
    }
};

// Client code
int main() {
    // Using local file handler
    std::unique_ptr<FileHandler> localHandler = std::make_unique<LocalFileHandler>();
    FileManager fileManagerLocal(std::move(localHandler));
    fileManagerLocal.writeContent("Hello, World!");
    std::cout << "Read from local file: " << fileManagerLocal.readContent() << std::endl;

    // Using cloud file handler
    std::unique_ptr<FileHandler> cloudHandler = std::make_unique<CloudFileHandler>();
    FileManager fileManagerCloud(std::move(cloudHandler));
    fileManagerCloud.writeContent("Hello, Cloud!");
    std::cout << "Read from cloud file: " << fileManagerCloud.readContent() << std::endl;

    return 0;
}

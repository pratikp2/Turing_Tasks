#include <iostream>
#include <memory>

// Implementor Interface
class FileFormat {
public:
    virtual ~FileFormat() = default;
    virtual void read() = 0;
    virtual void write() = 0;
};

// Concrete Implementors
class JsonFormat : public FileFormat {
public:
    void read() override {
        std::cout << "Reading from JSON format" << std::endl;
    }

    void write() override {
        std::cout << "Writing to JSON format" << std::endl;
    }
};

class XmlFormat : public FileFormat {
public:
    void read() override {
        std::cout << "Reading from XML format" << std::endl;
    }

    void write() override {
        std::cout << "Writing to XML format" << std::endl;
    }
};

// Abstraction
class FileProcessor {
protected:
    std::unique_ptr<FileFormat> fileFormat;

public:
    FileProcessor(std::unique_ptr<FileFormat> format) : fileFormat(std::move(format)) {}

    virtual void process() {
        fileFormat->read();
        fileFormat->write();
    }
};

// Refined Abstraction
class AdvancedFileProcessor : public FileProcessor {
public:
    AdvancedFileProcessor(std::unique_ptr<FileFormat> format) 
        : FileProcessor(std::move(format)) {}

    void process() override {
        std::cout << "Processing file using advanced processor:" << std::endl;
        FileProcessor::process();
    }
};

// Client code
int main() {
    std::unique_ptr<FileFormat> jsonFormat = std::make_unique<JsonFormat>();
    AdvancedFileProcessor jsonProcessor(std::move(jsonFormat));
    jsonProcessor.process();

    std::unique_ptr<FileFormat> xmlFormat = std::make_unique<XmlFormat>();
    AdvancedFileProcessor xmlProcessor(std::move(xmlFormat));
    xmlProcessor.process();

    return 0;
}

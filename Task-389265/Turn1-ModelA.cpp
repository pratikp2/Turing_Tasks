#include <iostream>
#include <assert.h>
#include <cstring>

// Interface
class DataProcessor {
public:
    virtual void processData(char* buffer, int size) = 0;
};

// Concrete Product Class 1
class SafeDataProcessor : public DataProcessor {
public:
    void processData(char* buffer, int size) override {
        assert(buffer != nullptr && size > 0 && size < 100); // Assertion for input validation
        std::cout << "Processing safe data: " << buffer << std::endl;
    }
};

// Concrete Product Class 2
class UnsafeDataProcessor : public DataProcessor {
public:
    void processData(char* buffer, int size) override {
        std::cout << "Processing unsafe data: " << buffer << std::endl;
    }
};

// Factory Class
class DataProcessorFactory {
public:
    virtual DataProcessor* createProduct() = 0;
};

// Concrete Factory Class 1
class SafeDataProcessorFactory : public DataProcessorFactory {
public:
    DataProcessor* createProduct() override {
        return new SafeDataProcessor();
    }
};

// Concrete Factory Class 2
class UnsafeDataProcessorFactory : public DataProcessorFactory {
public:
    DataProcessor* createProduct() override {
        return new UnsafeDataProcessor();
    }
};

// Client Code
int main() {
    DataProcessorFactory* factory = new SafeDataProcessorFactory();
    DataProcessor* processor = factory->createProduct();

    char buffer[20] = "Hello, World!";
    processor->processData(buffer, sizeof(buffer));

    delete processor;
    delete factory;

    return 0;
}
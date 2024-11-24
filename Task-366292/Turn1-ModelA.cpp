#include <iostream>
#include <string>

// Interface for UserInputHandler
class UserInputHandlerInterface {
public:
    virtual std::string getUserInput() = 0;
    virtual bool validateInput(const std::string& input) = 0;
};

// Implementation of UserInputHandlerInterface
class ConsoleUserInputHandler : public UserInputHandlerInterface {
public:
    std::string getUserInput() override {
        std::string input;
        std::cout << "Enter data: ";
        std::cin >> input;
        return input;
    }

    bool validateInput(const std::string& input) override {
        // Example validation: non-empty string
        return !input.empty();
    }
};

// Interface for DataProcessor
class DataProcessorInterface {
public:
    virtual void processData(const std::string& data) = 0;
};

// Implementation of DataProcessorInterface
class SimpleDataProcessor : public DataProcessorInterface {
public:
    void processData(const std::string& data) override {
        // Example processing: uppercase the input
        std::cout << "Processed Data: " << data << std::endl;
    }
};

// Orchestrating class
class Application {
private:
    std::unique_ptr<UserInputHandlerInterface> inputHandler;
    std::unique_ptr<DataProcessorInterface> dataProcessor;

public:
    Application(std::unique_ptr<UserInputHandlerInterface> inputHandler, 
                std::unique_ptr<DataProcessorInterface> dataProcessor)
        : inputHandler(std::move(inputHandler)), dataProcessor(std::move(dataProcessor)) {}

    void run() {
        std::string input = inputHandler->getUserInput();
        if (inputHandler->validateInput(input)) {
            dataProcessor->processData(input);
        } else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
};

int main() {
    auto inputHandler = std::make_unique<ConsoleUserInputHandler>();
    auto dataProcessor = std::make_unique<SimpleDataProcessor>();
    Application app(std::move(inputHandler), std::move(dataProcessor));
    app.run();

    return 0;
}
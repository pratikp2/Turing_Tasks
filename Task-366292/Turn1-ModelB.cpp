
// Class for User Input Handling
class UserInputHandler {
public:
    void getUserInput() { /* Implementation */ }
    void validateInput() { /* Implementation */ }
};

// Class for Data Processing
class DataProcessor {
public:
    void calculateData() { /* Implementation */ }
    void saveData() { /* Implementation */ }
    void displayData() { /* Implementation */ }
};
 
int main() {
    UserInputHandler inputHandler;
    DataProcessor calculator;

    inputHandler.getUserInput();
    inputHandler.validateInput();

    std::string input = inputHandler.getValidatedInput();
    double result = calculator.calculateData(input);

    calculator.saveData(result);
    calculator.displayData();
    return 0;
}

class BitwiseOperator {
public:
    virtual ~BitwiseOperator() = default;

    virtual unsigned int andOperation(unsigned int a, unsigned int b) = 0;
    virtual unsigned int orOperation(unsigned int a, unsigned int b) = 0;
};

class SpecificBitwiseOperator : public BitwiseOperator {
public:
    unsigned int andOperation(unsigned int a, unsigned int b) override {
        return a & b;
    }

    unsigned int orOperation(unsigned int a, unsigned int b) override {
        return a | b;
    }
};

class DataStructure {
public:
    virtual ~DataStructure() = default;

    virtual void setData(unsigned int value) = 0;
    virtual unsigned int getData() = 0;
    virtual void applyBitwiseOperator(BitwiseOperator& operator, unsigned int value) = 0;
};

class SpecificDataStructure : public DataStructure {
private:
    unsigned int data;

public:
    void setData(unsigned int value) override {
        data = value;
    }

    unsigned int getData() override {
        return data;
    }

    void applyBitwiseOperator(BitwiseOperator& operator, unsigned int value) override {
        data = operator.andOperation(data, value); // You can choose 'and' or 'or' here
    }
};

class ConfigurationManager {
private:
    std::unique_ptr<DataStructure> dataStructure;
    std::unique_ptr<BitwiseOperator> bitwiseOperator;

public:
    ConfigurationManager() : dataStructure(new SpecificDataStructure), bitwiseOperator(new SpecificBitwiseOperator) {}

    void setConfiguration(unsigned int configuration) {
        dataStructure->setData(configuration);
    }

    unsigned int getConfiguration() {
        return dataStructure->getData();
    }

    void applyConfiguration(unsigned int flags) {
        dataStructure->applyBitwiseOperator(*bitwiseOperator, flags);
    }

    void switchBitwiseOperationToOr() {
        // You can change the operation here without affecting the data structure
        bitwiseOperator.reset(new SpecificBitwiseOperator);
    }
};

int main() {
    ConfigurationManager configManager;

    configManager.setConfiguration(0b1010);  // Set initial configuration
    configManager.applyConfiguration(0b0101);  // Apply AND operation with 0b0101

    std::cout << "Current configuration: " << std::hex << configManager.getConfiguration() << std::dec << std::endl;

    configManager.switchBitwiseOperationToOr();
    configManager.applyConfiguration(0b1010);  // Now apply OR operation with 0b1010

    std::cout << "Current configuration after switching to OR: " << std::hex << configManager.getConfiguration() << std::dec << std::endl;

    return 0;
}

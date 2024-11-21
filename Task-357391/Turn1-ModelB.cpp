#include <gtest/gtest.h>
#include <gmock/gmock.h>


// Real dependency
class ICalculator {
public:
    virtual double calculateArea(double radius) = 0;
    virtual ~ICalculator() = default;
};

class Calculator : public ICalculator {
public:
    double calculateArea(double radius) override {
        return 3.14 * radius * radius;
    }
};

// Class that uses the dependency
class CircleAreaCalculator {
public:
    CircleAreaCalculator(ICalculator& calculator) : calculator_(calculator) {}

    double calculateArea(double radius) {
        return calculator_.calculateArea(radius);
    }

private:
    ICalculator& calculator_;
};

// Factory function to create the dependency
ICalculator* createCalculator() {
    return new Calculator();
}

// Mock object for ICalculator
class MockCalculator : public ICalculator {
public:
    MOCK_METHOD(double, calculateArea, (double radius), (override));
};

TEST(CircleAreaCalculatorTest, TestAreaCalculation) {
    // Create a mock object using dynamic mocking
    auto mockCalculator = GMOCK_CREATE_MOCK_FUNCTION(ICalculator*, createCalculator);
    EXPECT_CALL(*mockCalculator, calculateArea(10.0))
        .WillOnce(Return(314.0));

    // Inject the mock object into the CircleAreaCalculator
    CircleAreaCalculator calculator(*mockCalculator);

    // Perform the test
    double result = calculator.calculateArea(10.0);

    // Verify the result
    EXPECT_EQ(314.0, result);

    // Clean up the mock object
    GMOCK_DESTROY_MOCK_FUNCTION(mockCalculator);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
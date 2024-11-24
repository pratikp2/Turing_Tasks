#include <gtest/gtest.h>

// Your code under test
void leakyFunction() {
    int* ptr = new int; // Memory leak!
    // ...
}

TEST(YourTestSuite, LeakyFunction) {
    // Call the function under test
    leakyFunction();

    // Ensure the test completes without crashing
    SUCCEED();  // Explicitly mark the test as successful
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

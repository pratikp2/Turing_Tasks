#include <gtest/gtest.h>

// Your code under test
void leakyFunction() {
    int* ptr = new int; // Memory leak!
    // ...
}

TEST(YourTestSuite, LeakyFunction) {
    // Call the function under test
    leakyFunction();

    // Use GTEST_MEMORY_PROFILE to detect memory leaks
    GTEST_MEMORY_PROFILE_ON();
    leakyFunction();
    GTEST_MEMORY_PROFILE_OFF();

    // Compare the memory profile before and after the function call
    const char* memoryProfile = GTEST_MEMORY_PROFILE_RESULT();
    EXPECT_STREQ(memoryProfile, ""); // Expect no memory leaks
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
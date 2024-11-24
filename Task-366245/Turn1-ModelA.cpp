#include <gtest/gtest.h>

class MyClass {
public:
    MyClass() {
        myData = new int(42);
    }

    ~MyClass() {
        delete myData;
    }

private:
    int* myData;
};

TEST(MemoryLeakTest, NoLeak) {
    EXPECT_EQ(0, ::testing::LeakCheckPoint()); // Check for leaks before the test

    {
        MyClass* obj = new MyClass;
        delete obj;
    }

    // Check for leaks after the test
    EXPECT_EQ(0, ::testing::LeakCheckPoint());
}

TEST(MemoryLeakTest, WithLeak) {
    EXPECT_EQ(0, ::testing::LeakCheckPoint()); // Check for leaks before the test

    MyClass* obj = new MyClass; // Intentional leak

    // Check for leaks after the test; this should fail
    EXPECT_EQ(0, ::testing::LeakCheckPoint());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(catch_exceptions) = false; // Disable exception catching for leak checks
    return RUN_ALL_TESTS();
}
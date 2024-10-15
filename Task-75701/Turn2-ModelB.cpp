// calculate_gc_content.cpp

#include <iostream>
#include <string>
#include <stdexcept>
#include <gtest/gtest.h>  // Include Google Test header

double calculate_gc_content(const std::string& dna_sequence);

// Test fixture class for GC content calculation
class GcContentTest : public ::testing::Test {
protected:
    double calculate_gc_content_wrapper(const std::string& sequence) {
        return calculate_gc_content(sequence);
    }
};

// Example usage remains the same...

// Unit tests will be placed here

// calculate_gc_content.cpp (Continued)

TEST_F(GcContentTest, ValidDnaSequenceTest) {
    std::string sequence = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC";
    double expected_gc = 0.6;
    EXPECT_NEAR(expected_gc, calculate_gc_content_wrapper(sequence), 0.0001);
}

TEST_F(GcContentTest, InvalidDnaCharacterTest) {
    std::string sequence = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGCX";
    EXPECT_THROW(calculate_gc_content_wrapper(sequence), std::invalid_argument);
}

TEST_F(GcContentTest, EmptySequenceTest) {
    std::string sequence = "";
    EXPECT_THROW(calculate_gc_content_wrapper(sequence), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
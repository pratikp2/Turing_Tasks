// calculate_gc_content.cpp (Continued)

// Test fixture class for GC content calculation with data-driven testing
class GcContentDataDrivenTest : public ::testing::TestWithParam<std::pair<std::string, double>> {
protected:
    double calculate_gc_content_wrapper(const std::string& sequence) {
        return calculate_gc_content(sequence);
    }
};

INSTANTIATE_TEST_SUITE_P(GcContentDataDrivenTestSuite, GcContentDataDrivenTest,
                        ::testing::Values(
                            {"AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC", 0.6},
                            {"ATGCCATGC", 0.4},
                            {"TTTTTTTT", 0.0},
                            {"CCCCCCCC", 1.0},
                            // Add more test data pairs here...
                        ));

TEST_P(GcContentDataDrivenTest, DataDrivenTest) {
    std::string sequence = GetParam().first;
    double expected_gc = GetParam().second;
    EXPECT_NEAR(expected_gc, calculate_gc_content_wrapper(sequence), 0.0001) << "Failed for sequence: " << sequence;
}
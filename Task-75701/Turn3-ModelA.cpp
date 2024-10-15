// calculate_gc_content.cpp (Continued)

// New test for handling upper case DNA letters
TEST_F(GcContentTest, HandleUpperCaseDnaTest) {
	std::string sequence = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC";
	double expected_gc = 0.6;
	EXPECT_NEAR(expected_gc, calculate_gc_content_wrapper(sequence), 0.0001);
}

// Update an existing test to cover a new validation check
TEST_F(GcContentTest, ValidateInputSequenceLengthTest) {
	std::string short_sequence = "AT";
	EXPECT_THROW(calculate_gc_content_wrapper(short_sequence), std::invalid_argument);

	std::string long_sequence = "ATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGCATGC";
	EXPECT_NO_THROW(calculate_gc_content_wrapper(long_sequence));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
// calculate_gc_content.cpp

#include <iostream>
#include <string>
#include <stdexcept>

// Function to calculate GC content
double calculate_gc_content(const std::string& dna_sequence) {
    double gc_count = 0.0;

    for (char ch : dna_sequence) {
        if (ch == 'G' || ch == 'C') {
            gc_count++;
        } else if (ch != 'A' && ch != 'T') {
            throw std::invalid_argument("Invalid DNA character found");
        }
    }

    return gc_count / dna_sequence.length();
}

// Unit test function
void test_calculate_gc_content() {
    try {
        // Test 1: Valid DNA sequence
        std::string sequence1 = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC";
        double expected_gc1 = 0.6;
        double result_gc1 = calculate_gc_content(sequence1);
        if (std::abs(result_gc1 - expected_gc1) > 0.0001) {
            std::cout << "Test 1 failed: Expected GC content " << expected_gc1 << ", got " << result_gc1 << std::endl;
        } else {
            std::cout << "Test 1 passed" << std::endl;
        }

        // Test 2: Invalid DNA character
        std::string sequence2 = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGCX";
        calculate_gc_content(sequence2); // This should throw an exception
        std::cout << "Test 2 failed: Invalid DNA character not detected" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test 2 passed: Exception caught for invalid DNA character" << std::endl;
    }
}

int main() {
    // Documentation:
    /*
    This script calculates the GC content of a DNA sequence.
    Function: double calculate_gc_content(const std::string& dna_sequence)
    Input: A DNA sequence string (only valid characters: A, T, G, C)
    Output: The GC content as a decimal number between 0 and 1
    */

    // Run unit tests
    test_calculate_gc_content();

    // Example usage
    std::string dna_sequence = "ATGCCATGC";
    double gc_content = calculate_gc_content(dna_sequence);
    std::cout << "GC Content of " << dna_sequence << ": " << gc_content << std::endl;

    return 0;
}
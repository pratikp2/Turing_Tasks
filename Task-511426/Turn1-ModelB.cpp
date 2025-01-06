#include <iostream>
using namespace std;

// Calculates a simple bitwise XOR checksum for an array of bytes
unsigned char calculateChecksum(const unsigned char* data, size_t size) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < size; ++i) {
        checksum ^= data[i];
    }
    return checksum;
}

// Function to check data integrity using the calculated checksum
bool checkDataIntegrity(const unsigned char* data, size_t size, unsigned char stored_checksum) {
    unsigned char calculated_checksum = calculateChecksum(data, size);
    return calculated_checksum == stored_checksum;
}

int main() {
    const unsigned char sample_data[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10
    };

    size_t data_size = sizeof(sample_data) / sizeof(sample_data[0]);

    // Calculate and store the checksum
    unsigned char stored_checksum = calculateChecksum(sample_data, data_size);

    cout << "Calculated Checksum: 0x" << hex << static_cast<int>(stored_checksum) << dec << endl;

    // Simulate data modification (error introduction)
    sample_data[5] = 0xFF;

    // Check data integrity
    if (checkDataIntegrity(sample_data, data_size, stored_checksum)) {
        cout << "Data integrity check: Passed" << endl;
    } else {
        cout << "Data integrity check: Failed" << endl;
    }

    return 0;
}

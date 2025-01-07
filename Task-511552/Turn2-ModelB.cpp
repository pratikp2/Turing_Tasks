#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <endian.h> // For endianness detection and conversion

constexpr int TABLE_SIZE = 10;

struct HashNode {
    int key;
    std::string value;
    HashNode* next;
    HashNode(int k, const std::string& v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;
    bool isLittleEndian;

    int hashFunction(int key) {
        // Check if the key is stored in little-endian format
        if (isLittleEndian) {
            // Convert the key to big-endian for consistent hashing
            uint32_t bigEndianKey = htobe32(key);
            return static_cast<int>(bigEndianKey % TABLE_SIZE);
        } else {
            return std::abs(key % TABLE_SIZE);
        }
    }

public:
    HashTable() {
        table = new HashNode*[TABLE_SIZE]();
        // Detect endianness at runtime
        isLittleEndian = (htobe32(1) != 1);
    }

    // ... (Rest of the class implementation remains the same)
};

int main() {
    HashTable ht;
    ht.insert(12, "Hello");
    ht.insert(22, "World");
    ht.insert(32, "!");

    std::cout << "Search for key 22: " << ht.search(22) << std::endl;
    std::cout << "Contents of hash table:" << std::endl;
    ht.display();

    return 0;
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstdint>

constexpr int TABLE_SIZE = 10; // Define the size of the hash table

// Enum for endianness
enum class Endianness {
    LITTLE,
    BIG,
    UNKNOWN
};

// Detect endianness
Endianness detectEndianness() {
    uint32_t num = 1;
    if (*reinterpret_cast<uint8_t*>(&num) == 1) {
        return Endianness::LITTLE;
    } else {
        return Endianness::BIG;
    }
}

// Hash Table Node
struct HashNode {
    int key;
    std::string value;
    HashNode* next;

    HashNode(int k, const std::string& v) : key(k), value(v), next(nullptr) {}
};

// Hash Table Class
class HashTable {
private:
    HashNode** table;

    // A dynamic hash function that handles endianness
    int hashFunction(int key) {
        Endianness endianness = detectEndianness();
        unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&key);
        unsigned int shifted;

        if (endianness == Endianness::LITTLE) {
            shifted = (bytePtr[0] << 24) | (bytePtr[1] << 16) | (bytePtr[2] << 8) | bytePtr[3];
        } else {
            shifted = (bytePtr[3] << 24) | (bytePtr[2] << 16) | (bytePtr[1] << 8) | bytePtr[0];
        }
        
        return shifted % TABLE_SIZE;
    }

public:
    HashTable() {
        table = new HashNode*[TABLE_SIZE]();
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* current = table[i];
            while (current) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(int key, const std::string& value) {
        int index = hashFunction(key);
        HashNode* newNode = new HashNode(key, value);

        if (!table[index]) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    std::string search(int key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "Not found";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            std::cout << "[" << i << "]: ";
            while (current) {
                std::cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }
    }
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

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

constexpr int TABLE_SIZE = 10; // Define the size of the hash table

// Hash Table Node
struct HashNode {
    int key;
    std::string value;
    HashNode* next;

    HashNode(int k, const std::string& v) :
        key(k), value(v), next(nullptr) {}
};

// Hash Table Class
class HashTable {
private:
    HashNode** table;

    // A sample hash function that takes endianness into account.
    int hashFunction(int key) {
        // For demonstration: return key % TABLE_SIZE
        // This naive implementation does not specifically adjust for endianness
        // All integers will behave the same regardless of endianness.
        return std::abs(key % TABLE_SIZE);
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
            // Collision handling - chaining
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

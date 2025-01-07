#include<bits/stdc++.h>
using namespace std;

#define TABLE_SIZE 10

struct HashEntry {
    int key;
    int value;
    bool is_occupied;
};

class HashTable {

    HashEntry* table;

public:
    HashTable() {
        table = new HashEntry[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].is_occupied = false;
        }
    }

    ~HashTable() {
        delete[] table;
    }

    size_t simple_hash(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key, int value) {
        size_t index = simple_hash(key);

        while (table[index].is_occupied) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].key = key;
        table[index].value = value;
        table[index].is_occupied = true;
    }

    void print_table() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].is_occupied) {
                cout << "(" << table[i].key << ", " << table[i].value << ") ";
            }
        }
        cout << endl;
    }
};
 
int main() {
    HashTable hash_table;
    hash_table.insert(12, 100);
    hash_table.insert(22, 200);
    hash_table.insert(32, 300);
    hash_table.insert(42, 400);

    hash_table.print_table();
 
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

template <typename K, typename V>
class Cache {
private:
    struct Entry {
        K key;
        V value;
        bool isOccupied; // Indicates if the entry is occupied
        bool isDeleted; // Indicates if the entry was deleted
    };

    std::vector<Entry> table;
    size_t capacity;
    size_t size;
    float loadFactor;

    size_t hash(const K& key) {
        // Bitwise XOR shifted hash function
        std::hash<K> hasher;
        return (hasher(key) ^ (hasher(key) >> 16)) & (capacity - 1);
    }

    void rehash() {
        // Expand the table size and rehash
        std::vector<Entry> oldTable = table;
        capacity *= 2;
        table = std::vector<Entry>(capacity);
        size = 0;

        for (const auto& entry : oldTable) {
            if (entry.isOccupied && !entry.isDeleted) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    Cache(size_t initCapacity, float loadFactor = 0.7f) 
        : capacity(initCapacity), loadFactor(loadFactor), size(0) {
        table.resize(capacity);
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity * loadFactor) {
            rehash();
        }

        size_t idx = hash(key);
        while (table[idx].isOccupied) {
            if (table[idx].key == key && !table[idx].isDeleted) {
                // Update the value if the key already exists
                table[idx].value = value;
                return;
            }
            idx = (idx + 1) & (capacity - 1); // Linear probing
        }

        table[idx] = {key, value, true, false};
        size++;
    }

    V get(const K& key) {
        size_t idx = hash(key);
        while (table[idx].isOccupied) {
            if (table[idx].key == key && !table[idx].isDeleted) {
                return table[idx].value;
            }
            idx = (idx + 1) & (capacity - 1); // Linear probing
        }
        throw std::out_of_range("Key not found");
    }

    void remove(const K& key) {
        size_t idx = hash(key);
        while (table[idx].isOccupied) {
            if (table[idx].key == key && !table[idx].isDeleted) {
                table[idx].isDeleted = true; // Mark as deleted
                size--;
                return;
            }
            idx = (idx + 1) & (capacity - 1); // Linear probing
        }
        throw std::out_of_range("Key not found");
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    Cache<std::string, int> cache(16); // A cache for strings mapping to integers

    cache.insert("item1", 1);
    cache.insert("item2", 2);
    cache.insert("item3", 3);

    std::cout << "Value for item1: " << cache.get("item1") << std::endl;
    std::cout << "Size of cache: " << cache.getSize() << std::endl;

    cache.remove("item2");

    std::cout << "Size of cache after removal: " << cache.getSize() << std::endl;

    try {
        cache.get("item2"); // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Key not found
    }

    return 0;
}

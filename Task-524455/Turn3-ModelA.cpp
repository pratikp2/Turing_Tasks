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
        bool isDeleted;  // Indicates if the entry was deleted
    };

    std::vector<Entry> table; // The hash table
    size_t capacity;          // Capacity of the cache
    size_t size;             // Current size of the cache
    float loadFactor;        // Load factor threshold for resizing

    size_t hash(const K& key) {
        // Bitwise XOR shifted hash function
        std::hash<K> hasher;
        return (hasher(key) ^ (hasher(key) >> 16)) & (capacity - 1);
    }

    void rehash() {
        // Expand the table size and rehash
        std::vector<Entry> oldTable = table;
        capacity *= 2; // Double the capacity
        table = std::vector<Entry>(capacity); // Create a new table with doubled capacity
        size = 0; // Reset size to 0 for re-insertion

        for (const auto& entry : oldTable) {
            if (entry.isOccupied && !entry.isDeleted) {
                insert(entry.key, entry.value); // Reinsert the valid entries
            }
        }
    }

public:
    Cache(size_t initCapacity = 16, float loadFactor = 0.7f) 
        : capacity(initCapacity), loadFactor(loadFactor), size(0) {
        table.resize(capacity);
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity * loadFactor) {
            rehash(); // Resize if the load factor is exceeded
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

    size_t getCapacity() const {
        return capacity;
    }
};

int main() {
    Cache<std::string, int> cache; // A cache for strings mapping to integers

    // Insert a large number of items to trigger resizing
    for (int i = 0; i < 50; ++i) {
        cache.insert("item" + std::to_string(i), i);
    }

    std::cout << "Value for item10: " << cache.get("item10") << std::endl;
    std::cout << "Size of cache: " << cache.getSize() << std::endl;
    std::cout << "Capacity of cache: " << cache.getCapacity() << std::endl;

    cache.remove("item20");

    std::cout << "Size of cache after removal: " << cache.getSize() << std::endl;

    try {
        cache.get("item20"); // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Key not found
    }

    return 0;
}

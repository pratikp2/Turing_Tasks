#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
#include <thread>
#include <mutex>

template <typename K, typename V>
class Cache {
private:
    struct Entry {
        K key;
        V value;
        bool isOccupied; // Indicates if the entry is occupied
        bool isDeleted; // Indicates if the entry was deleted
    };

    std::vector<Entry> table; // The hash table
    size_t capacity;         // Capacity of the cache
    size_t size;            // Current size of the cache
    float loadFactor;       // Load factor threshold for resizing
    std::mutex mutex;       // Mutex lock for synchronization

    size_t hash(const K& key) {
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
    Cache(size_t initCapacity = 16, float loadFactor = 0.7f) 
        : capacity(initCapacity), loadFactor(loadFactor), size(0) {
        table.resize(capacity);
    }

    void insert(const K& key, const V& value) {
        std::lock_guard<std::mutex> lock(mutex); // Acquire lock

        if (size >= capacity * loadFactor) {
            rehash();
        }

        size_t idx = hash(key);
        while (table[idx].isOccupied) {
            if (table[idx].key == key && !table[idx].isDeleted) {
                table[idx].value = value;
                return;
            }
            idx = (idx + 1) & (capacity - 1);
        }

        table[idx] = {key, value, true, false};
        size++;
    }

    V get(const K& key) const {
        std::lock_guard<std::mutex> lock(mutex);

        size_t idx = hash(key);
        while (table[idx].isOccupied) {
            if (table[idx].key == key && !table[idx].isDeleted) {
                return table[idx].value;
            }
            idx = (idx + 1) & (capacity - 1);
        }
        throw std::out_of_range("Key not found");
    }

    void remove(const K& key) {
        std::lock_guard<std::mutex> lock(mutex);

        size_t idx = hash(key);
        while (table[idx].isOccupied) {
            if (table[idx].key == key && !table[idx].isDeleted) {
                table[idx].isDeleted = true;
                size--;
                return;
            }
            idx = (idx + 1) & (capacity - 1);
        }
        throw std::out_of_range("Key not found");
    }

    size_t getSize() const {
        std::lock_guard<std::mutex> lock(mutex);
        return size;
    }

    size_t getCapacity() const {
        std::lock_guard<std::mutex> lock(mutex);
        return capacity;
    }
};

int main() {
    Cache<std::string, int> cache;

    std::thread workerThread1([&] {
        for (int i = 0; i < 10; ++i) {
            cache.insert("item" + std::to_string(i), i);
        }
    });

    std::thread workerThread2([&] {
        for (int i = 10; i < 20; ++i) {
            cache.insert("item" + std::to_string(i), i);
        }
    });

    workerThread1.join();
    workerThread2.join();

    std::cout << "Value for item10: " << cache.get("item10") << std::endl;
    std::cout << "Size of cache: " << cache.getSize() << std::endl;
    std::cout << "Capacity of cache: " << cache.getCapacity() << std::endl;

    try {
        cache.get("item20"); // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Key not found
    }

    return 0;
}

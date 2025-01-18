#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class CacheEntry {
public:
    int key;
    int value;
    CacheEntry(int key, int value) : key(key), value(value) {}
};

class LinearProbingHashCache {
public:
    LinearProbingHashCache(int size) : size(size), cache(size) {}

    int hash(int key) {
        return key % size;
    }

    bool insert(int key, int value) {
        int index = hash(key);
        while (cache[index].key != 0) {
            if (cache[index].key == key) {
                cache[index].value = value;
                return false; // Key already exists, update the value
            }
            index = (index + 1) % size;
        }
        cache[index] = CacheEntry(key, value);
        return true;
    }

    int get(int key) {
        int index = hash(key);
        while (cache[index].key != 0) {
            if (cache[index].key == key) {
                return cache[index].value;
            }
            index = (index + 1) % size;
        }
        return -1; // Key not found
    }

    bool remove(int key) {
        int index = hash(key);
        while (cache[index].key != 0) {
            if (cache[index].key == key) {
                cache[index] = CacheEntry(0, 0);
                return true;
            }
            index = (index + 1) % size;
        }
        return false; // Key not found
    }

private:
    int size;
    vector<CacheEntry> cache;
};

int main() {
    LinearProbingHashCache cache(10);

    cache.insert(1, 10);
    cache.insert(2, 20);
    cache.insert(3, 30);
    cache.insert(4, 40);

    cout << "Cache Lookups:" << endl;
    cout << "Key 1: " << cache.get(1) << endl;
    cout << "Key 5: " << cache.get(5) << endl;

    cache.remove(2);

    cout << "\nCache after removing Key 2:" << endl;
    cout << "Key 2: " << cache.get(2) << endl;

    return 0;
}

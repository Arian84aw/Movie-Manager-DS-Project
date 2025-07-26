#pragma once
#include "Headers.h"
#include <type_traits>


template <typename K, typename V>
class HashTable {
private:
    vector<list<pair<K, V>>> table;
    string base;
    int numBuckets;
    int size;

    int hashFunction(const K& key) const {
        if constexpr (std::is_integral<K>::value) {
            return key % numBuckets;
        }
        else if constexpr (std::is_same<K, std::string>::value) {
            long long int hash = 0;
            for (char ch : key) {
                hash = (hash * 31 + int(ch)) % 100000007;
            }
            while (hash < 0) {
                hash += numBuckets;
            }
            return hash % numBuckets;
        }
        else if constexpr (std::is_floating_point<K>::value) {

            long long int hash = static_cast<long long int>(key * 1000000);  // Adjust precision as needed
            while (hash < 0) {
                hash += numBuckets;
            }
            return hash % numBuckets;
        }
        else {
            throw runtime_error("Unsupported key type");
        }
    }


public:
    HashTable(int buckets = 10) : numBuckets(buckets), size(0) {
        table.resize(numBuckets);
    }

    void insert(const K& key, V value) {
        int bucketIndex = hashFunction(key);
        table[bucketIndex].push_back({ key, value });
        size++;
    }


    bool search(const K& key, const V& value) const {
        int bucketIndex = hashFunction(key);
        const auto& bucket = table[bucketIndex];
        for (const auto& item : bucket) {
            if (item.first == key && item.second == value) {
                return true;
            }
        }
        return false;
    }
    void search(const K& key, vector<V>& movieList) {
        int bucketIndex = hashFunction(key);
        const auto& bucket = table[bucketIndex];
        for (const auto& item : bucket) {
            if (item.first == key) {
                movieList.push_back(item.second);
            }
        }
    }
    void remove(const K& key, const V& value) {
        int bucketIndex = hashFunction(key);
        auto& bucket = table[bucketIndex];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key && it->second == value) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }
    V& get( K key) {
        int bucketIndex = hashFunction(key);
        auto& bucket = table[bucketIndex];
        for (auto& item : bucket) {
            if (item.first == key) {
                return item.second;
            }
        }
        throw runtime_error("Key not found");
    }

    bool exists(const K& key) const {
        int bucketIndex = hashFunction(key);
        auto& bucket = table[bucketIndex];
        for (auto& item : bucket) {
            if (item.first == key) {
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < table.size(); ++i) {
            cout << "Bucket " << i << "(" << base << "): " << endl;
            for (auto& pair : table[i]) {
                pair.second.ShowMovieInfo();
            }
            cout << endl;
        }
    }

    int getSize() const {
        return size;
    }

    vector<K> getTable() const {
        vector<K> res;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                res.push_back(pair.first);
            }
        }
        return res;
    }
};
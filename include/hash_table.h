#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "itable.h"
#include <vector>
#include <functional>

template<typename KeyType, typename ValueType>
class HashTable : public ITable<KeyType, ValueType> {
private:
    struct Entry {
        KeyType key;
        ValueType value;
        bool occupied;
        bool deleted;

        Entry() : occupied(false), deleted(false) {}
        Entry(const KeyType& k, const ValueType& v) : key(k), value(v), occupied(true), deleted(false) {}
    };

    std::vector<Entry> table;
    size_t elemCount = 0;
    mutable size_t comparisons = 0;
    mutable size_t operations = 0;

    size_t hash(const KeyType& key) const {
        return std::hash<KeyType>{}(key) % table.size();
    }

    void rehash() {
        std::vector<Entry> oldTable = std::move(table);
        table.resize(oldTable.size() * 2);
        elemCount = 0;
        for (auto& entry : oldTable) {
            if (entry.occupied && !entry.deleted) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashTable(size_t initialSize = 16) : table(initialSize), elemCount(0), comparisons(0), operations(0) {}

    std::string name() const override {
        return "HashTable";
    }

    void resetCounters() override {
        comparisons = 0;
        operations = 0;
    }

    void insert(const KeyType& key, const ValueType& value) override {
        if (elemCount * 2 >= table.size()) {
            rehash();
        }

        size_t index = hash(key);
        size_t start = index;
        size_t i = 0;

        while (true) {
            comparisons++;
            if (!table[index].occupied || table[index].deleted) {
                table[index] = Entry(key, value);
                elemCount++;
                operations++;
                return;
            }
            else if (table[index].key == key) {
                table[index].value = value;
                operations++;
                return;
            }
            i++;
            index = (start + i) % table.size();
            if (i == table.size()) {
                rehash();
                insert(key, value);
                return;
            }
        }
    }

    bool find(const KeyType& key, ValueType& value) const override {
        size_t index = hash(key);
        size_t start = index;
        size_t i = 0;

        while (i < table.size()) {
            comparisons++;
            if (!table[index].occupied) return false;
            if (!table[index].deleted && table[index].key == key) {
                value = table[index].value;
                operations++;
                return true;
            }
            i++;
            index = (start + i) % table.size();
        }
        return false;
    }

    bool remove(const KeyType& key) override {
        size_t index = hash(key);
        size_t start = index;
        size_t i = 0;

        while (i < table.size()) {
            comparisons++;
            if (!table[index].occupied) return false;
            if (!table[index].deleted && table[index].key == key) {
                table[index].deleted = true;
                elemCount--;
                operations++;
                return true;
            }
            i++;
            index = (start + i) % table.size();
        }
        return false;
    }

    bool contains(const KeyType& key) const override {
        ValueType dummy;
        return find(key, dummy);
    }

    size_t size() const override {
        return elemCount;
    }

    void clear() override {
        table.clear();
        table.resize(16);
        elemCount = 0;
    }

    std::vector<KeyType> keys() const override {
        std::vector<KeyType> res;
        for (const auto& entry : table) {
            if (entry.occupied && !entry.deleted) {
                res.push_back(entry.key);
            }
        }
        return res;
    }

    size_t getComparisons() const override {
        return comparisons;
    }

    size_t getOperations() const override {
        return operations;
    }
};

#endif
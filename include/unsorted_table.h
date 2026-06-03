#ifndef UNSORTED_TABLE_H
#define UNSORTED_TABLE_H

#include "itable.h"
#include <vector>
#include <algorithm>

template<typename KeyType, typename ValueType>
class UnsortedArrayTable : public ITable<KeyType, ValueType> {
private:
    std::vector<std::pair<KeyType, ValueType>> data;
    mutable size_t comparisons = 0;
    mutable size_t operations = 0;

public:
    UnsortedArrayTable() : comparisons(0), operations(0) {}

    std::string name() const override {
        return "UnsortedArray";
    }

    void resetCounters() override {
        comparisons = 0;
        operations = 0;
    }

    void insert(const KeyType& key, const ValueType& value) override {
        for (auto& p : data) {
            comparisons++;
            if (p.first == key) {
                p.second = value;
                operations++;
                return;
            }
        }
        data.push_back({ key, value });
        operations++;
    }

    bool find(const KeyType& key, ValueType& value) const override {
        for (const auto& p : data) {
            comparisons++;
            if (p.first == key) {
                value = p.second;
                operations++;
                return true;
            }
        }
        return false;
    }

    bool remove(const KeyType& key) override {
        for (auto it = data.begin(); it != data.end(); ++it) {
            comparisons++;
            if (it->first == key) {
                data.erase(it);
                operations++;
                return true;
            }
        }
        return false;
    }

    bool contains(const KeyType& key) const override {
        ValueType dummy;
        return find(key, dummy);
    }

    size_t size() const override {
        return data.size();
    }

    void clear() override {
        data.clear();
    }

    std::vector<KeyType> keys() const override {
        std::vector<KeyType> res;
        for (const auto& p : data) {
            res.push_back(p.first);
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
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include "itable.h"

class OperationLogger {
public:
    template<typename KeyType, typename ValueType>
    static void logInsert(ITable<KeyType, ValueType>& table, const KeyType& key) {
        table.resetCounters();
        ValueType dummy;
        table.insert(key, dummy);
        std::cout << "[" << table.name() << "] INSERT " << key
            << " | сравнений: " << table.getComparisons()
            << " | операций: " << table.getOperations() << std::endl;
    }

    template<typename KeyType, typename ValueType>
    static void logInsertWithValue(ITable<KeyType, ValueType>& table, const KeyType& key, const ValueType& value) {
        table.resetCounters();
        table.insert(key, value);
        std::cout << "[" << table.name() << "] INSERT " << key
            << " | сравнений: " << table.getComparisons()
            << " | операций: " << table.getOperations() << std::endl;
    }

    template<typename KeyType, typename ValueType>
    static void logFind(ITable<KeyType, ValueType>& table, const KeyType& key) {
        table.resetCounters();
        ValueType val;
        bool found = table.find(key, val);
        std::cout << "[" << table.name() << "] FIND " << key
            << " | найдено: " << (found ? "да" : "нет")
            << " | сравнений: " << table.getComparisons()
            << " | операций: " << table.getOperations() << std::endl;
    }

    template<typename KeyType, typename ValueType>
    static void logRemove(ITable<KeyType, ValueType>& table, const KeyType& key) {
        table.resetCounters();
        bool removed = table.remove(key);
        std::cout << "[" << table.name() << "] REMOVE " << key
            << " | удалено: " << (removed ? "да" : "нет")
            << " | сравнений: " << table.getComparisons()
            << " | операций: " << table.getOperations() << std::endl;
    }
};

#endif
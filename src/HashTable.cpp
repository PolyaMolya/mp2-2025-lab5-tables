#include "HashTable.h"

int HashTable::calcHash(std::string key) {
  unsigned int hashVal = 0;
  for (char ch : key) {
    hashVal = (hashVal * 37) + ch;
  }
  return hashVal % TABLE_CAPACITY;
}

int HashTable::insert(std::string key, Polinom val) {
  int stepCount = 1;
  int idx = calcHash(key);

  for (auto& pair : chains[idx]) {
    stepCount++;
    if (pair.first == key) {
      pair.second = val;
      return stepCount;
    }
  }
  chains[idx].push_back({key, val});
  return stepCount;
}

Polinom* HashTable::find(std::string key, int& ops) {
  ops = 1;
  int idx = calcHash(key);

  for (auto& pair : chains[idx]) {
    ops++;
    if (pair.first == key) {
      return &pair.second;
    }
  }
  return nullptr;
}

int HashTable::remove(std::string key) {
  int idx = calcHash(key);
  int stepCount = 1;
  auto& targetChain = chains[idx];

  for (auto it = targetChain.begin(); it != targetChain.end(); ++it) {
    stepCount++;
    if (it->first == key) {
      targetChain.erase(it);
      return stepCount;
    }
  }
  return stepCount;
}
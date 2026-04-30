#include "HashTable.h"

int HashTable::hashFunction(std::string key) { 
	unsigned int h = 0;
  for (char c : key) {
    h = h * 31 + c;
  }
  return h % SIZE;
}

int HashTable::insert(std::string key, Polinom val) { 
  int ops = 1;
  int index = hashFunction(key);

  for (auto& item : buckets[index]) {
    ops++;
    if (item.first == key) {
      item.second = val;
      return ops;
    }
  }
  buckets[index].push_back({key, val});
  return ops;
}

Polinom* HashTable::find(std::string key, int& ops) { 
  ops = 1;
  int index = hashFunction(key);

  for (auto& item : buckets[index]) {
    ops++;
    if (item.first == key) {
      return &item.second;
    }
  }
  return nullptr;
}

int HashTable::remove(std::string key) {
  int index = hashFunction(key);
  int ops = 1;
  auto& chain = buckets[index];

  for (auto it = chain.begin(); it != chain.end(); ++it) {
    ops++;
    if (it->first == key) {
      chain.erase(it);
      return ops;
    }
  }
  return ops;
}
#include "ArrayTable.h"

int UnorderedArrayTable::insert(std::string key, Polinom val) {
  int ops = 0;

  for (size_t i = 0; i < data.size(); i++) {
    ops++;
    if (data[i].key == key) {
      data[i].value = val;
      return ops;
    }
  }
  data.push_back({key, val});
  ops++;
  return ops;
}

Polinom* UnorderedArrayTable::find(std::string key, int& ops) {
  ops = 0;

  for (size_t i = 0; i < data.size(); i++) {
    ops++;
    if (data[i].key == key) {
      return &data[i].value;
    }
  }
  return nullptr;
}

int UnorderedArrayTable::remove(std::string key) {
  int ops = 0;

  for (auto it = data.begin(); it != data.end(); ++it) {
    ops++;
    if (it->key == key) {
      data.erase(it);
      return ops;
    }
  }
  return ops;
}
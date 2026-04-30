#pragma once
#include "Table.h"
#include <list>
#include <vector>

class HashTable : public Table {
 private:
  static const int SIZE = 101;
  std::list<std::pair<std::string, Polinom>> buckets[SIZE];
  int hashFunction(std::string key);

 public:
  int insert(std::string key, Polinom val) override;
  Polinom* find(std::string key, int& ops) override;
  int remove(std::string key) override;
};

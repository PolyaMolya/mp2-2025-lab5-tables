#pragma once
#include <list>
#include <vector>
#include "Table.h"

class HashTable : public Table {
private:
  static const int TABLE_CAPACITY = 127;
  std::list<std::pair<std::string, Polinom>> chains[TABLE_CAPACITY];
  
  int calcHash(std::string key);

public:
  int insert(std::string key, Polinom val) override;
  Polinom* find(std::string key, int& ops) override;
  int remove(std::string key) override;
};
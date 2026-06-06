#pragma once
#include <string>
#include <vector>
#include "Table.h"

struct ArrayRow {
  std::string key;
  Polinom data;
};

class SortedArrayTable : public Table {
private:
  std::vector<ArrayRow> records;

public:
  int insert(std::string key, Polinom val) override;
  Polinom* find(std::string key, int& ops) override;
  int remove(std::string key) override;
};
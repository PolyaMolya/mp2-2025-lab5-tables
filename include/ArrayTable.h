#pragma once
#include "Table.h"
#include <vector>
#include <string>

struct Record {
  std::string key;
  Polinom value;
};

class UnorderedArrayTable : public Table {
 private:
  std::vector<Record> data;

 public:
  int insert(std::string key, Polinom val) override;
  Polinom* find(std::string key, int& ops) override;
  int remove(std::string key) override;
};
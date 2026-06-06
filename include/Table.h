#pragma once
#include <string>
#include "polinoms.h"

class Table {
public:
  virtual int insert(std::string key, Polinom val) = 0;
  virtual Polinom* find(std::string key, int& ops) = 0;
  virtual int remove(std::string key) = 0;
  virtual ~Table() {}
};
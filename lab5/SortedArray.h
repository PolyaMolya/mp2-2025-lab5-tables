#pragma once
#include "Polynomial.h"
#include <string>
#include <vector>

struct Unit {
  std::string key; // more convenient
  Polynomial value;
};

class SortedArrayTable {
private:
  std::vector<Unit> data;
  int Size;

public:
  SortedArrayTable(int size = 50) {
    Size = size;
    data.reserve(Size); // for efficiency
  }

  int find(const std::string &key, size_t &count);
  bool insert(const std::string &key, const Polynomial &poly, size_t &count);
  bool remove(const std::string &key, size_t &count);

  Polynomial *get(const std::string &key, size_t &count);

  size_t size() const { return data.size(); }
  bool isFull() const { return data.size() >= Size; }
};

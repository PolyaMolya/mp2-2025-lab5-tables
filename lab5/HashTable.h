#pragma once
#include "Polynomial.h"
#include <string>
#include <vector>

enum class State { Empty, Occupied, Deleted };

struct HashUnit {
  std::string key;
  Polynomial value;
  State state;

  HashUnit() : key(""), state(State::Empty) {}
};

class HashTable {
private:
  std::vector<HashUnit> data;
  size_t capacity;
  size_t count;

  size_t hash1(const std::string &key) const;

  size_t hash2(const std::string &key) const;

public:
  HashTable(size_t initialCapacity = 113);

  bool insert(const std::string &key, const Polynomial &poly, size_t &count);

  Polynomial *find(const std::string &key, size_t &count);

  bool remove(const std::string &key, size_t &count);

  size_t size() const { return count; }
};
#ifndef ITABLE_H
#define ITABLE_H

#include <string>
#include <vector>

template <typename KeyType, typename ValueType> class ITable {
public:
  virtual ~ITable() = default;

  virtual void insert(const KeyType &key, const ValueType &value) = 0;
  virtual bool find(const KeyType &key, ValueType &value) const = 0;
  virtual bool remove(const KeyType &key) = 0;
  virtual bool contains(const KeyType &key) const = 0;
  virtual size_t size() const = 0;
  virtual void clear() = 0;
  virtual std::vector<KeyType> keys() const = 0;
  virtual std::string name() const = 0;
  virtual void resetCounters() = 0;
  virtual size_t getComparisons() const = 0;
  virtual size_t getOperations() const = 0;
};

#endif
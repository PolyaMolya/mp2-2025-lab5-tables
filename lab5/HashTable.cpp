#include "HashTable.h"

HashTable::HashTable(size_t initialCapacity) {
  capacity = initialCapacity;
  data.resize(capacity);
  count = 0;
}

size_t HashTable::hash1(const std::string &key) const {
  size_t h = 0;
  for (char c : key) {
    h = h * 31 + static_cast<unsigned char>(c);
  }
  return h % capacity;
}

size_t HashTable::hash2(const std::string &key) const {
  size_t h = 0;
  for (char c : key) {
    h = h * 37 + static_cast<unsigned char>(c);
  }
  return (h % (capacity - 1)) + 1; // avoid 0 shift
}

bool HashTable::insert(const std::string &key, const Polynomial &poly,
                       size_t &ñount) {
  ñount = 0;
  if (count >= capacity) // count of units in Table
    return false;

  size_t h1 = hash1(key);
  size_t h2 = hash2(key);
  size_t index = h1;

  int firstDeleted = -1;

  for (size_t i = 0; i < capacity; ++i) {
    ñount++;

    if (data[index].state == State::Empty) {
      size_t targetIndex = (firstDeleted != -1) ? (size_t)firstDeleted : index;
      data[targetIndex].key = key;
      data[targetIndex].value = poly;
      data[targetIndex].state = State::Occupied;
      count++;
      return true;
    }

    if (data[index].state == State::Occupied && data[index].key == key) {
      data[index].value = poly;
      return true;
    }

    if (data[index].state == State::Deleted && firstDeleted == -1) {
      firstDeleted = (int)index;
    }

    index = (index + h2) % capacity;
  }

  return false;
}

Polynomial *HashTable::find(const std::string &key, size_t &count) {
  count = 0;
  size_t h1 = hash1(key);
  size_t h2 = hash2(key);
  size_t index = h1;

  for (size_t i = 0; i < capacity; ++i) {
    count++;

    if (data[index].state == State::Empty) {
      return nullptr;
    }

    if (data[index].state == State::Occupied && data[index].key == key) {
      return &(data[index].value);
    }

    index = (index + h2) % capacity; // jump the distance calculated by hash2
  }
  return nullptr;
}

bool HashTable::remove(const std::string &key, size_t &count2) {
  count2 = 0;
  size_t h1 = hash1(key);
  size_t h2 = hash2(key);
  size_t index = h1;

  for (size_t i = 0; i < capacity; ++i) {
    count2++;

    if (data[index].state == State::Empty)
      return false;

    if (data[index].state == State::Occupied && data[index].key == key) {
      data[index].state = State::Deleted;
      count--;
      return true;
    }

    index = (index + h2) % capacity;
  }
  return false;
}
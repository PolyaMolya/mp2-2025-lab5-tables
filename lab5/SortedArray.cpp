#include "SortedArray.h"
#include <algorithm>

int SortedArrayTable::find(const std::string &key, size_t &count) {
  count = 0;
  int left = 0;
  int right = data.size() - 1;

  while (left <= right) {
    count++;
    int mid = left + (right - left) / 2;
    if (data[mid].key == key) {
      return mid;
    }
    if (data[mid].key < key) {
      left = mid + 1;
    }
    if (data[mid].key > key) {
      right = mid - 1;
    }
  }
  return -1;
}

Polynomial *SortedArrayTable::get(const std::string &key, size_t &count) {
  int index = find(key, count);
  if (index != -1) {
    return &data[index].value;
  }
  return nullptr;
}

bool SortedArrayTable::insert(const std::string &key, const Polynomial &poly,
                              size_t &count) {
  count = 0;
  size_t findCount = 0;

  int index = find(key, findCount);
  count += findCount;

  if (index != -1) {
    data[index].value = poly;
    return true;
  }

  if (isFull()) {
    return false;
  }

  auto begin = data.begin();
  while (begin != data.end()) {
    count++;
    if (begin->key > key) {
      break;
    }
    begin++;
  }

  size_t moveCount =
      std::distance(begin, data.end()); // counting the number of elements to
                                        // shift, cant sub iterators
  data.insert(begin, {key, poly});
  count += moveCount;
  return true;
}

bool SortedArrayTable::remove(const std::string &key, size_t &count) {
  count = 0;
  size_t findCount = 0;
  int index = find(key, findCount);
  count += findCount;
  if (index == -1) {
    return false;
  }
  size_t moveCount =
      data.size() - index - 1; // counting the number of elements to shift
  data.erase(data.begin() + index);

  count += moveCount;
  return true;
}
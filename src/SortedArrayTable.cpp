#include "SortedArrayTable.h"

int SortedArrayTable::insert(std::string key, Polinom val) {
  int opsCount = 0;
  int left = 0;
  int right = records.size() - 1;
  int pos = 0;

  while (left <= right) {
    opsCount++;
    int mid = left + (right - left) / 2;
    if (records[mid].key == key) {
      records[mid].data = val;
      return opsCount;
    }
    if (records[mid].key < key) {
      left = mid + 1;
      pos = mid + 1;
    } else {
      right = mid - 1;
      pos = mid;
    }
  }
  
  records.insert(records.begin() + pos, {key, val});
  return opsCount;
}

Polinom* SortedArrayTable::find(std::string key, int& opsCount) {
  opsCount = 0;
  int left = 0;
  int right = records.size() - 1;

  while (left <= right) {
    opsCount++;
    int mid = left + (right - left) / 2;
    if (records[mid].key == key) {
      return &records[mid].data;
    }
    if (records[mid].key < key) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return nullptr;
}

int SortedArrayTable::remove(std::string key) {
  int opsCount = 0;
  int left = 0;
  int right = records.size() - 1;
  int pos = -1;

  while (left <= right) {
    opsCount++;
    int mid = left + (right - left) / 2;
    if (records[mid].key == key) {
      pos = mid;
      break;
    }
    if (records[mid].key < key) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  if (pos != -1) {
    records.erase(records.begin() + pos);
  }
  return opsCount;
}
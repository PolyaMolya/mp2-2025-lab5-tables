#include "Polynom.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct OperationLog {
  int unsortedComparisons = 0;
  int sortedComparisons = 0;
  int sortedShifts = 0;
  int avlComparisons = 0;
  int avlRotations = 0;
  int hashProbes = 0;
  int hashComputations = 0;

  void reset() {
    unsortedComparisons = 0;
    sortedComparisons = 0;
    sortedShifts = 0;
    avlComparisons = 0;
    avlRotations = 0;
    hashProbes = 0;
    hashComputations = 0;
  }

  void print(const string &operation, const string &key) {
    cout << "\n----------------------------------------------------------------"
            "\n";
    cout << " LOG: " << operation << " | KEY: " << key << "\n";
    cout << "-----------------------------------------------------------------"
            "\n";
    cout << " neuporyad: " << unsortedComparisons << " srav.\n";
    cout << " otsort: " << sortedComparisons << " srav. + " << sortedShifts
         << " sdwig\n";
    cout << " AVL:             " << avlComparisons << " srav. + "
         << avlRotations << " povor.\n";
    cout << " HASH (2):  " << hashComputations << " hash + " << hashProbes
         << " prob\n";
    cout << "----------------------------------------------------------------"
            "\n";
  }
};

class UnsortedArrayTable {
  vector<pair<string, Polynom>> data;
  OperationLog *log;

public:
  UnsortedArrayTable(OperationLog *l) : log(l) {}

  void insert(const string &key, const Polynom &poly) {
    data.push_back({key, poly});
  }

  Polynom *find(const string &key) {
    log->unsortedComparisons = 0;
    for (auto &item : data) {
      log->unsortedComparisons++;
      if (item.first == key)
        return &item.second;
    }
    return nullptr;
  }

  bool remove(const string &key) {
    for (auto it = data.begin(); it != data.end(); ++it) {
      if (it->first == key) {
        data.erase(it);
        return true;
      }
    }
    return false;
  }
};

class SortedArrayTable {
  vector<pair<string, Polynom>> data;
  OperationLog *log;

public:
  SortedArrayTable(OperationLog *l) : log(l) {}

  void insert(const string &key, const Polynom &poly) {
    int left = 0, right = data.size() - 1;
    int pos = data.size();
    log->sortedComparisons = 0;

    while (left <= right) {
      int mid = (left + right) / 2;
      log->sortedComparisons++;
      if (data[mid].first < key) {
        left = mid + 1;
      } else if (data[mid].first > key) {
        right = mid - 1;
        pos = mid;
      } else {
        pos = mid;
        break;
      }
    }

    log->sortedShifts = data.size() - pos;
    data.insert(data.begin() + pos, {key, poly});
  }

  Polynom *find(const string &key) {
    int left = 0, right = data.size() - 1;
    log->sortedComparisons = 0;

    while (left <= right) {
      int mid = (left + right) / 2;
      log->sortedComparisons++;
      if (data[mid].first == key)
        return &data[mid].second;
      else if (data[mid].first < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
    return nullptr;
  }
};

struct AVLNode {
  string key;
  Polynom value;
  AVLNode *left;
  AVLNode *right;
  int height;
  AVLNode(string k, const Polynom &v)
      : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTable {
  AVLNode *root;
  OperationLog *log;

  int height(AVLNode *n) { return n ? n->height : 0; }
  int balanceFactor(AVLNode *n) {
    return n ? height(n->left) - height(n->right) : 0;
  }

  AVLNode *rotateRight(AVLNode *y) {
    log->avlRotations++;
    AVLNode *x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
  }

  AVLNode *rotateLeft(AVLNode *x) {
    log->avlRotations++;
    AVLNode *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
  }

  AVLNode *insert(AVLNode *node, const string &key, const Polynom &value) {
    if (!node)
      return new AVLNode(key, value);

    log->avlComparisons++;
    if (key < node->key) {
      node->left = insert(node->left, key, value);
    } else if (key > node->key) {
      node->right = insert(node->right, key, value);
    } else {
      node->value = value;
      return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
      return rotateRight(node);
    if (balance < -1 && key > node->right->key)
      return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    return node;
  }

  AVLNode *find(AVLNode *node, const string &key) {
    if (!node)
      return nullptr;
    log->avlComparisons++;
    if (key == node->key)
      return node;
    if (key < node->key)
      return find(node->left, key);
    return find(node->right, key);
  }

  void destroy(AVLNode *node) {
    if (node) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }

public:
  AVLTable(OperationLog *l) : root(nullptr), log(l) {}
  ~AVLTable() { destroy(root); }

  void insert(const string &key, const Polynom &value) {
    root = insert(root, key, value);
  }

  Polynom *find(const string &key) {
    log->avlComparisons = 0;
    AVLNode *res = find(root, key);
    return res ? &res->value : nullptr;
  }
};

class DoubleHashTable {
  struct Entry {
    string key;
    Polynom value;
    bool occupied;
    bool deleted;
    Entry() : occupied(false), deleted(false) {}
  };

  vector<Entry> table;
  int size;
  int capacity;
  OperationLog *log;

  size_t h1(const string &key) {
    log->hashComputations++;
    size_t hash = 0;
    for (char c : key)
      hash = (hash * 131 + c) % capacity;
    return hash;
  }

  size_t h2(const string &key) {
    log->hashComputations++;
    size_t hash = 0;
    for (char c : key)
      hash = (hash * 137 + c) % capacity;
    return (hash % (capacity - 1)) + 1;
  }

  void resize() {
    int oldCap = capacity;
    capacity *= 2;
    vector<Entry> oldTable = move(table);
    table.clear();
    table.resize(capacity);
    size = 0;

    for (auto &e : oldTable) {
      if (e.occupied && !e.deleted) {
        insert(e.key, e.value);
      }
    }
  }

public:
  DoubleHashTable(OperationLog *l, int initCap = 16)
      : capacity(initCap), size(0), log(l) {
    table.resize(capacity);
  }

  void insert(const string &key, const Polynom &value) {
    if (size * 2 >= capacity)
      resize();

    size_t i = 0;
    size_t idx = h1(key);
    size_t step = h2(key);

    while (table[idx].occupied && !table[idx].deleted) {
      log->hashProbes++;
      if (table[idx].key == key) {
        table[idx].value = value;
        return;
      }
      i++;
      idx = (h1(key) + i * step) % capacity;
    }

    table[idx].key = key;
    table[idx].value = value;
    table[idx].occupied = true;
    table[idx].deleted = false;
    size++;
  }

  Polynom *find(const string &key) {
    log->hashProbes = 0;
    size_t i = 0;
    size_t idx = h1(key);
    size_t step = h2(key);

    while (table[idx].occupied) {
      if (!table[idx].deleted && table[idx].key == key) {
        return &table[idx].value;
      }
      log->hashProbes++;
      i++;
      idx = (h1(key) + i * step) % capacity;
      if (i >= (size_t)capacity)
        break;
    }
    return nullptr;
  }
};

Polynom inputPoly() {
  Polynom p;
  int n;
  cout << " kol-vo odnoclenov: ";
  cin >> n;
  cout << " coeff x y z):\n";
  for (int i = 0; i < n; i++) {
    double c;
    int x, y, z;
    cin >> c >> x >> y >> z;
    p.addMonom(c, x * 100 + y * 10 + z);
  }
  return p;
}

int main() {
  OperationLog logger;

  UnsortedArrayTable unsorted(&logger);
  SortedArrayTable sorted(&logger);
  AVLTable avl(&logger);
  DoubleHashTable hash(&logger);

  int choice = 1;
  string name;

  do {
    cout << "1. ADD IN ALL                        \n";
    cout << "2. SEARCH IN ALL                         \n";
    cout << "3. (A + B) ADD RESULT \n";
    cout << "4. (A * B) ADD RESULT \n";
    cout << "5. (A * scalar) ADD RESULT       \n";
    cin >> choice;

    if (choice == 1) {
      cout << "NAME POLY: ";
      cin >> name;
      cout << "POLY:\n";
      Polynom p = inputPoly();

      logger.reset();
      unsorted.insert(name, p);
      sorted.insert(name, p);
      avl.insert(name, p);
      hash.insert(name, p);
      logger.print("INSERT", name);

    } else if (choice == 2) {
      cout << "NAME POLY: ";
      cin >> name;

      cout << "\nSEARCH \"" << name << "\":\n";

      logger.reset();
      Polynom *p1 = unsorted.find(name);
      logger.print("SEARCH (neupor.)", name);
      if (p1) {
        cout << "yes: ";
        p1->print();
      }
      logger.reset();
      Polynom *p2 = sorted.find(name);
      logger.print("SEARCH (otsort.)", name);
      if (p2) {
        cout << "yes: ";
        p2->print();
      }
      logger.reset();
      Polynom *p3 = avl.find(name);
      logger.print("SEARCH (AVL)", name);
      if (p3) {
        cout << "yes: ";
        p3->print();
      }
      logger.reset();
      Polynom *p4 = hash.find(name);
      logger.print("SEARCH (hash)", name);
      if (p4) {
        cout << "yes: ";
        p4->print();
      }

      if (!p1 && !p2 && !p3 && !p4) {
        cout << "\nno!\n";
      }

    } else if (choice == 3) {
      string name1, name2, resName;
      cout << "name 1: ";
      cin >> name1;
      cout << "name 2: ";
      cin >> name2;
      cout << "nsme 3: ";
      cin >> resName;

      Polynom *a = unsorted.find(name1);
      if (!a)
        a = avl.find(name1);
      if (!a)
        a = hash.find(name1);

      Polynom *b = unsorted.find(name2);
      if (!b)
        b = avl.find(name2);
      if (!b)
        b = hash.find(name2);

      if (!a || !b) {
        cout << "ERROR: One of the polynomials not found!\n";
        continue;
      }

      Polynom result = *a + *b;
      cout << "res A + B: ";
      result.print();

      logger.reset();
      unsorted.insert(resName, result);
      sorted.insert(resName, result);
      avl.insert(resName, result);
      hash.insert(resName, result);
      logger.print("INSERT (res)", resName);

    } else if (choice == 4) {
      string name1, name2, resName;
      cout << "name 1: ";
      cin >> name1;
      cout << "name 2: ";
      cin >> name2;
      cout << "name 3: ";
      cin >> resName;

      Polynom *a = unsorted.find(name1);
      if (!a)
        a = avl.find(name1);
      if (!a)
        a = hash.find(name1);

      Polynom *b = unsorted.find(name2);
      if (!b)
        b = avl.find(name2);
      if (!b)
        b = hash.find(name2);

      if (!a || !b) {
        cout << "ERROR: One of the polynomials not found!\n";
        continue;
      }

      Polynom result = *a * *b;
      cout << "res A * B: ";
      result.print();

      logger.reset();
      unsorted.insert(resName, result);
      sorted.insert(resName, result);
      avl.insert(resName, result);
      hash.insert(resName, result);
      logger.print("INSERT (res)", resName);

    } else if (choice == 5) {
      string name1, resName;
      double scalar;
      cout << "name: ";
      cin >> name1;
      cout << "scal: ";
      cin >> scalar;
      cout << "name res: ";
      cin >> resName;

      Polynom *a = unsorted.find(name1);
      if (!a)
        a = avl.find(name1);
      if (!a)
        a = hash.find(name1);

      if (!a) {
        cout << "ERROR: Polynomial not found!\n";
        continue;
      }

      Polynom result = *a * scalar;
      cout << "res A * " << scalar << ": ";
      result.print();

      logger.reset();
      unsorted.insert(resName, result);
      sorted.insert(resName, result);
      avl.insert(resName, result);
      hash.insert(resName, result);
      logger.print("INSERT (res)", resName);
    }
  } while (choice != 0);
  cout << "\nend\n";
  return 0;
}
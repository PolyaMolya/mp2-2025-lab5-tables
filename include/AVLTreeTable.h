#pragma once
#include "Table.h"

struct Node {
  std::string key;
  Polinom value;
  Node *left, *right;
  int height;

  Node(std::string k, Polinom v)
      : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTreeTable : public Table {
 private:
  Node* root;

  int getHeight(Node* n);
  int getBalance(Node* n);
  Node* rotateRight(Node* y, int& ops);
  Node* rotateLeft(Node* x, int& ops);
  Node* insertRecursive(Node* node, std::string key, Polinom val, int& ops);
  Node* findRecursive(Node* node, std::string key, int& ops);

public:
  AVLTreeTable() : root(nullptr) {}

  int insert(std::string key, Polinom val) override;
  Polinom* find(std::string key, int& ops) override;
  int remove(std::string key) override { return 0; }
};

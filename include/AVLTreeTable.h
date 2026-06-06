#pragma once
#include "Table.h"

struct AVLNode {
  std::string key;
  Polinom data;
  AVLNode *leftNode;
  AVLNode *rightNode;
  int depth;

  AVLNode(std::string k, Polinom v)
      : key(k), data(v), leftNode(nullptr), rightNode(nullptr), depth(1) {}
};

class AVLTreeTable : public Table {
private:
  AVLNode* rootNode;

  int nodeDepth(AVLNode* node);
  int bFactor(AVLNode* node);
  AVLNode* rightRotate(AVLNode* y, int& counter);
  AVLNode* leftRotate(AVLNode* x, int& counter);
  AVLNode* addNode(AVLNode* node, std::string key, Polinom val, int& counter);

public:
  AVLTreeTable() : rootNode(nullptr) {}

  int insert(std::string key, Polinom val) override;
  Polinom* find(std::string key, int& ops) override;
  int remove(std::string key) override { return 0; }
};
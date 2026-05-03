#pragma once
#include "Polynomial.h"
#include <string>

enum Color { red, black };

struct RBNode {
  std::string key;
  Polynomial value;
  RBNode *left, *right, *parent;
  Color color;

  RBNode(std::string k, Polynomial v, RBNode *p = nullptr)
      : key(k), value(v), left(nullptr), right(nullptr), parent(p), color(red) {
  }
};

class RBTree {
private:
  RBNode *root;

  void rotateLeft(RBNode *&root, RBNode *x, size_t &ñount);
  void rotateRight(RBNode *&root, RBNode *y, size_t &ñount);
  void fixInsert(RBNode *&root, RBNode *&z, size_t &ñount);

  void clear(RBNode *node);

public:
  RBTree() { root = nullptr; }
  ~RBTree() { clear(root); }

  Polynomial *find(const std::string &key, size_t &count);

  void insert(const std::string &key, const Polynomial &poly, size_t &count);
};
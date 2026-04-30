#include "AVLTreeTable.h"
#include <algorithm>

int AVLTreeTable::getHeight(Node* n) { 
	return n ? n->height : 0;
}

int AVLTreeTable::getBalance(Node* n) {
  return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* AVLTreeTable::rotateRight(Node* y, int& ops) {
  ops++;
  Node* x = y->left;
  Node* T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}

Node* AVLTreeTable::rotateLeft(Node* x, int& ops) { 
  ops++;
  Node* y = x->right;
  Node* T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

Node* AVLTreeTable::insertRecursive(Node* node, std::string key, Polinom val,
	int& ops) {
  ops++;
  if (!node) return new Node(key, val);

  if (key < node->key)
    node->left = insertRecursive(node->left, key, val, ops);

  else if (key > node->key)
    node->right = insertRecursive(node->right, key, val, ops);

  else {
    node->value = val;
    return node;
  }
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key) return rotateRight(node, ops);

  if (balance < -1 && key > node->right->key) return rotateLeft(node, ops);

  if (balance > 1 && key > node->left->key) {
    node->left = rotateLeft(node->left, ops);
    return rotateRight(node, ops);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rotateRight(node->right, ops);
    return rotateLeft(node, ops);
  }
  return node;
}

int AVLTreeTable::insert(std::string key, Polinom val) { 
  int ops = 0;
  root = insertRecursive(root, key, val, ops);
  return ops;
}

Polinom* AVLTreeTable::find(std::string key, int& ops) { 
  ops = 0;
  Node* current = root;
  while (current) {
    ops++;
    if (key == current->key) 
      return &current->value;
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return nullptr;
}
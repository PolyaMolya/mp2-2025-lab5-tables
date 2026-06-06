#include "AVLTreeTable.h"
#include <algorithm>

int AVLTreeTable::nodeDepth(AVLNode* node) {
  if (!node) return 0;
  return node->depth;
}

int AVLTreeTable::bFactor(AVLNode* node) {
  if (!node) return 0;
  return nodeDepth(node->leftNode) - nodeDepth(node->rightNode);
}

AVLNode* AVLTreeTable::rightRotate(AVLNode* y, int& counter) {
  counter++;
  AVLNode* x = y->leftNode;
  AVLNode* temp = x->rightNode;

  x->rightNode = y;
  y->leftNode = temp;

  y->depth = std::max(nodeDepth(y->leftNode), nodeDepth(y->rightNode)) + 1;
  x->depth = std::max(nodeDepth(x->leftNode), nodeDepth(x->rightNode)) + 1;

  return x;
}

AVLNode* AVLTreeTable::leftRotate(AVLNode* x, int& counter) {
  counter++;
  AVLNode* y = x->rightNode;
  AVLNode* temp = y->leftNode;

  y->leftNode = x;
  x->rightNode = temp;

  x->depth = std::max(nodeDepth(x->leftNode), nodeDepth(x->rightNode)) + 1;
  y->depth = std::max(nodeDepth(y->leftNode), nodeDepth(y->rightNode)) + 1;

  return y;
}

AVLNode* AVLTreeTable::addNode(AVLNode* node, std::string key, Polinom val, int& counter) {
  counter++;
  if (!node) return new AVLNode(key, val);

  if (key < node->key) {
    node->leftNode = addNode(node->leftNode, key, val, counter);
  } else if (key > node->key) {
    node->rightNode = addNode(node->rightNode, key, val, counter);
  } else {
    node->data = val;
    return node;
  }

  node->depth = 1 + std::max(nodeDepth(node->leftNode), nodeDepth(node->rightNode));
  int balance = bFactor(node);

  if (balance > 1 && key < node->leftNode->key) return rightRotate(node, counter);
  if (balance < -1 && key > node->rightNode->key) return leftRotate(node, counter);

  if (balance > 1 && key > node->leftNode->key) {
    node->leftNode = leftRotate(node->leftNode, counter);
    return rightRotate(node, counter);
  }

  if (balance < -1 && key < node->rightNode->key) {
    node->rightNode = rightRotate(node->rightNode, counter);
    return leftRotate(node, counter);
  }

  return node;
}

int AVLTreeTable::insert(std::string key, Polinom val) {
  int counter = 0;
  rootNode = addNode(rootNode, key, val, counter);
  return counter;
}

Polinom* AVLTreeTable::find(std::string key, int& ops) {
  ops = 0;
  AVLNode* curr = rootNode;
  while (curr) {
    ops++;
    if (key == curr->key) {
      return &curr->data;
    }
    if (key < curr->key) {
      curr = curr->leftNode;
    } else {
      curr = curr->rightNode;
    }
  }
  return nullptr;
}
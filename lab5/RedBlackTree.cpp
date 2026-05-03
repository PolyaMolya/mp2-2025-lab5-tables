#include "RedBlackTree.h"
#include <iostream>

void RBTree::clear(RBNode *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

void RBTree::rotateLeft(RBNode *&root, RBNode *x, size_t &count) {
  count++;
  RBNode *y = x->right;
  x->right = y->left;

  if (y->left != nullptr) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

void RBTree::rotateRight(RBNode *&root, RBNode *y, size_t &count) {
  count++;
  RBNode *x = y->left;
  y->left = x->right;

  if (x->right != nullptr) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == nullptr) {
    root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  x->right = y;
  y->parent = x;
}

Polynomial *RBTree::find(const std::string &key, size_t &count) {
  count = 0;
  RBNode *current = root;
  while (current != nullptr) {
    count++;
    if (key == current->key)
      return &(current->value);

    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return nullptr;
}

void RBTree::fixInsert(RBNode *&root, RBNode *&z, size_t &count) {
  while (z != root && z->parent->color == red) {
    if (z->parent == z->parent->parent->left) {
      RBNode *y = z->parent->parent->right;
      if (y != nullptr && y->color == red) {

        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {

        if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(root, z, count);
        }

        z->parent->color = black;
        z->parent->parent->color = red;
        rotateRight(root, z->parent->parent, count);
      }
    } else {

      RBNode *y = z->parent->parent->left;
      if (y != nullptr && y->color == red) {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(root, z, count);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        rotateLeft(root, z->parent->parent, count);
      }
    }
  }
  root->color = black;
}

void RBTree::insert(const std::string &key, const Polynomial &poly,
                    size_t &count) {
  count = 0;
  RBNode *z = new RBNode(key, poly);
  RBNode *y = nullptr;
  RBNode *x = root;

  while (x != nullptr) {
    y = x;
    count++;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;
  if (y == nullptr)
    root = z;
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;

  fixInsert(root, z, count);
}
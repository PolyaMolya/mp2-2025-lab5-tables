#ifndef RBTREE_TABLE_H
#define RBTREE_TABLE_H

#include "itable.h"
#include <memory>
#include <vector>

enum Color { RED, BLACK };

template<typename K, typename V>
struct RBNode {
    K key;
    V value;
    Color color;
    std::shared_ptr<RBNode<K, V>> left;
    std::shared_ptr<RBNode<K, V>> right;
    std::shared_ptr<RBNode<K, V>> parent;

    RBNode(const K& k, const V& v)
        : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename KeyType, typename ValueType>
class RBTreeTable : public ITable<KeyType, ValueType> {
private:
    std::shared_ptr<RBNode<KeyType, ValueType>> root;
    size_t sz = 0;
    mutable size_t comparisons = 0;
    mutable size_t operations = 0;

    void rotateLeft(std::shared_ptr<RBNode<KeyType, ValueType>> x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(std::shared_ptr<RBNode<KeyType, ValueType>> y) {
        auto x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(std::shared_ptr<RBNode<KeyType, ValueType>> z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                auto y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            }
            else {
                auto y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    std::shared_ptr<RBNode<KeyType, ValueType>> findNode(const KeyType& key) const {
        auto cur = root;
        while (cur) {
            comparisons++;
            if (key < cur->key) cur = cur->left;
            else if (key > cur->key) cur = cur->right;
            else return cur;
        }
        return nullptr;
    }

    void inorder(std::shared_ptr<RBNode<KeyType, ValueType>> node, std::vector<KeyType>& keys) const {
        if (!node) return;
        inorder(node->left, keys);
        keys.push_back(node->key);
        inorder(node->right, keys);
    }

    void transplant(std::shared_ptr<RBNode<KeyType, ValueType>> u,
        std::shared_ptr<RBNode<KeyType, ValueType>> v) {
        if (!u->parent) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v) {
            v->parent = u->parent;
        }
    }

    std::shared_ptr<RBNode<KeyType, ValueType>> minimum(std::shared_ptr<RBNode<KeyType, ValueType>> node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void fixRemove(std::shared_ptr<RBNode<KeyType, ValueType>> x) {
        while (x != root && (!x || x->color == BLACK)) {
            if (x == x->parent->left) {
                auto w = x->parent->right;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if ((!w->left || w->left->color == BLACK) &&
                    (!w->right || w->right->color == BLACK)) {
                    if (w) w->color = RED;
                    x = x->parent;
                }
                else {
                    if (!w->right || w->right->color == BLACK) {
                        if (w->left) w->left->color = BLACK;
                        if (w) w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    if (w) {
                        w->color = x->parent->color;
                        if (w->right) w->right->color = BLACK;
                    }
                    x->parent->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else {
                auto w = x->parent->left;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if ((!w->right || w->right->color == BLACK) &&
                    (!w->left || w->left->color == BLACK)) {
                    if (w) w->color = RED;
                    x = x->parent;
                }
                else {
                    if (!w->left || w->left->color == BLACK) {
                        if (w->right) w->right->color = BLACK;
                        if (w) w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    if (w) {
                        w->color = x->parent->color;
                        if (w->left) w->left->color = BLACK;
                    }
                    x->parent->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        if (x) x->color = BLACK;
    }

public:
    RBTreeTable() : root(nullptr), sz(0), comparisons(0), operations(0) {}

    std::string name() const override {
        return "RBTree";
    }

    void resetCounters() override {
        comparisons = 0;
        operations = 0;
    }

    void insert(const KeyType& key, const ValueType& value) override {
        auto z = std::make_shared<RBNode<KeyType, ValueType>>(key, value);
        std::shared_ptr<RBNode<KeyType, ValueType>> y = nullptr;
        auto x = root;

        while (x) {
            comparisons++;
            y = x;
            if (z->key < x->key) x = x->left;
            else if (z->key > x->key) x = x->right;
            else {
                x->value = value;
                operations++;
                return;
            }
        }
        z->parent = y;
        if (!y) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;

        fixInsert(z);
        sz++;
        operations++;
    }

    bool find(const KeyType& key, ValueType& value) const override {
        auto node = findNode(key);
        if (node) {
            value = node->value;
            operations++;
            return true;
        }
        return false;
    }

    bool remove(const KeyType& key) override {
        auto z = findNode(key);
        if (!z) return false;

        comparisons++;

        Color originalColor = z->color;
        std::shared_ptr<RBNode<KeyType, ValueType>> x;

        // Случай 1: нет левого ребенка
        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        }
        // Случай 2: нет правого ребенка
        else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        }
        // Случай 3: есть оба ребенка
        else {
            auto y = minimum(z->right);
            originalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x) x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (originalColor == BLACK) {
            fixRemove(x);
        }

        sz--;
        operations++;
        return true;
    }

    bool contains(const KeyType& key) const override {
        ValueType dummy;
        return find(key, dummy);
    }

    size_t size() const override {
        return sz;
    }

    void clear() override {
        root = nullptr;
        sz = 0;
    }

    std::vector<KeyType> keys() const override {
        std::vector<KeyType> res;
        inorder(root, res);
        return res;
    }

    size_t getComparisons() const override {
        return comparisons;
    }

    size_t getOperations() const override {
        return operations;
    }
};

#endif
#pragma once
#include <string>
#include "Polinom.h"

struct AVLNode {
	std::string key;
	Polinom pol;
	AVLNode* left;
	AVLNode* right;
	int height;
	AVLNode(const std::string& k, const Polinom& p) : key(k), pol(p), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
	AVLNode* root;
	int height(AVLNode* n) const;
	int balFactor(AVLNode* n) const;
	AVLNode* rotR(AVLNode* y);
	AVLNode* rotL(AVLNode* x);
	AVLNode* balance(AVLNode* n);
	AVLNode* insertRec(AVLNode* n, const std::string& key, const Polinom& pol, int& comparisons);
	AVLNode* findMinNode(AVLNode* n) const;
	AVLNode* removeMinNode(AVLNode* n);
	AVLNode* removeRec(AVLNode* n, const std::string& key, Polinom& remPol, int& comparisons);
	const Polinom* findRec(AVLNode* n, const std::string& key, int& comparisons) const;
	void destroyTree(AVLNode* n);
public:
	AVL();
	~AVL();
	int insert(const std::string& key, const Polinom& pol);
	const Polinom* find(const std::string& key, int& comparisons) const;
	bool remove(const std::string& key, Polinom& remPol, int& comparisons);
	void print() const;
	void printRec(AVLNode* n) const;
};
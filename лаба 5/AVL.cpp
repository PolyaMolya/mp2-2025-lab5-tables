#include "AVL.h"
#include <algorithm>
#include <iostream>

AVL::AVL() :root(nullptr) {};
AVL::~AVL() {
	destroyTree(root);
}

void AVL::destroyTree(AVLNode* n) {
	if (!n) return;
	destroyTree(n->left);
	destroyTree(n->right);
	delete n;
}

int AVL::height(AVLNode* n) const {
	return n ? n->height : 0;
}

int AVL::balFactor(AVLNode* n) const {
	return n ? height(n->left) - height(n->right) : 0;
}

AVLNode* AVL::rotR(AVLNode* y) {
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = std::max(height(y->left), height(y->right)) + 1;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	return x;
}

AVLNode* AVL::rotL(AVLNode* x) {
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	y->height = std::max(height(y->left), height(y->right)) + 1;
	return y;
}

AVLNode* AVL::balance(AVLNode* n) {
	if (!n) return n;
	n->height = std::max(height(n->left), height(n->right)) + 1;
	int bf = balFactor(n);
	//LL
	if (bf > 1 && balFactor(n->left) >= 0)
		return rotR(n);
	//LR
	if (bf > 1 && balFactor(n->left) < 0) {
		n->left = rotL(n->left);
		return rotR(n);
	}
	//RR
	if (bf < -1 && balFactor(n->right) <= 0)
		return rotL(n);
	//RL
	if (bf < -1 && balFactor(n->right)>0) {
		n->right = rotR(n->right);
		return rotL(n);
	}
	return n;
}

AVLNode* AVL::insertRec(AVLNode* n, const std::string& key, const Polinom& pol, int& comparisons) {
	if (!n)
		return new AVLNode(key, pol);
	++comparisons;
	if (key < n->key) {
		n->left = insertRec(n->left, key, pol, comparisons);
	}
	else if (key > n->key) {
		n->right = insertRec(n->right, key, pol, comparisons);
	}
	else {
		n->pol = pol;
		return n;
	}
	return balance(n);
}

int AVL::insert(const std::string& key, const Polinom& pol) {
	int comparisons = 0;
	root = insertRec(root, key, pol, comparisons);
	return comparisons;
}

const Polinom* AVL::findRec(AVLNode* n, const std::string& key, int& comparisons) const {
	if (!n) return nullptr;
	++comparisons;
	if (key == n->key)
		return &n->pol;
	else if (key < n->key)
		return findRec(n->left, key, comparisons);
	else 
		return findRec(n->right, key, comparisons);

}

const Polinom* AVL::find(const std::string& key, int& comparisons) const {
	comparisons = 0;
	return findRec(root, key, comparisons);
}

AVLNode* AVL::findMinNode(AVLNode* n) const {
	while (n && n->left) n = n->left;
	return n;
}

AVLNode* AVL::removeMinNode(AVLNode* n) {
	if (!n->left) {
		AVLNode* right = n->right;
		delete n;
		return right;
	}
	n->left = removeMinNode(n->left);
	return balance(n);
}

AVLNode* AVL::removeRec(AVLNode* n, const std::string& key, Polinom& removPol, int& comparisons) {
	if (!n) return nullptr;

	++comparisons;
	if (key < n->key)
		n->left = removeRec(n->left, key, removPol, comparisons);
	else if (key > n->key)
		n->right = removeRec(n->right, key, removPol, comparisons);
	else {
		removPol = n->pol;
		//1 net left son
		if (!n->left) {
			AVLNode* right = n->right;
			delete n;
			return right;
		}
		//2 net right son
		else if (!n->right) {
			AVLNode* left = n->left;
			delete n;
			return left;
		}
		//3 est left i right
		else {
			AVLNode* minNode = findMinNode(n->right);
			n->key = minNode->key;
			n->pol = minNode->pol;
			n->right = removeMinNode(n->right);
		}
	}
	return balance(n);
}

bool AVL::remove(const std::string& key, Polinom& removePol, int& comparisons) {
	comparisons = 0;
	root = removeRec(root, key, removePol, comparisons);
	return !(root == nullptr && comparisons == 0);
}

void AVL::printRec(AVLNode* n) const {
	if (!n) return;
	printRec(n->left);
	std::cout << " " << n->key << " = ";
	n->pol.print();
	std::cout << "\n";
	printRec(n->right);
}

void AVL::print() const {
	std::cout << "AVL tree:\n";
	printRec(root);
}
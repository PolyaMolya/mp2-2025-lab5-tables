#pragma once
#include <cmath>
#include <iostream>
#include <string>

struct Monom {
  double coeff;
  int degree;
  Monom(double c = 0.0, int d = 0) : coeff(c), degree(d) {}
};

struct Node {
  Monom data;
  Node *next;
  Node(Monom m, Node *n = nullptr) : data(m), next(n) {}
};

class Polynomial {
private:
  Node *head;
  void copy(const Polynomial &other);
  void clear();
  void insert_ordered(Monom m);

public:
  Polynomial();
  ~Polynomial();
  Polynomial(const Polynomial &other);
  Polynomial &operator=(const Polynomial &other);

  void add_monom(double coeff, int x, int y, int z);

  Polynomial operator+(const Polynomial &other) const;
  Polynomial operator-(const Polynomial &other) const;
  Polynomial operator*(double scalar) const;
  Polynomial operator*(const Polynomial &other) const;

  void print() const;
};

void inputPolynomial(Polynomial &p);

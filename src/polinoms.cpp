#include "polinoms.h"
#include <iostream>

Monom::Monom() {
  coeff = 0.0;
  degree = 0;
  next = nullptr;
}
Monom::Monom(double c, int d, Monom *n) {
  coeff = c;
  degree = d;
  next = n;
}

Polinom::Polinom() {
  head = new Monom(0.0, -1);
  head->next = nullptr;
}

Polinom::Polinom(const Polinom &other) {
  head = new Monom(0.0, -1);
  head->next = nullptr;

  Monom *tmp = other.head->next;
  while (tmp != nullptr) {
    this->addMonom(tmp->coeff, tmp->degree);
    tmp = tmp->next;
  }
}

Polinom::~Polinom() {
  Monom *current = head;

  while (current != nullptr) {
    Monom *nextNode = current->next;
    delete current;
    current = nextNode;
  }
}

void Polinom::addMonom(double c, int d) {
  if (c == 0) return;

  Monom *prev = head;
  Monom *current = head->next;

  while (current != nullptr && current->degree < d) {
    prev = current;
    current = current->next;
  }

  if (current != nullptr && current->degree == d) {
    current->coeff = current->coeff + c;
    if (current->coeff == 0) {
      prev->next = current->next;
      delete current;
    }
    return;
  }
  Monom *newNode = new Monom(c, d, current);
  prev->next = newNode;
}

void Polinom::print() {
  Monom *tmp = head->next;
  if (tmp == nullptr) {
    std::cout << "0" << std::endl;
    return;
  }

  bool first = true;

  while (tmp != nullptr) {
    double coeff = tmp->coeff;

    if (coeff > 0 && !first) std::cout << "+";

    std::cout << coeff;

    int d = tmp->degree;
    int x = d / 100;
    int y = (d / 10) % 10;
    int z = d % 10;

    if (x > 0) std::cout << "x^" << x;
    if (y > 0) std::cout << "y^" << y;
    if (z > 0) std::cout << "z^" << z;

    tmp = tmp->next;
    first = false;
  }
}

Polinom Polinom::operator+(const Polinom &other) const {
  Polinom res;

  const Monom *p1 = head->next;

  while (p1 != nullptr) {
    res.addMonom(p1->coeff, p1->degree);
    p1 = p1->next;
  }

  const Monom *p2 = other.head->next;

  while (p2 != nullptr) {
    res.addMonom(p2->coeff, p2->degree);
    p2 = p2->next;
  }
  return res;
}

Polinom Polinom::operator-(const Polinom &other) const {
  Polinom res;

  const Monom *p1 = head->next;

  while (p1 != nullptr) {
    res.addMonom(p1->coeff, p1->degree);
    p1 = p1->next;
  }

  const Monom *p2 = other.head->next;

  while (p2 != nullptr) {
    res.addMonom(-(p2->coeff), p2->degree);
    p2 = p2->next;
  }
  return res;
}

Polinom Polinom::operator*(const Polinom &other) const {
  Polinom res;

  for (const Monom *p1 = head->next; p1 != nullptr; p1 = p1->next) {
    for (const Monom *p2 = other.head->next; p2 != nullptr; p2 = p2->next) {
      int d1 = p1->degree;
      int d2 = p2->degree;

      if ((d1 / 100 + d2 / 100 > 9) || ((d1 / 10) % 10 + (d2 / 10) % 10 > 9) ||
          (d1 % 10 + d2 % 10 > 9)) {
        throw std::runtime_error("Degree above 9");
      }

      int newDegree = d1 + d2;
      double newCoeff = p1->coeff * p2->coeff;

      res.addMonom(newCoeff, newDegree);
    }
  }
  return res;
}

Polinom Polinom::operator*(double value) const {
  Polinom res;

  if (value == 0) return res;

  const Monom *p1 = head->next;

  while (p1 != nullptr) {
    double newCoeff = value * p1->coeff;
    res.addMonom(newCoeff, p1->degree);
    p1 = p1->next;
  }
  return res;
}

Polinom Polinom::operator=(const Polinom &other) {
  if (this == &other) return *this;

  Monom *p1 = head->next;
  while (p1 != nullptr) {
    Monom *next = p1->next;
    delete p1;
    p1 = next;
  }

  head->next = nullptr;

  Monom *p2 = other.head->next;
  while (p2 != nullptr) {
    this->addMonom(p2->coeff, p2->degree);
    p2 = p2->next;
  }
  return *this;
}

bool Polinom::operator==(const Polinom &other) const {
  Monom *p1 = head->next;
  Monom *p2 = other.head->next;

  while (p1 != nullptr && p2 != nullptr) {
    if (p1->degree != p2->degree || p1->coeff != p2->coeff) {
      return false;
    }
    p1 = p1->next;
    p2 = p2->next;
  }
  return (p1 == nullptr && p2 == nullptr);
}
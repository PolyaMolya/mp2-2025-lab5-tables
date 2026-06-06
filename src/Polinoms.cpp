#include "polinoms.h"
#include <iostream>
#include <stdexcept>

Monomial::Monomial() {
  coefficient = 0.0;
  power = 0;
  nextNode = nullptr;
}

Monomial::Monomial(double coef, int pwr, Monomial *next) {
  coefficient = coef;
  power = pwr;
  nextNode = next;
}

Polinom::Polinom() {
  dummyHead = new Monomial(0.0, -1);
  dummyHead->nextNode = nullptr;
}

Polinom::Polinom(const Polinom &other) {
  dummyHead = new Monomial(0.0, -1);
  dummyHead->nextNode = nullptr;

  Monomial *temp = other.dummyHead->nextNode;
  while (temp != nullptr) {
    this->addMonom(temp->coefficient, temp->power);
    temp = temp->nextNode;
  }
}

Polinom::~Polinom() {
  Monomial *curr = dummyHead;
  while (curr != nullptr) {
    Monomial *next = curr->nextNode;
    delete curr;
    curr = next;
  }
}

void Polinom::addMonom(double coef, int pwr) {
  if (coef == 0.0) return;

  Monomial *prevNode = dummyHead;
  Monomial *currNode = dummyHead->nextNode;

  while (currNode != nullptr && currNode->power < pwr) {
    prevNode = currNode;
    currNode = currNode->nextNode;
  }

  if (currNode != nullptr && currNode->power == pwr) {
    currNode->coefficient += coef;
    if (currNode->coefficient == 0.0) {
      prevNode->nextNode = currNode->nextNode;
      delete currNode;
    }
    return;
  }

  Monomial *newNode = new Monomial(coef, pwr, currNode);
  prevNode->nextNode = newNode;
}

void Polinom::print() {
  Monomial *temp = dummyHead->nextNode;
  if (temp == nullptr) {
    std::cout << "0" << std::endl;
    return;
  }

  bool isFirst = true;
  while (temp != nullptr) {
    double c = temp->coefficient;
    if (c > 0 && !isFirst) {
      std::cout << "+";
    }
    std::cout << c;

    int deg = temp->power;
    int p1 = deg / 100;
    int p2 = (deg / 10) % 10;
    int p3 = deg % 10;

    if (p1 > 0) std::cout << "x^" << p1;
    if (p2 > 0) std::cout << "y^" << p2;
    if (p3 > 0) std::cout << "z^" << p3;

    temp = temp->nextNode;
    isFirst = false;
  }
}

Polinom Polinom::operator+(const Polinom &other) const {
  Polinom result;
  Monomial *ptr1 = dummyHead->nextNode;
  while (ptr1 != nullptr) {
    result.addMonom(ptr1->coefficient, ptr1->power);
    ptr1 = ptr1->nextNode;
  }

  Monomial *ptr2 = other.dummyHead->nextNode;
  while (ptr2 != nullptr) {
    result.addMonom(ptr2->coefficient, ptr2->power);
    ptr2 = ptr2->nextNode;
  }
  return result;
}

Polinom Polinom::operator-(const Polinom &other) const {
  Polinom result;
  Monomial *ptr1 = dummyHead->nextNode;
  while (ptr1 != nullptr) {
    result.addMonom(ptr1->coefficient, ptr1->power);
    ptr1 = ptr1->nextNode;
  }

  Monomial *ptr2 = other.dummyHead->nextNode;
  while (ptr2 != nullptr) {
    result.addMonom(-(ptr2->coefficient), ptr2->power);
    ptr2 = ptr2->nextNode;
  }
  return result;
}

Polinom Polinom::operator*(const Polinom &other) const {
  Polinom result;
  for (Monomial *ptr1 = dummyHead->nextNode; ptr1 != nullptr; ptr1 = ptr1->nextNode) {
    for (Monomial *ptr2 = other.dummyHead->nextNode; ptr2 != nullptr; ptr2 = ptr2->nextNode) {
      int d1 = ptr1->power;
      int d2 = ptr2->power;

      if ((d1 / 100 + d2 / 100 > 9) || ((d1 / 10) % 10 + (d2 / 10) % 10 > 9) || (d1 % 10 + d2 % 10 > 9)) {
        throw std::runtime_error("Degree above 9");
      }

      int resDeg = d1 + d2;
      double resCoef = ptr1->coefficient * ptr2->coefficient;
      result.addMonom(resCoef, resDeg);
    }
  }
  return result;
}

Polinom Polinom::operator*(double multiplier) const {
  Polinom result;
  if (multiplier == 0.0) return result;

  Monomial *ptr1 = dummyHead->nextNode;
  while (ptr1 != nullptr) {
    result.addMonom(ptr1->coefficient * multiplier, ptr1->power);
    ptr1 = ptr1->nextNode;
  }
  return result;
}

Polinom Polinom::operator=(const Polinom &other) {
  if (this == &other) return *this;

  Monomial *ptr1 = dummyHead->nextNode;
  while (ptr1 != nullptr) {
    Monomial *nextMonom = ptr1->nextNode;
    delete ptr1;
    ptr1 = nextMonom;
  }
  dummyHead->nextNode = nullptr;

  Monomial *ptr2 = other.dummyHead->nextNode;
  while (ptr2 != nullptr) {
    this->addMonom(ptr2->coefficient, ptr2->power);
    ptr2 = ptr2->nextNode;
  }
  return *this;
}

bool Polinom::operator==(const Polinom &other) const {
  Monomial *ptr1 = dummyHead->nextNode;
  Monomial *ptr2 = other.dummyHead->nextNode;

  while (ptr1 != nullptr && ptr2 != nullptr) {
    if (ptr1->power != ptr2->power || ptr1->coefficient != ptr2->coefficient) {
      return false;
    }
    ptr1 = ptr1->nextNode;
    ptr2 = ptr2->nextNode;
  }
  return (ptr1 == nullptr && ptr2 == nullptr);
}
#include "Polynom.h"
#include <cmath>
#include <stdexcept>

Polynom::Polynom() { head = new Monom{0, 0, nullptr}; }

Polynom::Polynom(const Polynom &other) {
  head = new Monom{0, 0, nullptr};
  Monom *curr = other.head->next;
  while (curr) {
    this->addMonom(curr->coeff, curr->degree);
    curr = curr->next;
  }
}

Polynom::~Polynom() {
  Monom *curr = head;
  while (curr) {
    Monom *tmp = curr;
    curr = curr->next;
    delete tmp;
  }
}

Polynom &Polynom::operator=(const Polynom &other) {
  if (this == &other) {
    return *this;
  }

  Monom *curr = head;
  while (curr) {
    Monom *tmp = curr;
    curr = curr->next;
    delete tmp;
  }

  head = new Monom{0, 0, nullptr};
  Monom *otherCurr = other.head->next;
  while (otherCurr) {
    this->addMonom(otherCurr->coeff, otherCurr->degree);
    otherCurr = otherCurr->next;
  }

  return *this;
}

int Polynom::getX(int deg) const { return deg / 100; }
int Polynom::getY(int deg) const { return (deg / 10) % 10; }
int Polynom::getZ(int deg) const { return deg % 10; }

int Polynom::makeDegree(int x, int y, int z) const {
  return x * 100 + y * 10 + z;
}

void Polynom::addMonom(double coeff, int degree) {
  if (coeff == 0)
    return;

  Monom *prev = head;
  Monom *curr = head->next;

  while (curr && curr->degree > degree) {
    prev = curr;
    curr = curr->next;
  }

  if (curr && curr->degree == degree) {
    curr->coeff += coeff;
    if (curr->coeff == 0) {
      prev->next = curr->next;
      delete curr;
    }
  } else {
    Monom *node = new Monom{coeff, degree, curr};
    prev->next = node;
  }
}

Polynom Polynom::operator+(const Polynom &other) const {
  Polynom result;

  Monom *a = head->next;
  Monom *b = other.head->next;

  while (a && b) {
    if (a->degree > b->degree) {
      result.addMonom(a->coeff, a->degree);
      a = a->next;
    } else if (a->degree < b->degree) {
      result.addMonom(b->coeff, b->degree);
      b = b->next;
    } else {
      result.addMonom(a->coeff + b->coeff, a->degree);
      a = a->next;
      b = b->next;
    }
  }

  while (a) {
    result.addMonom(a->coeff, a->degree);
    a = a->next;
  }

  while (b) {
    result.addMonom(b->coeff, b->degree);
    b = b->next;
  }

  return result;
}

Polynom Polynom::operator-(const Polynom &other) const {
  return *this + (other * -1.0);
}

Polynom Polynom::operator*(double scalar) const {
  Polynom result;

  for (Monom *curr = head->next; curr; curr = curr->next) {
    result.addMonom(curr->coeff * scalar, curr->degree);
  }

  return result;
}

Polynom Polynom::operator*(const Polynom &other) const {
  Polynom result;

  for (Monom *a = head->next; a; a = a->next) {
    for (Monom *b = other.head->next; b; b = b->next) {
      int x = getX(a->degree) + getX(b->degree);
      int y = getY(a->degree) + getY(b->degree);
      int z = getZ(a->degree) + getZ(b->degree);

      if (x > 9 || y > 9 || z > 9)
        throw std::runtime_error("Degree overflow");

      int deg = makeDegree(x, y, z);
      result.addMonom(a->coeff * b->coeff, deg);
    }
  }

  return result;
}

void Polynom::print() const {
  Monom *curr = head->next;

  while (curr) {
    std::cout << curr->coeff << "(deg=" << curr->degree << ") ";
    curr = curr->next;
  }
  std::cout << std::endl;
}

bool Polynom::operator==(const Polynom &other) const {
  Monom *a = head->next;
  Monom *b = other.head->next;

  while (a && b) {
    if (a->degree != b->degree || abs(a->coeff - b->coeff) > 1e-6)
      return false;
    a = a->next;
    b = b->next;
  }

  return a == nullptr && b == nullptr;
}
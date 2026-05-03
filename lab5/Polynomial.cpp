#include "Polynomial.h"

Polynomial::Polynomial() { head = new Node(Monom(0, -1)); }

Polynomial::~Polynomial() {
  clear();
  delete head;
}

void Polynomial::copy(const Polynomial &other) {
  Node *currOther = other.head->next;
  Node *currThis = head;
  while (currOther) {
    currThis->next = new Node(currOther->data);
    currThis = currThis->next;
    currOther = currOther->next;
  }
}

void Polynomial::clear() {
  Node *curr = head->next;
  while (curr) {
    Node *temp = curr;
    curr = curr->next;
    delete temp;
  }
  head->next = nullptr;
}

void Polynomial::insert_ordered(Monom m) {
  if (std::abs(m.coeff) < 1e-10)
    return;
  Node *prev = head;
  Node *curr = head->next;
  while (curr && curr->data.degree > m.degree) {
    prev = curr;
    curr = curr->next;
  }
  if (curr && curr->data.degree == m.degree) {
    curr->data.coeff += m.coeff;
    if (std::abs(curr->data.coeff) < 1e-10) {
      prev->next = curr->next;
      delete curr;
    }
  } else {
    prev->next = new Node(m, curr);
  }
}

Polynomial::Polynomial(const Polynomial &other) : Polynomial() { copy(other); }

Polynomial &Polynomial::operator=(const Polynomial &other) {
  if (this != &other) {
    clear();
    copy(other);
  }
  return *this;
}

void Polynomial::add_monom(double coeff, int x, int y, int z) {
  if (x < 0 || x > 9 || y < 0 || y > 9 || z < 0 || z > 9) {
    throw std::out_of_range("Degree of the variable must be from 0 to 9");
  }
  insert_ordered(Monom(coeff, x * 100 + y * 10 + z));
}

Polynomial Polynomial::operator+(const Polynomial &other) const {
  Polynomial res;
  Node *p1 = head->next;
  Node *p2 = other.head->next;
  while (p1 || p2) {
    if (p1 && (!p2 || p1->data.degree > p2->data.degree)) {
      res.insert_ordered(p1->data);
      p1 = p1->next;
    } else if (p2 && (!p1 || p2->data.degree > p1->data.degree)) {
      res.insert_ordered(p2->data);
      p2 = p2->next;
    } else {
      Monom combined(p1->data.coeff + p2->data.coeff, p1->data.degree);
      res.insert_ordered(combined);
      p1 = p1->next;
      p2 = p2->next;
    }
  }
  return res;
}

Polynomial Polynomial::operator*(double scalar) const {
  Polynomial res;
  if (std::abs(scalar) < 1e-10)
    return res;
  Node *curr = head->next;
  while (curr) {
    res.insert_ordered(Monom(curr->data.coeff * scalar, curr->data.degree));
    curr = curr->next;
  }
  return res;
}

Polynomial Polynomial::operator-(const Polynomial &other) const {
  return *this + (other * -1.0);
}

Polynomial Polynomial::operator*(const Polynomial &other) const {
  Polynomial res;
  for (Node *p1 = head->next; p1 != nullptr; p1 = p1->next) {
    for (Node *p2 = other.head->next; p2 != nullptr; p2 = p2->next) {
      int d1 = p1->data.degree;
      int d2 = p2->data.degree;
      int nx = (d1 / 100) + (d2 / 100);
      int ny = (d1 / 10 % 10) + (d2 / 10 % 10);
      int nz = (d1 % 10) + (d2 % 10);
      if (nx > 9 || ny > 9 || nz > 9)
        continue;
      res.insert_ordered(
          Monom(p1->data.coeff * p2->data.coeff, nx * 100 + ny * 10 + nz));
    }
  }
  return res;
}

void Polynomial::print() const {
  Node *curr = head->next;
  if (!curr) {
    std::cout << "0" << std::endl;
    return;
  }
  bool first = true;
  while (curr) {
    double c = curr->data.coeff;
    int d = curr->data.degree;
    if (!first && c > 0)
      std::cout << " + ";
    else if (c < 0)
      std::cout << " - ";
    double absCoeff = std::abs(c);
    if (absCoeff != 1.0 || d == 0)
      std::cout << absCoeff;
    if (d > 0) {
      int x = d / 100;
      int y = (d / 10) % 10;
      int z = d % 10;
      if (x > 0)
        std::cout << "x^" << x;
      if (y > 0)
        std::cout << "y^" << y;
      if (z > 0)
        std::cout << "z^" << z;
    }
    first = false;
    curr = curr->next;
  }
  std::cout << std::endl;
}

void inputPolynomial(Polynomial &p) {
  int count;
  std::cout << "Enter the number of monoms:";
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    double c;
    int x, y, z;
    std::cout << "Monom " << i + 1 << ": ";
    if (!(std::cin >> c >> x >> y >> z)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }
    try {
      p.add_monom(c, x, y, z);
    } catch (...) {
      i--;
    } // second try
  }
}
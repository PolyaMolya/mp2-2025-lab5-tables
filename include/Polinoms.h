#pragma once

struct Monomial {
  double coefficient;
  int power;
  Monomial *nextNode;

  Monomial();
  Monomial(double coef, int pwr, Monomial *next = nullptr);
};

class Polinom {
private:
  Monomial *dummyHead;

public:
  Polinom();
  Polinom(const Polinom &other);
  ~Polinom();

  void addMonom(double coef, int pwr);
  void print();

  Polinom operator+(const Polinom &other) const;
  Polinom operator-(const Polinom &other) const;
  Polinom operator*(const Polinom &other) const;
  Polinom operator*(double multiplier) const;
  Polinom operator=(const Polinom &other);
  bool operator==(const Polinom &other) const;
};
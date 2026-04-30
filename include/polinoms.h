#pragma once

struct Monom {
  double coeff;
  int degree;
  Monom *next;

  Monom();
  Monom(double c, int d, Monom *n = nullptr);
};

class Polinom {
 private:
  Monom *head;

 public:
  Polinom();

  Polinom(const Polinom &other);

  ~Polinom();

  void addMonom(double c, int d);

  void print();

  Polinom operator+(const Polinom &other) const;

  Polinom operator-(const Polinom &other) const;

  Polinom operator*(const Polinom &other) const;

  Polinom operator*(double value) const;

  Polinom operator=(const Polinom &other);

  bool operator==(const Polinom &other) const;
};

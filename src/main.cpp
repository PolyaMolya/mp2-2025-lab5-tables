#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "AVLTreeTable.h"
#include "ArrayTable.h"
#include "HashTable.h"
#include "polinoms.h"

void clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n');
}

int main() {
  Table* tables[3];
  tables[0] = new UnorderedArrayTable();
  tables[1] = new HashTable();
  tables[2] = new AVLTreeTable();

  std::string names[3] = {"Unordered Array", "Hash Table", "AVL Tree"};

  int choice = -1;
  while (true) {
    std::cout << "\n--- TABLE MANAGER ---\n";
    std::cout << "\n1. Add Polynomial\n";
    std::cout << "2. Find Polynomial\n";
    std::cout << "3. Calculate Expression\n";
    std::cout << "0. Exit\n";
    std::cout << "\nYour choice: ";

    if (!(std::cin >> choice)) {
      std::cout << "\nPlease enter a NUMBER!\n";
      clearInput();
      continue;
    }
    clearInput();  // Очищаем после выбора пункта

    if (choice == 0) break;

    if (choice == 1) {
      std::string key;
      std::cout << "\nEnter name (key): ";
      std::getline(std::cin, key);  // Читаем строку целиком

      Polinom p;
      int n;
      std::cout << "\nHow many monoms? ";
      while (!(std::cin >> n)) {
        std::cout << "\nEnter a number: ";
        clearInput();
      }
      clearInput();

      for (int i = 0; i < n; i++) {
        double c;
        int d;
        std::cout << "\nMonome " << i + 1 << " (coeff and degree): ";
        while (!(std::cin >> c >> d)) {
          std::cout << "\nInvalid. Enter coeff(double) and degree(int): " << "\n";
          clearInput();
        }
        clearInput();
        p.addMonom(c, d);
        std::cout << "\n";
      }

      for (int i = 0; i < 3; i++) {
        int ops = tables[i]->insert(key, p);
        std::cout << names[i] << ": " << ops << " operations\n";
      }
    } else if (choice == 2) {
      std::string key;
      std::cout << "\nEnter name to find: ";
      std::getline(std::cin, key);
      std::cout << "\n";

      for (int i = 0; i < 3; i++) {
        int ops = 0;
        Polinom* res = tables[i]->find(key, ops);
        std::cout << names[i] << ": " << ops << " operations";
        if (i == 0 && res) {
          std::cout << " (Found: ";
          res->print();
          std::cout << ")";
        }
        std::cout << "\n";
      }
    } else if (choice == 3) {
      int op;
      std::cout << "\nChoose operation: 1(+), 2(-), 3(*): ";
      while (!(std::cin >> op)) {
        std::cout << "\nEnter 1, 2 or 3: ";
        clearInput();
      }
      clearInput();

      std::string n1, n2, resName;
      std::cout << "\nEnter name of 1st polynomial: ";
      std::getline(std::cin, n1);
      std::cout << "\nEnter name of 2nd polynomial: ";
      std::getline(std::cin, n2);
      std::cout << "\nEnter name for the result: ";
      std::getline(std::cin, resName);

      int findOps = 0;
      Polinom* p1 = tables[1]->find(n1, findOps);
      Polinom* p2 = tables[1]->find(n2, findOps);

      if (p1 && p2) {
        Polinom res;
        if (op == 1)
          res = *p1 + *p2;
        else if (op == 2)
          res = *p1 - *p2;
        else if (op == 3)
          res = *p1 * *p2;

        std::cout << "\nResult: ";
        res.print();
        std::cout << "\n";
        for (int i = 0; i < 3; i++) tables[i]->insert(resName, res);
      } else {
        std::cout << "\nError: Polynomials not found!\n";
      }
    }
  }

  for (int i = 0; i < 3; i++) delete tables[i];
  return 0;
}
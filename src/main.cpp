#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "AVLTreeTable.h"
#include "SortedArrayTable.h"
#include "HashTable.h"
#include "polinoms.h"

void flushStream() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
  Table* storage[3];
  storage[0] = new SortedArrayTable();
  storage[1] = new AVLTreeTable();
  storage[2] = new HashTable();

  std::string structNames[3] = {"Сортированный массив", "АВЛ-дерево", "Хеш-таблица"};

  bool running = true;
  while (running) {
    std::cout << "\n=== Управления полиномами ===\n";
    std::cout << "1. Добавить новый полином\n";
    std::cout << "2. Найти полином\n";
    std::cout << "3. Вычислить выражение (+, -, *)\n";
    std::cout << "4. Выйти\n";
    std::cout << "Выберите действие: ";

    int action;
    if (!(std::cin >> action)) {
      flushStream();
      continue;
    }
    flushStream();

    switch (action) {
      case 1: {
        std::string polyName;
        std::cout << "Введите имя полинома: ";
        std::getline(std::cin, polyName);

        Polinom newPoly;
        int monomCount;
        std::cout << "Количество мономов для добавления: ";
        while (!(std::cin >> monomCount)) {
          flushStream();
        }
        flushStream();

        std::cout << "Подсказка: степень вводится как 3 цифры (xyz). Например, для 5x^2y^3z^0 пишите '5 230'\n";

        for (int i = 0; i < monomCount; ++i) {
          double coef;
          int deg;
          std::cout << "Моном " << i + 1 << " (формат: коэффициент степень): ";
          while (!(std::cin >> coef >> deg)) {
            flushStream();
          }
          flushStream();
          newPoly.addMonom(coef, deg);
        }

        std::cout << "\n[Аналитика добавления]\n";
        for (int i = 0; i < 3; ++i) {
          int iterCount = storage[i]->insert(polyName, newPoly);
          std::cout << structNames[i] << " заняло " << iterCount << " итераций.\n";
        }
        break;
      }
      case 2: {
        std::string searchKey;
        std::cout << "Введите имя полинома для поиска: ";
        std::getline(std::cin, searchKey);
        
        std::cout << "\n[Аналитика поиска]\n";
        for (int i = 0; i < 3; ++i) {
          int iterCount = 0;
          Polinom* found = storage[i]->find(searchKey, iterCount);
          std::cout << structNames[i] << " заняло " << iterCount << " итераций.";
          if (i == 0 && found) {
            std::cout << " Данные: ";
            found->print();
          } else if (i == 0) {
            std::cout << " Не найдено.";
          }
          std::cout << "\n";
        }
        break;
      }
      case 3: {
        std::string opStr;
        std::cout << "Введите оператор (+, -, *): ";
        std::getline(std::cin, opStr);

        std::string firstPoly, secondPoly, resultPoly;
        std::cout << "Имя первого операнда: ";
        std::getline(std::cin, firstPoly);
        std::cout << "Имя второго операнда: ";
        std::getline(std::cin, secondPoly);
        std::cout << "Сохранить результат как: ";
        std::getline(std::cin, resultPoly);

        int dummyOps = 0;
        Polinom* op1 = storage[2]->find(firstPoly, dummyOps);
        Polinom* op2 = storage[2]->find(secondPoly, dummyOps);

        if (op1 && op2) {
          Polinom calculated;
          if (opStr == "+") {
            calculated = *op1 + *op2;
          } else if (opStr == "-") {
            calculated = *op1 - *op2;
          } else if (opStr == "*") {
            calculated = *op1 * *op2;
          } else {
            std::cout << "\nНеверный оператор.\n";
            break;
          }

          std::cout << "\nВычисленный результат: ";
          calculated.print();
          std::cout << "\n";

          for (int i = 0; i < 3; ++i) {
            storage[i]->insert(resultPoly, calculated);
          }
        } else {
          std::cout << "\nОшибка: Один или оба полинома не найдены!\n";
        }
        break;
      }
      case 4: {
        running = false;
        break;
      }
    }
  }

  for (int i = 0; i < 3; ++i) {
    delete storage[i];
  }
  return 0;
}
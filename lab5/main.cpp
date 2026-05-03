#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "HashTable.h"
#include "Polynomial.h"
#include "RedBlackTree.h"
#include "SortedArray.h"

using namespace std;

HashTable tableHash(113);
RBTree tableTree;
SortedArrayTable tableArray;

// clear function for buufer
void clearInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Polynomial *findUniversal(const string &key) {
  size_t count = 0;
  Polynomial *res = nullptr;

  res = tableHash.find(key, count);
  if (res) {
    return res;
  }

  res = tableTree.find(key, count);
  if (res) {
    return res;
  }

  res = tableArray.get(key, count);
  if (res) {
    return res;
  }

  return nullptr;
}

void saveToStorage(const string &key, const Polynomial &p) {
  size_t countHash = 0;
  size_t countTree = 0;
  size_t countArray = 0;

  tableHash.insert(key, p, countHash);
  tableTree.insert(key, p, countTree);
  tableArray.insert(key, p, countArray);

  cout << "\nPolynomial saved to all structures:" << endl;
  cout << "- Hash Table (ops: " << countHash << ")" << endl;
  cout << "- Red-Black Tree (ops: " << countTree << ")" << endl;
  cout << "- Sorted Array (ops: " << countArray << ")" << endl;
}

void printMenu() {
  cout << "1. Create new polynomial\n";
  cout << "2. Show polynomial\n";
  cout << "3. Add polynomials\n";
  cout << "4. Subtract polynomials\n";
  cout << "5. Multiply by scalar\n";
  cout << "6. Multiply polynomials\n";
  cout << "7. Remove polynomial\n";
  cout << "0. Exit\n";
  cout << "----------------------------------------\n";
  cout << "Select action: ";
}

int main() {
  int choice;
  string key1, key2, resKey;
  size_t Count;

  while (true) {
    printMenu();
    if (!(cin >> choice)) {
      clearInput();
      continue;
    }

    if (choice == 0)
      break;

    switch (choice) {
    case 1: {
      cout << "Enter a key: ";
      cin >> key1;
      Polynomial p;
      inputPolynomial(p);
      saveToStorage(key1, p);
      break;
    }

    case 2: {
      cout << "Enter the polynomial name:  ";
      cin >> key1;
      Polynomial *p = findUniversal(key1);
      if (p) {
        cout << "Value " << key1 << ": ";
        p->print();
      } else
        cout << "The polynomial was not found.\n";
      break;
    }

    case 3:
    case 4:
    case 6: {
      cout << "Enter the name of the 1st polynomial: ";
      cin >> key1;
      cout << "Enter the name of the 2nd polynomial: ";
      cin >> key2;
      Polynomial *p1 = findUniversal(key1);
      Polynomial *p2 = findUniversal(key2);

      if (!p1 || !p2) {
        cout << "One of the polynomials was not found.\n";
        break;
      }

      Polynomial result;
      if (choice == 3)
        result = (*p1) + (*p2);
      else if (choice == 4)
        result = (*p1) - (*p2);
      else
        result = (*p1) * (*p2);

      cout << "Result: ";
      result.print();
      cout << "Enter a name to save the result:";
      cin >> resKey;
      saveToStorage(resKey, result);
      break;
    }

    case 5: {
      cout << "Enter the polynomial name: ";
      cin >> key1;
      double k;
      cout << "Enter a scalar: ";
      cin >> k;
      Polynomial *p = findUniversal(key1);
      if (p) {
        Polynomial result = (*p) * k;
        cout << "Result: ";
        result.print();
        cout << "Enter a name to save: ";
        cin >> resKey;
        saveToStorage(resKey, result);
      } else
        cout << "One of the polynomials was not found.\n";
      break;
    }

    case 7: {
      cout << "Enter the polynomial name: ";
      cin >> key1;
      size_t c = 0;

      bool h = tableHash.remove(key1, c);
      // no remove for RBTree because you sad that its not necessary
      bool a = tableArray.remove(key1, c);

      if (h || a)
        cout << "Polynomial removed from all structures.(not removed due to abscence of function remove in RBTree)\n";
      else
        cout << "The polynomial was not found\n";
      break;
    }

    default:
      cout << "Incorrect input\n";
    }
  }

  return 0;
}
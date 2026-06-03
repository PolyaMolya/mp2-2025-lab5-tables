#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <limits>
#include "unsorted_table.h"
#include "rbtree_table.h"
#include "hash_table.h"
#include "logger.h"
#include "polinom.h"
#include "arithmetic.h"

using namespace std;

void printMenu() {
    cout << "\n========== ЛР5 ТАБЛИЦЫ ПОЛИНОМОВ ==========\n";
    cout << "1. Добавить полином в таблицы (по имени)\n";
    cout << "2. Найти полином по имени\n";
    cout << "3. Удалить полином\n";
    cout << "4. Показать содержимое всех таблиц\n";
    cout << "5. Вычислить выражение и сохранить результат\n";
    cout << "6. Показать все ключи в таблицах\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

void showTableContents(const vector<ITable<string, Polinom>*>& tables) {
    for (auto* table : tables) {
        cout << "\n--- " << table->name() << " ---\n";
        auto keys = table->keys();
        if (keys.empty()) {
            cout << "(пусто)\n";
        }
        else {
            for (const auto& key : keys) {
                Polinom p;
                if (table->find(key, p)) {
                    cout << key << " = " << p << endl;
                }
            }
        }
        cout << "Всего элементов: " << table->size() << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Russian"); 

    // Три типа таблиц: неупорядоченный массив, красно-черное дерево, хеш-таблица
    UnsortedArrayTable<string, Polinom> unsorted;
    RBTreeTable<string, Polinom> rbtree;
    HashTable<string, Polinom> hashTable;

    vector<ITable<string, Polinom>*> tables = { &unsorted, &rbtree, &hashTable };

    ArithmeticCalculator calc;
    calc.setVariable("x", 1.0);
    calc.setVariable("y", 1.0);
    calc.setVariable("z", 1.0);

    int choice;
    do {
        printMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            string name, polyStr;
            cout << "Имя полинома: ";
            getline(cin, name);
            cout << "Введите полином: ";
            getline(cin, polyStr);
            try {
                Polinom p = Polinom::parseFromString(polyStr);
                for (auto* table : tables) {
                    OperationLogger::logInsertWithValue(*table, name, p);
                }
                cout << "Полином добавлен во все таблицы.\n";
            }
            catch (const exception& e) {
                cout << "Ошибка парсинга: " << e.what() << endl;
            }
            break;
        }
        case 2: {
            string name;
            cout << "Имя полинома для поиска: ";
            getline(cin, name);
            for (auto* table : tables) {
                OperationLogger::logFind(*table, name);
                Polinom p;
                if (table->find(name, p)) {
                    cout << "  Значение: " << p << endl;
                }
            }
            break;
        }
        case 3: {
            string name;
            cout << "Имя полинома для удаления: ";
            getline(cin, name);
            for (auto* table : tables) {
                OperationLogger::logRemove(*table, name);
            }
            break;
        }
        case 4: {
            showTableContents(tables);
            break;
        }
        case 5: {
            string expr, resultName;
            cout << "Арифметическое выражение (с x,y,z, pi, e, sin, cos и т.д.): ";
            getline(cin, expr);
            cout << "Сохранить результат под именем: ";
            getline(cin, resultName);
            try {
                double val = calc.calculate(expr);
                string constStr = to_string(val);
                Polinom constPoly = Polinom::parseFromString(constStr);
                for (auto* table : tables) {
                    OperationLogger::logInsertWithValue(*table, resultName, constPoly);
                }
                cout << "Результат " << val << " сохранён как полином-константа.\n";
            }
            catch (const exception& e) {
                cout << "Ошибка вычисления: " << e.what() << endl;
            }
            break;
        }
        case 6: {
            for (auto* table : tables) {
                cout << "\n--- " << table->name() << " ключи ---\n";
                auto keys = table->keys();
                for (const auto& k : keys) {
                    cout << "  " << k << endl;
                }
            }
            break;
        }
        case 0:
            cout << "До свидания!\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
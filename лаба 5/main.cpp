#include <iostream>
#include <string>
#include <limits>
#include "polinom.h"
#include "table_array.h"
#include "AVL.h"
#include "Hash.h"

using namespace std;

// --------------------------------------------------------------
// Input polynomial from keyboard
Polinom inputPolynomial() {
    int n;
    cout << "Enter number of monomials: ";
    cin >> n;
    Polinom res;
    for (int i = 0; i < n; ++i) {
        double coef;
        int x, y, z;
        cout << "Monom " << i + 1 << " (coeff, deg_x, deg_y, deg_z): ";
        cin >> coef >> x >> y >> z;
        if (x < 0 || y < 0 || z < 0 || x > 9 || y > 9 || z > 9) {
            cout << "Error: degrees must be 0..9. Monom skipped.\n";
            continue;
        }
        int deg = x * 100 + y * 10 + z;
        Monom m(deg, coef);
        res.insertPol(m);
    }
    res.removeZero();
    return res;
}

// --------------------------------------------------------------
// Logging for insertion
void logInsert(const string& key, int arrOps, int avlOps, int hashOps) {
    cout << "\n=== INSERT polynomial with key '" << key << "' ===\n";
    cout << "  Unsorted array: " << arrOps << " operation(s)\n";
    cout << "  AVL tree: " << avlOps << " comparisons\n";
    cout << "  Hash table: " << hashOps << " comparisons\n";
}

// Logging for search
void logFind(const string& key, bool found, int arrComp, int avlComp, int hashComp) {
    cout << "\n=== SEARCH polynomial with key '" << key << "' ===\n";
    cout << "  Result: " << (found ? "FOUND" : "NOT FOUND") << "\n";
    cout << "  Unsorted array: " << arrComp << " comparisons\n";
    cout << "  AVL tree: " << avlComp << " comparisons\n";
    cout << "  Hash table: " << hashComp << " comparisons\n";
}

// Logging for removal
void logRemove(const string& key, bool removed, int arrOps, int avlOps, int hashOps) {
    cout << "\n=== REMOVE polynomial with key '" << key << "' ===\n";
    cout << "  Result: " << (removed ? "REMOVED" : "NOT FOUND") << "\n";
    cout << "  Unsorted array: " << arrOps << " operations (comparisons+shifts)\n";
    cout << "  AVL tree: " << avlOps << " comparisons\n";
    cout << "  Hash table: " << hashOps << " comparisons\n";
}

// Helper to search in all tables and log
void searchAndLog(const string& key, UnsortTable& arr, AVL& avl, Hash& hash) {
    int arrComp = 0, avlComp = 0, hashComp = 0;
    const Polinom* pArr = arr.find(key, arrComp);
    const Polinom* pAvl = avl.find(key, avlComp);
    const Polinom* pHash = hash.find(key, hashComp);
    bool found = (pArr != nullptr);
    logFind(key, found, arrComp, avlComp, hashComp);
}

// --------------------------------------------------------------
int main() {
    UnsortTable arrTable;
    AVL avlTable;
    Hash hashTable;

    int choice;
    string key, key1, key2, op, resultKey;
    Polinom poly, resPoly, removedPoly;

    while (true) {
        cout << "\n===================================================\n";
        cout << "   LAB WORK #5 – TABLES WITH POLYNOMIALS\n";
        cout << "===================================================\n";
        cout << "1. Add polynomial to all tables\n";
        cout << "2. Find polynomial by key (in all tables)\n";
        cout << "3. Remove polynomial by key (from all tables)\n";
        cout << "4. Arithmetic operation (key1 +-* key2)\n";
        cout << "5. Show content of all tables\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1: {
            cout << "Enter key (name): ";
            cin >> key;
            cout << "Enter polynomial:\n";
            poly = inputPolynomial();

            int arrOps = arrTable.insert(key, poly);
            int avlOps = avlTable.insert(key, poly);
            int hashOps = hashTable.insert(key, poly);

            logInsert(key, arrOps, avlOps, hashOps);
            break;
        }

        case 2: {
            cout << "Enter key to search: ";
            cin >> key;
            int arrComp = 0, avlComp = 0, hashComp = 0;
            const Polinom* pArr = arrTable.find(key, arrComp);
            const Polinom* pAvl = avlTable.find(key, avlComp);
            const Polinom* pHash = hashTable.find(key, hashComp);
            bool found = (pArr != nullptr);
            if (found) {
                cout << "\nPolynomial found (from array): ";
                pArr->print();
                cout << endl;
            }
            logFind(key, found, arrComp, avlComp, hashComp);
            break;
        }

        case 3: {
            cout << "Enter key to remove: ";
            cin >> key;
            int arrOps = 0, avlOps = 0, hashOps = 0;
            Polinom removedArr, removedAvl, removedHash;
            bool okArr = arrTable.remove(key, removedArr, arrOps);
            bool okAvl = avlTable.remove(key, removedAvl, avlOps);
            bool okHash = hashTable.remove(key, removedHash, hashOps);
            bool removed = okArr; // all three should be consistent
            if (removed) {
                cout << "\nRemoved polynomial (from array): ";
                removedArr.print();
                cout << endl;
            }
            logRemove(key, removed, arrOps, avlOps, hashOps);
            break;
        }

        case 4: {
            cout << "Enter expression in format: key1 + key2   (or -, *)\n";
            cin >> key1 >> op >> key2;

            // Search operands in all tables with logging
            cout << "\n--- Searching first operand '" << key1 << "' ---\n";
            searchAndLog(key1, arrTable, avlTable, hashTable);
            cout << "\n--- Searching second operand '" << key2 << "' ---\n";
            searchAndLog(key2, arrTable, avlTable, hashTable);

            // Get polynomials from array (any table) for operation
            int tmp;
            const Polinom* p1 = arrTable.find(key1, tmp);
            const Polinom* p2 = arrTable.find(key2, tmp);
            if (!p1 || !p2) {
                cout << "Error: one or both polynomials not found in tables!\n";
                break;
            }

            // Compute result
            try {
                if (op == "+") {
                    resPoly = p1->add(*p2);
                }
                else if (op == "-") {
                    resPoly = p1->subtract(*p2);
                }
                else if (op == "*") {
                    resPoly = p1->mul(*p2);
                }
                else {
                    cout << "Unknown operation. Use +, -, *\n";
                    break;
                }
            }
            catch (const exception& e) {
                cout << "Error during computation: " << e.what() << endl;
                break;
            }

            cout << "\nResult: ";
            resPoly.print();
            cout << endl;

            cout << "Save result to tables? Enter key (or 0 to skip): ";
            cin >> resultKey;
            if (resultKey != "0") {
                int arrOps = arrTable.insert(resultKey, resPoly);
                int avlOps = avlTable.insert(resultKey, resPoly);
                int hashOps = hashTable.insert(resultKey, resPoly);
                logInsert(resultKey, arrOps, avlOps, hashOps);
            }
            break;
        }

        case 5: {
            cout << "\n--- Content of all tables ---\n";
            arrTable.print();
            avlTable.print();
            hashTable.print();
            break;
        }

        default:
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } // switch
    } // while

    return 0;
}
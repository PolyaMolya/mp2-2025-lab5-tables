#include  <math.h>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Tables.h"


//int main() {
//    Polinom ans;
//    Polinom polinom;
//    Polinom polinom2;
//    while (true) {
//        std::string input;
//        std::vector<char> toEnter;
//        int choice;
//        std::cout << "1. Enter a polinom" << std::endl;
//        std::cout << "2. Convert to postfix form" << std::endl;
//        std::cout << "3. Enter variable values" << std::endl;
//        std::cout << "4. Evaluate the expression" << std::endl;
//        std::cout << "Select action: ";
//        system("cls");
//        double valInp;
//        std::string nameInp;
//                while (input != "0") {
//                    std::cout << "Enter monom in format: coefficent degree(where 100 is degree x, 10 degeree y, 1 degree z)         '0' for exit " << std::endl;
//                    std::getline(std::cin, input);
//                    if (input.empty()) {
//                        continue;
//                    }
//                    if (input == "0") {
//                        break;
//                    }
//                    try {
//                        std::istringstream iss(input);
//                        double coefficient;
//                        int degree;
//                        std::string trash;
//                        if (iss >> coefficient >> degree) {
//                            Monom* m = new Monom(coefficient, degree);
//                            polinom.ptr_add_new_monom(m);
//                         
//                        }
//                        else {
//                            std::cout << "Error: Invalid input format" << std::endl;
//                            std::cout << "Try again" << std::endl;
//                        }
//                        if (iss >> trash) {
//                            std::cout << "only two first numbers would be used" << std::endl;
//                        }
//                        polinom.print();
//                        std::cout << std::endl;
//                    }
//                    catch (const std::string& error) {
//                        std::cout << "Error: " << error << std::endl;
//                        std::cout << "Try again" << std::endl;
//                    }
//                }
//                std::cout << "Polinom successfully installed : ";
//                polinom.print();
//                std::cout << std::endl;
//                std::cout << "enter operation(+, -, *)" << std::endl;
//                std::string operation1;
//                std::getline(std::cin, operation1);
//                std::istringstream iss(operation1);
//                std::string firstWord;
//                char operation = ' ';
//                if (iss >> firstWord) {
//                    
//                    operation = firstWord[0];
//                    if (operation == '+' || operation == '-' || operation == '*')
//                        std::cout << "Operation successfully installed: " << operation << std::endl;
//                    else std::cout << "Anknown operation";
//                }
//                else {
//                    std::cout << "Error: Invalid operation format" << std::endl;
//                }
//                input.clear();
//                std::cout << "Enter enother polinom" << std::endl;
//                while (input != "0") {
//                    std::cout << "Enter monom in format: coefficent degree(where 100 is degree x, 10 degeree y, 1 degree z)         '0' for exit " << std::endl;
//                    std::getline(std::cin, input);
//                    if (input.empty()) {
//                        continue;
//                    }
//                    if (input == "0") {
//                        break;
//                    }
//                    try {
//                        std::istringstream iss(input);
//                        double coefficient;
//                        int degree;
//
//                        if (iss >> coefficient >> degree) {
//                            Monom* m = new Monom(coefficient, degree);
//                            polinom2.ptr_add_new_monom(m);
//
//                        }
//                        else {
//                            std::cout << "Error: Invalid input format" << std::endl;
//                        }
//                        polinom2.print();
//                        std::cout << std::endl;
//                    }
//                    catch (const std::string& error) {
//                        std::cout << "Error: " << error << std::endl;
//                    }
//                }
//                std::cout << "Polinom successfully installed : ";
//                polinom.print();
//                std::cout << std::endl;
//                switch (operation) {
//                    case '+':
//                        ans = polinom + polinom2;
//                        std::cout << "Answer: ";
//                        ans.print();
//                        break;
//                    case '-':
//                         ans = polinom - polinom2;
//                         std::cout << "Answer: ";
//                         ans.print();
//                         break;
//                    case '*':
//                        ans = polinom * polinom2;
//                        std::cout << "Answer: ";
//                        ans.print();
//                        break;
//                }
//                break;
//    }
//                
//
//        
//    
//    return 0;
//}
int main() {
    //Table_Tree<int> table;
    //Monom b(123, 123);
    //Monom c(321, 123);

    //Monom f(2, 111);
    //Polinom B,C,F;
    //B.add_new_monom(b);
    //C.add_new_monom(c);
    //F.add_new_monom(f);
    //table.Insert(5, C);
    //table.Insert(2, C);
    //table.Insert(8, B);
    //table.Insert(2, F);


    //table.print(); 
    //std::cout << std::endl;
    //std::cout << std::endl;
    //std::cout << std::endl;
    //
    //table.find_by_key(2);

        Monom b(777, 777);
        Monom c(321, 123);
        Polinom B,C;
        B.add_new_monom(b);
        C.add_new_monom(c);
        Table_Tree<int> table_tree;
        Table_array<int> table_array;              
        Hash_Table<int> table_hash;
        table_array.add_data_and_key(C, 2);
        table_hash.insert(2, C);
        table_tree.insert(2, C);
        table_array.add_data_and_key(B, 3);
        table_hash.insert(3, B);
        table_tree.insert(3, B);
        while (true) {
            Polinom polinom;
            std::string input;
            std::vector<char> toEnter;
            int choice;
            table_tree.print();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "1. Enter a new expression to table" << std::endl;
            std::cout << "2. Select Polinoms for action" << std::endl;
            std::cout << "Select action: ";
            std::cin >> choice;
            system("cls");
            double valInp;
            std::string nameInp;
            switch (choice) {
            case 1:
                while (input != "0") {
                    std::cout << "Enter monom in format: coefficent degree(where 100 is degree x, 10 degeree y, 1 degree z)         '0' for exit " << std::endl;
                    std::getline(std::cin, input);
                    if (input.empty()) {
                        continue;
                    }
                    if (input == "0") {
                        break;
                    }
                    try {
                        std::istringstream iss(input);
                        double coefficient;
                        int degree;
                        std::string trash;
                        if (iss >> coefficient >> degree) {
                            Monom* m = new Monom(coefficient, degree);
                            polinom.ptr_add_new_monom(m);
                        }
                        else {
                            std::cout << "Error: Invalid input format" << std::endl;
                            std::cout << "Try again" << std::endl;
                        }
                        if (iss >> trash) {
                            std::cout << "only two first numbers would be used" << std::endl;
                        }
                        polinom.print();
                        std::cout << std::endl;
                    }
                    catch (const std::string& error) {
                        std::cout << "Error: " << error << std::endl;
                        std::cout << "Try again" << std::endl;
                    }
                }
                polinom.print();
                std::cout << "For adding your polinom in tables print Key: ";
                std::getline(std::cin, input);
                if (input.empty()) {
                    continue;
                }
                try {
                    std::istringstream iss(input);
                    int key;
                    if (iss >> key) {
                        table_array.add_data_and_key(polinom, key);
                        table_tree.insert(key, polinom);
                        table_hash.insert(key, polinom);
                    }
                    else {
                        std::cout << "Error: Invalid input format" << std::endl;
                    }
                }
                catch (const std::string& error) {
                    std::cout << "Error: " << error << std::endl;
                    std::cout << "Try again" << std::endl;
                }
                std::cout << std::endl;
                system("cls");
                break;
            case 2: {
                std::cin.ignore();
                system("cls");
                bool chosen = false;
                Polinom SecondUserPol;
                Polinom FirstUserPol;
                Polinom ans;
                bool valid = false;
                while (!valid) {
                    std::cout << "Enter key of your first Polinom" << std::endl;
                    std::getline(std::cin, input);
                    if (input.empty()) {
                        continue;
                    }
                    try {
                        int key;
                        std::istringstream iss(input);
                        if (iss >> key) {
                            FirstUserPol = table_array.find_by_key(key);
                            FirstUserPol = table_hash.search(key);
                            FirstUserPol = table_tree.find_by_key(key);
                            valid = true;

                        }
                    }

                    catch (const std::string& error) {
                        std::cout << "Error: " << error << std::endl;
                        std::cout << "Try again" << std::endl;
                    }

                }
                valid = false;
                while (!valid) {
                    std::cout << "Enter key of your second Polinom" << std::endl;
                    std::getline(std::cin, input);
                    if (input.empty()) {
                        continue;
                    }
                    try {

                        int key;
                        std::istringstream iss(input);
                        if (iss >> key) {
                            SecondUserPol = table_array.find_by_key(key);
                            SecondUserPol = table_hash.search(key);
                            SecondUserPol = table_tree.find_by_key(key);
                            valid = true;

                        }
                    }

                    catch (const std::string& error) {
                        std::cout << "Error: " << error << std::endl;
                        std::cout << "Try again" << std::endl;
                    }
                }
                try {
                    bool valid = false;
                    char action = ' ';
                    while (!valid) {
                        std::cout << "Enter operation (+, -, *): ";
                        std::cin >> action;

                        if (action == '+' || action == '-' || action == '*') {
                            switch (action) {
                            case '+':
                                ans = FirstUserPol + SecondUserPol;
                                break;
                            case '-':
                                ans = FirstUserPol - SecondUserPol;
                                break;
                            case '*':
                                ans = FirstUserPol * SecondUserPol;
                                break;
                            }
                            std::cout << "Answer: ";
                            ans.print();
                            valid = true;
                        }
                        else {
                            std::cout << "Unknown operation. Try again: ";
                        }
                    }
                }
                catch (const std::string& error) {
                    std::cout << "Error: " << error << std::endl;
                    std::cout << "Try again" << std::endl;
                }
                std::cout << std::endl;
                std::cout << "For adding your polinom in tables print Key: ";
                std::cin.ignore();
                input = "";
                std::getline(std::cin, input);
                if (input.empty()) {
                    continue;
                }
                try {
                    std::istringstream iss(input);
                    int key;
                    if (iss >> key) {
                        table_array.add_data_and_key(ans, key);
                        table_tree.insert(key, ans);
                        table_hash.insert(key, ans);
                    }
                    else {
                        std::cout << "Error: Invalid input format" << std::endl;
                    }
                }
                catch (const std::string& error) {
                    std::cout << "Error: " << error << std::endl;
                    std::cout << "Try again" << std::endl;
                }
                std::cout << std::endl;
                chosen = true;


                system("cls");
                break;
                }
            }

        }
        return 0;
}
#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <optional>
#pragma once
struct Monom {
    double coefficient;
    int degrees;
    Monom* next;
public:
    Monom() :coefficient(0), degrees(0) { next = nullptr; }
    Monom(const double _coefficient, const int _degrees) {
        if (_degrees > 999) throw std::string("degrees cant be more than 999");
        if (_degrees < 0) throw std::string("Degrees cannot be negative");
        if (std::isnan(_coefficient) || std::isinf(_coefficient)) throw std::string("Degrees cannot be null or inf");
        coefficient = _coefficient;
        degrees = _degrees;
    }
};
class Polinom {
    Monom* head;
    int count;
public:
    Polinom() : head(nullptr), count(0) {}
    Polinom(const Monom& m) {
        head = new Monom(m.coefficient, m.degrees);
        count = 1;
    }
    ~Polinom() {
        while (head != nullptr) {
            Monom* temp = head;
            head = head->next;
            delete temp;
        }
    }
    bool NotEmpty() {
        Monom* current = head;
        return current != nullptr ? true : false;
    }
    void ptr_add_new_monom(Monom* m) {
        if (m == nullptr) throw std::string("Cannot add null monom pointer");
        if (head == nullptr) {
            head = m;
            head->next = nullptr;
            count = 1;
            return;
        }

        if (m->degrees > head->degrees) {
            m->next = head;
            head = m;
            count++;
            return;
        }

        if (m->degrees == head->degrees) {
            head->coefficient = head->coefficient + m->coefficient;
            delete m;
            if (std::abs(head->coefficient) < 1e-10) {
                Monom* temp = head;
                head = head->next;
                delete temp;
                count--;
            }
            return;
        }

        Monom* current = head;
        while (current->next != nullptr && current->next->degrees > m->degrees) {
            current = current->next;
        }

        if (current->next != nullptr && current->next->degrees == m->degrees) {
            current->next->coefficient += m->coefficient;
            delete m;
            if (std::abs(current->next->coefficient) < 1e-10) {
                Monom* temp = current->next;
                current->next = current->next->next;
                delete temp;
                count--;
            }
        }
        else {
            m->next = current->next;
            current->next = m;
            count++;
        }
    }
    void add_new_monom(const Monom& m) {
        if (head == nullptr) {
            head = new Monom(m.coefficient, m.degrees);
            head->next = nullptr;
            count = 1;
            return;
        }

        if (m.degrees > head->degrees) {
            Monom* newMonom = new Monom(m.coefficient, m.degrees);
            newMonom->next = head;
            head = newMonom;
            count++;
            return;
        }

        if (m.degrees == head->degrees) {
            head->coefficient += m.coefficient;
            if (std::abs(head->coefficient) < 1e-10) {
                Monom* temp = head;
                head = head->next;
                delete temp;
            }
            return;
        }
        Monom* current = head;
        while (current->next != nullptr && current->next->degrees > m.degrees) {
            current = current->next;
        }
        if (current->next != nullptr && current->next->degrees == m.degrees) {
            current->next->coefficient += m.coefficient;
            if (std::abs(current->next->coefficient) < 1e-10) {
                Monom* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
        else {
            Monom* newMonom = new Monom(m.coefficient, m.degrees);
            newMonom->next = current->next;
            current->next = newMonom;
            count++;
        }
    }
    void print() {
        if (head == nullptr) {
            std::cout << "Polynom is empty" << std::endl;
            return;
        }
        Monom* current = head;
        while (current != nullptr) {

            std::cout << current->coefficient
                << "x^" << current->degrees / 100 << " "
                << "y^" << (current->degrees / 10) % 10 << " "
                << "z^" << current->degrees % 10;

            current = current->next;
            if (current != nullptr) {
                std::cout << " + ";
            }
        }
        std::cout << std::endl;
    }
    Polinom(const Polinom& other) : head(nullptr), count(0) {
        if (other.head) {
            Monom* currentOther = other.head;
            Monom* last = nullptr;

            while (currentOther) {
                Monom* newNode = new Monom(currentOther->coefficient, currentOther->degrees);
                newNode->next = nullptr;

                if (!head) {
                    head = newNode;
                }
                else {
                    last->next = newNode;
                }
                last = newNode;

                currentOther = currentOther->next;
                count++;
            }
        }
    }

    Polinom& operator=(const Polinom& other) {
        if (this != &other) {
            while (head) {
                Monom* temp = head;
                head = head->next;
                delete temp;
            }
            count = 0;

            if (other.head) {
                Monom* currentOther = other.head;
                Monom* last = nullptr;

                while (currentOther) {
                    Monom* newNode = new Monom(currentOther->coefficient, currentOther->degrees);
                    newNode->next = nullptr;

                    if (!head) {
                        head = newNode;
                    }
                    else {
                        last->next = newNode;
                    }
                    last = newNode;

                    currentOther = currentOther->next;
                    count++;
                }
            }
        }
        return *this;
    }
    Polinom operator + (const Polinom& pol) {
        if (this->head == nullptr || pol.head == nullptr)
            throw std::string("Cannot add empty polynomials");
        Polinom ans;
        Monom* current1 = head;
        Monom* current2 = pol.head;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->degrees > current2->degrees) {
                Monom* to_add = new Monom(current1->coefficient, current1->degrees);
                ans.ptr_add_new_monom(to_add);
                current1 = current1->next;
            }
            else if (current1->degrees < current2->degrees) {
                Monom* to_add = new Monom(current2->coefficient, current2->degrees);
                ans.ptr_add_new_monom(to_add);
                current2 = current2->next;
            }
            else {
                if (std::abs(current1->coefficient + current2->coefficient) >= 1e-10) {
                    Monom* to_add = new Monom(current1->coefficient + current2->coefficient, current1->degrees);
                    ans.ptr_add_new_monom(to_add);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        while (current1 != nullptr) {
            Monom* to_add = new Monom(current1->coefficient, current1->degrees);
            ans.ptr_add_new_monom(to_add);
            current1 = current1->next;
        }
        while (current2 != nullptr) {
            Monom* to_add = new Monom(current2->coefficient, current2->degrees);
            ans.ptr_add_new_monom(to_add);
            current2 = current2->next;
        }

        return ans;
    }
    Polinom  operator - (const Polinom& pol) {
        if (this->head == nullptr || pol.head == nullptr)
            throw std::string("Cannot minus empty polynomials");
        Polinom polRevers;
        Monom* current = pol.head;
        while (current != nullptr) {
            Monom* to_add = new Monom(-1 * current->coefficient, current->degrees);
            polRevers.ptr_add_new_monom(to_add);
            current = current->next;
        }
        Polinom ans;
        Monom* current1 = head;
        Monom* current2 = polRevers.head;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->degrees > current2->degrees) {
                Monom* to_add = new Monom(current1->coefficient, current1->degrees);
                ans.ptr_add_new_monom(to_add);
                current1 = current1->next;
            }
            else if (current1->degrees < current2->degrees) {
                Monom* to_add = new Monom(current2->coefficient, current2->degrees);
                ans.ptr_add_new_monom(to_add);
                current2 = current2->next;
            }
            else {
                if (std::abs(current1->coefficient + current2->coefficient) >= 1e-10) {
                    Monom* to_add = new Monom(current1->coefficient + current2->coefficient, current1->degrees);
                    ans.ptr_add_new_monom(to_add);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        while (current1 != nullptr) {
            Monom* to_add = new Monom(current1->coefficient, current1->degrees);
            ans.ptr_add_new_monom(to_add);
            current1 = current1->next;
        }
        while (current2 != nullptr) {
            Monom* to_add = new Monom(current2->coefficient, current2->degrees);
            ans.ptr_add_new_monom(to_add);
            current2 = current2->next;
        }

        return ans;
    }
    Polinom operator * (const Polinom& pol) {
        if (this->head == nullptr || pol.head == nullptr)
            throw std::string("Cannot multiply empty polynomials");
        Polinom ans;
        Monom* current1 = head;
        Monom* current2 = pol.head;
        while (current1 != nullptr) {
            while (current2 != nullptr) {
                Polinom dop;
                if (current1->degrees + current2->degrees > 999) {
                    throw std::string("degrees more than 10 (");
                }
                Monom* to_add = new Monom(current1->coefficient * current2->coefficient, current1->degrees + current2->degrees);
                ans.ptr_add_new_monom(to_add);
                current2 = current2->next;
            }
            current1 = current1->next;
            current2 = pol.head;
        }
        return ans;
    }

};
enum class Color { RED, BLACK };
template <typename T>
struct Row {
    T key;
    Polinom data;
    bool is_free;
    Row() : key(0), data(), is_free(true) {}
};
template <typename T>
class Hash_Table {
private:
    Row<T>* table;
    size_t count;
    size_t size;
public:
    Hash_Table(int _size = 101) {
        size = _size;
        table = new Row<T>[size];
    }
    ~Hash_Table() {
        delete[] table;
    }
    size_t hash_function (T key) {
        return static_cast<size_t>(key) % size;
    }
    size_t probe(size_t hash_value, size_t i) const {
        return (hash_value + i * i) % size;
    }
    bool insert(T key, const Polinom& data) {
        size_t oper = 0;
        if (count >= size) {
            return false;
        }
        size_t hash = hash_function(key);
        for (size_t i = 0; i < size; ++i) {
            size_t ind = probe(hash, i);
            Row<T>& row = table[ind];
            oper++;
            if (row.is_free == true) {
                row.key = key;
                row.data = data;
                row.is_free = false;
                ++count;
                std::cout << "[Hash Table] Insert need operations: " << oper << std::endl;
                return true;
            }
            else if (row.is_free == false && row.key == key) {
                row.data = data;
                return true;
            }
        }
        return false;
    }

    Polinom search(T key) {
        size_t oper = 0;
        size_t hash = hash_function(key);
        for (size_t i = 0; i < size; ++i) {
            size_t ind = probe(hash, i);
            const Row<T> row = table[ind];
            if (row.is_free) {
                break;
            }
            if (!row.is_free && row.key == key) {
                std::cout << "[Hash Table] Search need operations: " << oper << std::endl;
                return row.data;
            }
        }
        throw std::string("Key not found");
    }
   
};


template<typename K>
struct Node {
    K key;              
    Polinom data;            
    Color color;        
    Node* left;        
    Node* right;        
    Node* parent;       

    Node(K k, Polinom v): key(k), data(v), color(Color::RED),left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename K>
class Table_Tree {
private:
    Node<K>* root;
    size_t size_;

    void rotateLeft(Node<K>* x) {
        Node<K>* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node<K>* x) {
        Node<K>* y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node<K>* z) {
        while (z->parent != nullptr && z->parent->color == Color::RED) {
            if (z->parent == z->parent->parent->left) {
                Node<K>* ancle = z->parent->parent->right;

                if (ancle != nullptr && ancle->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    ancle->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateRight(z->parent->parent);
                }
            }
            else {
                Node<K>* y = z->parent->parent->left;

                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }


    void clearTree(Node<K>* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    Table_Tree() : root(nullptr), size_(0) {}

    ~Table_Tree() {
        clearTree(root);
    }

    void insert(const K& key, const Polinom& data) {
        size_t oper = 0;
        Node<K>* z = new Node<K>(key, data);
        Node<K>* y = nullptr;
        Node<K>* x = root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                oper++;
                x = x->left;
            }
            else if (x->key < z->key) {
                oper++;
                x = x->right;
            }
            else {
                oper += 2;
                x->data = data;
                delete z;
                return;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            oper++;
            root = z;
        }
        else if (z->key < y->key) {
            oper++;
            y->left = z;
        }
        else {
            oper++;
            y->right = z;
        }

        size_++;
        fixInsert(z);
        std::cout << "[RB-Tree] Insert need operations: " << oper << std::endl;
    }


   

    Polinom find_by_key(const K key) {
        size_t oper = 0;
        Node<K>* current = root;
        if (root == nullptr) {
            throw std::string("Tree is clear");
        }
        else {
            while (current != nullptr && current->key != key) {
                if (key > current->key) {
                    oper++;
                    current = current->right;
                }
                else if (key < current->key) {
                    oper++;
                    current = current->left;
                }
            }

            if (current == nullptr) {
                throw std::string("Key not found");
            }
        }
        std::cout << "[RB-Tree] Find need operations: " << oper << std::endl;
        return current->data;
    }


    void printNode(Node<K>* node) const {
        if (node == nullptr) return;

        printNode(node->left);
        std::cout << node->key << " -> ";
        node->data.print();
        printNode(node->right);
    }

    void print() const {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << 
            "TABLE: " << std::endl;
        if (root == nullptr) {
            std::cout << "(empty)" << std::endl;
        }
        else {
            printNode(root);
        }
        std::cout  << std::endl;
    }
};
template <typename T>
class Table_array {
private:
    Row<T>* table;
    size_t count;
    size_t capacity;
public:
    Table_array(size_t size = 100) : count(0), capacity(size) {
        table = new Row<T>[capacity];
        for (size_t i = 0; i < capacity; i++) {
            table[i].is_free = true;  
        }
    }

    ~Table_array() {
        delete[] table;
    }

    void add_data_and_key(const Polinom& data, const T key) {
        size_t oper = 0;
        bool is_replased = false;
        Row<T> to_add;
        to_add.data = data;
        to_add.key = key;
        for (int i = 0; i < count; i++) {
            oper++;
            if (table[i].key == key && !table[i].is_free) {
                table[i] = to_add;
                table[i].is_free = false;
                is_replased = true;
                break;
            }
        }
        if (!is_replased) {
            oper++;
            for (int i = 0; i < capacity; i++) if (table[i].is_free) {
                table[i] = to_add;
                table[i].is_free = false;
                count++;
                std::cout << "[Array] Insert need operations: " << oper << std::endl;
                return;
            }
        }
        
    }
    Polinom find_by_key(const T key) {
        for (size_t i = 0; i < count; i++) {
            if (table[i].key == key) {
                std::cout << "[Array] Find need operations: " << i + 1 << std::endl;
                return table[i].data;
            }
        }
        throw std::string("Element didnt found");
    }

    void print_all_table() {
        for (int i = 0; i < count; i++) {
            table[i].data.print();
        }
    }
};
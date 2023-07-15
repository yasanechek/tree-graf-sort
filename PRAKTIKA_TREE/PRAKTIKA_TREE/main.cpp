#include <iostream>

using namespace std;

template<typename T>
class Helper {
public:
    Helper* left = nullptr;
    Helper* parent = nullptr;
    Helper* right_brother = nullptr;
    T* value = nullptr;
};

void task();

template<typename T>
class Tree {
private:

    Helper<T>* root = nullptr;

    friend void task();
    void add(Helper<T>* parent, T value) {
        if (root == nullptr) {
            root = new Helper<T>();
            root->value = new T(value);
            return;
        }
        if (*parent->value > value) {
            if (parent->left != nullptr && parent->left->value != nullptr) {
                add(parent->left, value);
            }
            else if (parent->left != nullptr && parent->left->value == nullptr) {
                parent->left->value = new T(value);
            }
            else {
                parent->left = new Helper<T>();
                parent->left->value = new T(value);
                parent->left->right_brother = nullptr;
                parent->left->parent = parent;
            }
        }
        else {
            if (parent->left != nullptr && parent->left->value != nullptr) {
                if (parent->left->right_brother != nullptr) {
                    add(parent->left->right_brother, value);
                }
                else {
                    parent->left->right_brother = new Helper<T>();
                    parent->left->right_brother->value = new T(value);
                    parent->left->right_brother->parent = parent;
                }
            }
            else {
                if (parent->left != nullptr && parent->left->right_brother != nullptr) {
                    add(parent->left->right_brother, value);
                }
                else {
                    parent->left = new Helper<T>();
                    parent->left->value = nullptr;
                    parent->left->parent = parent;
                    parent->left->right_brother = new Helper<T>;
                    parent->left->right_brother->value = new T(value);
                    parent->left->right_brother->parent = parent;
                }

            }
        }
    }

    bool in_tree_el(Helper<T>* root, T value) {
        if (root == nullptr) return false;
        if (root->value != nullptr && *root->value == value)return true;
        if (root->left != nullptr)
            return in_tree_el(root->left, value) || in_tree_el(root->left->right_brother, value);
        else
            return in_tree_el(root->left, value);
    }

    void printer(Helper<T>* root) {
        if (root) {
            if (root->value != nullptr)
                cout << *root->value << endl;
            if (root->left != nullptr) {
                printer(root->left);
                printer(root->left->right_brother);
            }
        }
    }

    void simetrichno(Helper<T>* root) {
        if (root) {
            if (root->left != nullptr) {
                simetrichno(root->left);
            }
            if (root->value != nullptr)
                cout << *root->value << endl;
            if (root->left != nullptr) {
                simetrichno(root->left->right_brother);
            }
        }
    }

    void help_reverse(Helper<T>* root) {
        if (root) {
            if (root->left != nullptr) {
                help_reverse(root->left);
                help_reverse(root->left->right_brother);
            }
            if (root->value != nullptr)
                cout << *root->value << endl;
        }
    }

    void add_b_to_a(Helper<T>* root, Tree<T> a) {
        if (root) {
            if (root->value != nullptr)
                a.insert(*root->value);
            if (root->left != nullptr) {
                add_b_to_a(root->left, a);
                add_b_to_a(root->left->right_brother, a);
            }
        }
    }

    void _diffence(Helper<T>* root, Tree<T> other) {
        if (root) {
            if (root->left != nullptr) {
                _diffence(root->left, other);
                _diffence(root->left->right_brother, other);
            }
            if (other.in_tree(*root->value)) {
                root->value = nullptr;
            }
        }
    }

    void del(Helper<T>* root) {
        if (root) {
            if (root->left != nullptr) {
                del(root->left->right_brother);
                del(root->left);
            }
            delete root;
        }
    }

public:

    Tree();

    Tree(T root_value) {
        root = new Helper<T>();
        root->value = new T(root_value);
    }

    void insert(T value) {
        add(root, value);
    }


    void print_tree() {
        if (root == nullptr) {
            cout << "Дерево пустое!" << endl;
            return;
        }
        printer(root);
    }


    void print_semetrichno() {
        if (root == nullptr) {
            cout << "Дерево пустое!" << endl;
            return;
        }
        simetrichno(root);
    }

    void print_reverse() {
        if (root == nullptr) {
            cout << "Дерево пустое!" << endl;
            return;
        }
        help_reverse(root);
    }

    void add_to(Tree<T> other) {
        add_b_to_a(root, other);
    }

    bool in_tree(T value) {
        return in_tree_el(root, value);
    }

    void difference(Tree<T> other) {
        _diffence(root, other);
    }

    void del_tree() {
        del(root);
        root = nullptr;
        cout << "Дерево удалено" << endl;
    }
};


void task() {

    Tree<int> a(11);
    a.insert(9);
    a.insert(7);
    a.insert(10);
    a.insert(21);
    a.insert(1);
    a.insert(12);
    a.insert(31);

    cout << "Дерево А(обратный)" << endl;
    a.print_reverse();

    cout << endl;

    Tree<int> b(6);
    b.insert(31);
    b.insert(17);
    b.insert(4);
    b.insert(7);
    b.insert(6);
    b.insert(3);
    b.insert(2);
    b.insert(16);
    b.insert(1);
    b.insert(8);
    b.insert(10);
    b.insert(44);
    b.insert(12);

    cout << "Дерево B(симметричный)" << endl;
    b.print_semetrichno();

    a.difference(b);

    cout << endl;

    cout << "Дерево A - Дерево B через прямой обход(вывод через прямой обход)" << endl;

    a.print_tree();

    cout << endl;
    b.del_tree();
    a.del_tree();


}

int main() {
    setlocale(LC_ALL, "rus");
    task();
}


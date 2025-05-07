#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    bool lthread, rthread;

    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = true;
    }
};

class TBST {
private:
    Node *root;

public:
    TBST() {
        root = nullptr;
    }

    void insert(int key) {
        Node *ptr = root;
        Node *par = nullptr;

        while (ptr != nullptr) {
            if (key == ptr->data) return;  // No duplicates
            par = ptr;
            if (key < ptr->data) {
                if (!ptr->lthread)
                    ptr = ptr->left;
                else
                    break;
            } else {
                if (!ptr->rthread)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        Node *tmp = new Node(key);
        if (par == nullptr) {
            root = tmp;
        } else if (key < par->data) {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        } else {
            tmp->right = par->right;
            tmp->left = par;
            par->rthread = false;
            par->right = tmp;
        }
    }

    void inorder() {
        Node *ptr = root;
        if (ptr == nullptr) return;

        // Move to the leftmost node
        while (!ptr->lthread)
            ptr = ptr->left;

        while (ptr != nullptr) {
            cout << ptr->data << " ";

            if (ptr->rthread) {
                ptr = ptr->right;
            } else {
                ptr = ptr->right;
                while (!ptr->lthread)
                    ptr = ptr->left;
            }
        }
    }
};

int main() {
    TBST tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);

    cout << "Inorder traversal of TBST: ";
    tree.inorder();
    return 0;
}

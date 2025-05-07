#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    bool lthread, rthread;

    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = false; // Initially regular BST, no threads
    }
};

// Insert into regular BST
Node* insertBST(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->data) root->left = insertBST(root->left, key);
    else if (key > root->data) root->right = insertBST(root->right, key);
    return root;
}

// Store inorder nodes
void storeInorder(Node* root, vector<Node*>& inorderList) {
    if (!root) return;
    storeInorder(root->left, inorderList);
    inorderList.push_back(root);
    storeInorder(root->right, inorderList);
}

// Convert BST to TBST
void convertToTBST(vector<Node*>& inorderList) {
    int n = inorderList.size();
    for (int i = 0; i < n; ++i) {
        Node* curr = inorderList[i];
        // Left thread
        if (!curr->left) {
            curr->left = (i == 0) ? nullptr : inorderList[i - 1];
            curr->lthread = true;
        }
        // Right thread
        if (!curr->right) {
            curr->right = (i == n - 1) ? nullptr : inorderList[i + 1];
            curr->rthread = true;
        }
    }
}

// Inorder traversal using threads
void inorderTBST(Node* root) {
    if (!root) return;

    // Go to leftmost node
    while (!root->lthread && root->left)
        root = root->left;

    while (root) {
        cout << root->data << " ";
        if (root->rthread)
            root = root->right;
        else {
            root = root->right;
            while (root && !root->lthread)
                root = root->left;
        }
    }
}

int main() {
    int n, val;
    Node* root = nullptr;
    cout << "Enter number of nodes: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> val;
        root = insertBST(root, val);
    }

    vector<Node*> inorderList;
    storeInorder(root, inorderList);
    convertToTBST(inorderList);

    cout << "Inorder traversal of Threaded BST: ";
    inorderTBST(inorderList[0]); // Start from leftmost
    return 0;
}

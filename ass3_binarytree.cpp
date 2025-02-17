#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

Node* BinaryTree(){
    int root;
    cin >> root;
    if (root == -1) {
        return NULL;
    }
    Node* temp = new Node(root);
    cout << "left child " << root << " :";
    temp->left = BinaryTree(); 
    cout << "right child " << root << " :";
    temp->right = BinaryTree(); 
    return temp;
}

Node* insertBST(Node* root, int value) {
    if (root == NULL) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insertBST(root->left, value);
    } else if (value > root->data) {
        root->right = insertBST(root->right, value);
    }
    return root;
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL) return root;
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

bool searchBST(Node* root, int value) {
    if (root == NULL) {
        return false;
    }
    if (root->data == value) {
        return true;
    } else if (value < root->data) {
        return searchBST(root->left, value);
    } else {
        return searchBST(root->right, value);
    }
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Non-Recursive Traversals
void inorderNonRecursive(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    while (curr != NULL || !s.empty()) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

void preorderNonRecursive(Node* root) {
    if (root == NULL) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->data << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

void postorderNonRecursive(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        Node* curr = s2.top();
        s2.pop();
        cout << curr->data << " ";
    }
}

vector<int> levelorder(Node* root) {
    queue<Node*> q;
    q.push(root);
    vector<int> ans;
    Node* temp;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        ans.push_back(temp->data);
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
    return ans;
}

class tree {
public:
    tree* root1;
    tree() {
        root1 = NULL;
    }
    Node* treeclone(Node* root1) {
        if (root1 == NULL) {
            return NULL;
        }
        Node* newnode = new Node(root1->data);
        newnode->left = treeclone(root1->left);
        newnode->right = treeclone(root1->right);
        return newnode;
    }

    void printtree(Node* root1) {
        preorder(root1);
    }

    int height(Node* root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (max(leftHeight, rightHeight) + 1);
    }

    bool areTreesEqual(Node* root1, Node* root2) {
        if (root1 == NULL && root2 == NULL) {
            return true;
        }
        if (root1 == NULL || root2 == NULL) {
            return false;
        }
        return (root1->data == root2->data) &&
               areTreesEqual(root1->left, root2->left) &&
               areTreesEqual(root1->right, root2->right);
    }

    Node* mirrorImage(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        Node* newRoot = new Node(root->data);
        newRoot->left = mirrorImage(root->right);
        newRoot->right = mirrorImage(root->left);
        return newRoot;
    }
};
Node* constructBSTFromInorderPreorder(vector<int>& preorder, vector<int>& inorder, int& preIndex, int inStart, int inEnd) {
    if (inStart > inEnd) return NULL;

    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);

    int inIndex = -1;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == rootVal) {
            inIndex = i;
            break;
        }
    }

    root->left = constructBSTFromInorderPreorder(preorder, inorder, preIndex, inStart, inIndex - 1);
    root->right = constructBSTFromInorderPreorder(preorder, inorder, preIndex, inIndex + 1, inEnd);

    return root;
}

Node* createBSTFromInorderPreorder(vector<int>& preorder, vector<int>& inorder) {
    int preIndex = 0;
    return constructBSTFromInorderPreorder(preorder, inorder, preIndex, 0, inorder.size() - 1);
}

void inordertraversal(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
int main() {
    // cout<<"Enter the root value: ";
    // Node* root=BinaryTree();
    Node* root = NULL;
    tree t;
    int choice;
    int bstValue;

    cout << "Enter values for BST (enter -1 to stop): " << endl;
    while (true) {
        cin >> bstValue;
        if (bstValue == -1) break;
        root = insertBST(root, bstValue);
    }

    while (true) {
        cout << "1. Inorder\n2. Preorder\n3. Postorder\n4. Levelorder\n5. Tree clone\n6. Height of tree\n7. Check Trees are equal\n8. Mirror Image\n9. Delete node from BST\n10. Search in BST\n11. creat a BST using preorder and inorder: \n12. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nInorder: ";
            inorderNonRecursive(root);
            cout << endl;
        } else if (choice == 2) {
            cout << "\nPreorder: ";
            preorderNonRecursive(root);
            cout << endl;
        } else if (choice == 3) {
            cout << "\nPostorder: ";
            postorderNonRecursive(root);
            cout << endl;
        } else if (choice == 4) {
            cout << "\nLevelorder: ";
            vector<int> ans = levelorder(root);
            for (auto a : ans) {
                cout << a << " ";
            }
            cout << endl;
        } else if (choice == 5) {
            cout << "\nTree clone (Preorder of cloned tree): ";
            t.printtree(root);
            cout << endl;
        } else if (choice == 6) {
            int treeHeight = t.height(root);
            cout << "\nHeight of the tree: " << treeHeight << endl;
        } else if (choice == 7) {
            cout << "\nCheck if original and cloned trees are equal: ";
            Node* clonedRoot = t.treeclone(root);
            if (t.areTreesEqual(root, clonedRoot)) {
                cout << "Yes, the trees are equal." << endl;
            } else {
                cout << "No, the trees are not equal." << endl;
            }
        } else if (choice == 8) {
            cout << "\nMirror image (Preorder of mirrored tree): ";
            Node* mirroredRoot = t.mirrorImage(root);
            t.printtree(mirroredRoot);
            cout << endl;
        } else if (choice == 9) {
            int deleteValue;
            cout << "Enter value to delete from BST: ";
            cin >> deleteValue;
            root = deleteNode(root, deleteValue);
            cout << "Node deleted (if present)" << endl;
        } else if (choice == 10) {
            int searchValue;
            cout << "Enter value to search in BST: ";
            cin >> searchValue;
            if (searchBST(root, searchValue)) {
                cout << searchValue << " found in BST." << endl;
            } else {
                cout << searchValue << " not found in BST." << endl;
            }
        } else if (choice == 11) {
            vector<int> preorder = {10, 5, 1, 7, 40, 50};
            vector<int> inorder = {1, 5, 7, 10, 40, 50};
        
            Node* root = createBSTFromInorderPreorder(preorder, inorder);
        
            cout << "Inorder traversal of the constructed BST: ";
            inordertraversal(root);
            cout << endl;
            break;
          
        }else if(choice == 12){
            cout<<"Exiting program ";
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 1. Insert into BST
Node* insertBST(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// 2. Traversals
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        cout << node->data << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

void inorderTraversal(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }
        current = st.top();
        st.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preorderTraversal(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        cout << current->data << " ";

        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
}

void postorderTraversal(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// 3. Height of Tree
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// 4. Clone Tree
Node* clone(Node* root) {
    if (!root) return nullptr;
    Node* newNode = new Node(root->data);
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}

// 5. Mirror
Node* mirror(Node* root) {
    if (!root) return nullptr;
    Node* mirrored = new Node(root->data);
    mirrored->left = mirror(root->right);
    mirrored->right = mirror(root->left);
    return mirrored;
}

// 6. Build tree from inorder and preorder
int search(int inorder[], int start, int end, int val) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == val) return i;
    return -1;
}

Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int& preIndex) {
    if (inStart > inEnd) return nullptr;
    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);
    int inIndex = search(inorder, inStart, inEnd, rootVal);
    root->left = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex);
    root->right = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex);
    return root;
}

// 7. Delete node in BST
Node* minValueNode(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void deleteTree(Node*& root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

// 8. Check if trees are equal
bool isEqual(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b || a->data != b->data) return false;
    return isEqual(a->left, b->left) && isEqual(a->right, b->right);
}

int main() {
    Node* root = nullptr;
    root = insertBST(root, 50);
    insertBST(root, 30);
    insertBST(root, 70);
    insertBST(root, 20);
    insertBST(root, 40);
    insertBST(root, 60);
    insertBST(root, 80);

    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    cout << "Level Order: "; levelOrder(root); cout << endl;

    cout << "Height: " << height(root) << endl;

    Node* cloned = clone(root);
    deleteTree(root);
    cout << "Original tree deleted. Cloned inorder: "; inorder(cloned); cout << endl;

    Node* mirrorTree = mirror(cloned);
    cout << "Mirror inorder: "; inorder(mirrorTree); cout << endl;

    int inorderArr[] = {20, 30, 40, 50, 60, 70, 80};
    int preorderArr[] = {50, 30, 20, 40, 70, 60, 80};
    int preIndex = 0;
    Node* built = buildTree(inorderArr, preorderArr, 0, 6, preIndex);
    cout << "Built Tree Inorder: "; inorder(built); cout << endl;

    built = deleteNode(built, 30);
    cout << "After deleting 30: "; inorder(built); cout << endl;

    cout << "Are cloned and mirror equal? " << (isEqual(cloned, mirrorTree) ? "Yes" : "No") << endl;

    return 0;
}


#include <iostream>
#include <climits>
#include <string>
using namespace std;

const int MAX = 50;

struct Node {
    int keyIndex;
    Node* left;
    Node* right;

    Node(int idx) : keyIndex(idx), left(nullptr), right(nullptr) {}
};

Node* buildTree(int rootTable[MAX][MAX], int i, int j) {
    if (rootTable[i][j] == 0) return nullptr;
    int rootIdx = rootTable[i][j];
    Node* node = new Node(rootIdx);
    node->left = buildTree(rootTable, i, rootIdx - 1);
    node->right = buildTree(rootTable, rootIdx + 1, j);
    return node;
}

Node* optimalBST(int success[], int failure[], int n) {
    int cost[MAX][MAX] = {}, weight[MAX][MAX] = {}, root[MAX][MAX] = {};

    // Initialize for one key
    for (int i = 1; i <= n; i++) {
        weight[i][i] = failure[i - 1] + success[i] + failure[i];
        cost[i][i] = weight[i][i];
        root[i][i] = i;
    }

    // Build for multiple keys
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            weight[i][j] = weight[i][j - 1] + success[j] + failure[j];
            cost[i][j] = INT_MAX;

            for (int k = i; k <= j; k++) {
                int tempCost = cost[i][k - 1] + cost[k + 1][j] + weight[i][j];
                if (tempCost < cost[i][j]) {
                    cost[i][j] = tempCost;
                    root[i][j] = k;
                }
            }
        }
    }

    cout << "Cost of Optimal BST: " << cost[1][n] << endl;
    return buildTree(root, 1, n);
}

void preorder(Node* node, string keys[]) {
    if (!node) return;
    cout << keys[node->keyIndex] << " ";
    preorder(node->left, keys);
    preorder(node->right, keys);
}

int main() {
    int n;
    cout << "Number of keys: ";
    cin >> n;

    string keys[n + 1];     // keys[1...n]
    int success[n + 1];     // success probabilities
    int failure[n + 1];     // failure probabilities

    cout << "Enter keys in sorted order:\n";
    for (int i = 1; i <= n; i++) cin >> keys[i];

    cout << "Enter success probabilities (p[1...n]):\n";
    for (int i = 1; i <= n; i++) cin >> success[i];

    cout << "Enter failure probabilities (q[0...n]):\n";
    for (int i = 0; i <= n; i++) cin >> failure[i];

    Node* root = optimalBST(success, failure, n);

    cout << "Preorder traversal of Optimal BST:\n";
    preorder(root, keys);
    cout << endl;

    return 0;
}

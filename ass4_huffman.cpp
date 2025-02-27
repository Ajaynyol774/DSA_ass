#include<bits/stdc++.h>
using namespace std;

#include <map>
#include <vector>

using namespace std;

class ThreadedNode {
public:
    int data;
    ThreadedNode* left;
    ThreadedNode* right;
    bool leftThread;  
    bool rightThread; 

    ThreadedNode(int val) {
        data = val;
        left = right = NULL;
        leftThread = rightThread = false;
    }
};


void inorderTraversal(ThreadedNode* root) {
    ThreadedNode* current = root;
    while (current != NULL) {
        while (current->left != NULL && !current->leftThread) {
            current = current->left;
        }

        
        cout << current->data << " ";

        
        if (current->rightThread) {
            current = current->right;
        } else {
            
            current = current->right;
        }
    }
}


ThreadedNode* insertThreaded(ThreadedNode* root, int value) {
    if (root == NULL) return new ThreadedNode(value);

    ThreadedNode* current = root;
    ThreadedNode* parent = NULL;

 
    while (current != NULL) {
        parent = current;
        if (value < current->data) {
            if (current->left == NULL || current->leftThread) {
                break;
            }
            current = current->left;
        } else {
            if (current->right == NULL || current->rightThread) {
                break;
            }
            current = current->right;
        }
    }

    ThreadedNode* newNode = new ThreadedNode(value);

    if (value < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->leftThread = true;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rightThread = true;
        parent->right = newNode;
    }

    return root;
}


ThreadedNode* nextInOrder(ThreadedNode* root) {
    if (root == NULL) return NULL;

    // If right child exists, the next node will be the leftmost child of right subtree
    if (!root->rightThread) {
        root = root->right;
        while (root != NULL && root->left != NULL && !root->leftThread) {
            root = root->left;
        }
        return root;
    }

    return root->right;
}


struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

void sortNodes(vector<MinHeapNode*>& nodes) {
    sort(nodes.begin(), nodes.end(), [](MinHeapNode* a, MinHeapNode* b) {
        return a->freq < b->freq;
    });
}

void printCodes(MinHeapNode* root, string str) {
    if (root == NULL) return;

    // If this is a leaf node, print the character and its code
    if (root->data != '$') {
        cout << root->data << ": " << str << endl;
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(string data, vector<int> freq) {
    // Create a list of nodes, each with a character and frequency
    vector<MinHeapNode*> nodes;
    for (int i = 0; i < data.size(); ++i) {
        nodes.push_back(new MinHeapNode(data[i], freq[i]));
    }

    // Build the Huffman tree
    while (nodes.size() > 1) {
        sortNodes(nodes);

        MinHeapNode* left = nodes[0];
        MinHeapNode* right = nodes[1];

        // Create a new internal node with frequency sum of two nodes
        MinHeapNode* top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        // Remove the two nodes from the list and add the new node
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        nodes.push_back(top);
    }

    // The final node is the root of the Huffman tree
    printCodes(nodes[0], "");
}

int main() {
    int choice, value;
    ThreadedNode* root = NULL;

    while (true) {
        cout << "1. Insert into Threaded Binary Tree\n2. Inorder Traversal of TBT\n3. Find Next Node in TBT\n4. Huffman Code\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter value to insert: ";
            cin >> value;
            root = insertThreaded(root, value);
        }
        else if (choice == 2) {
            cout << "Inorder Traversal of Threaded Binary Tree: ";
            inorderTraversal(root);
            cout << endl;
        }
        else if (choice == 3) {
            ThreadedNode* nextNode = nextInOrder(root);
            if (nextNode != NULL)
                cout << "Next node in inorder: " << nextNode->data << endl;
            else
                cout << "No next node found." << endl;
        }
        else if (choice == 4) {
            string data = "abcdef";
            vector<int> freq = {5, 9, 12, 13, 16, 45};

            cout << "Huffman Code for the given data:\n";
            HuffmanCodes(data, freq);
        }
        else if (choice == 5) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

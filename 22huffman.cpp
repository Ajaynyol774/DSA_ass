#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, string str, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = str;
    buildCodes(root->left, str + "0", codes);
    buildCodes(root->right, str + "1", codes);
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    cout << "Enter character and frequency:\n";
    for (int i = 0; i < n; ++i) {
        char ch; int freq;
        cin >> ch >> freq;
        pq.push(new Node(ch, freq));
    }

    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* parent = new Node('$', l->freq + r->freq);
        parent->left = l;
        parent->right = r;
        pq.push(parent);
    }

    unordered_map<char, string> codes;
    buildCodes(pq.top(), "", codes);

    cout << "\nHuffman Codes:\n";
    for (auto& p : codes)
        cout << p.first << ": " << p.second << '\n';

    string input;
    cout << "\nEnter string to encode: ";
    cin >> input;

    cout << "Encoded string: ";
    for (char ch : input)
        cout << codes[ch];
    cout << '\n';

    return 0;
}

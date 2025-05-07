#include <bits/stdc++.h>
using namespace std;

const int SIZE = 26;  // 26 letters for 'a' to 'z'

// Each index holds a list of words that hash to it
vector<string> table[SIZE];

// Simple hash: based on first letter
int hashFunc(string word) {
    return word[0] - 'a';
}

void insert(string word) {
    int index = hashFunc(word);
    table[index].push_back(word);
}

bool search(string word) {
    int index = hashFunc(word);
    for (string w : table[index])
        if (w == word) return true;
    return false;
}

int main() {
    // Sample correct words
    string words[] = {
        "apple", "ball", "cat", "dog", "egg", "fish", "goat", "hat", "ice", "jug", "kite", "lion", "milk", "net", "owl", "pig", "queen", "rat", "sun", "tree"
    };

    for (string w : words) insert(w);

    string input;
    cout << "Enter a word to check spelling (type 'exit' to quit):\n";
    while (true) {
        cout << "> ";
        cin >> input;
        if (input == "exit") break;
        if (search(input))
            cout << "o '" << input << "' is spelled correctly.\n";
        else
            cout << "X '" << input << "' is not in the dictionary.\n";
    }

    return 0;
}

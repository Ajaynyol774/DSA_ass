#include<iostream>
using namespace std;
const int table_size=10;

class hashtable {
private:
    int table[table_size];

public:
    hashtable() {
        for(int i = 0; i < table_size; i++) {
            table[i] = -1;
        }
    }

    int hashfunction(int key) {
        return key % table_size;
    }

    bool tableFull() {
        for(int i = 0; i < table_size; i++) {
            if(table[i] == -1) {
                return false;
            }
        }
        return true;
    }

    void insert(int key) {
        if(tableFull()) {
            cout << "Table is full, cannot insert more keys." << endl;
            return;
        }

        int index = hashfunction(key);
        while(table[index] != -1) {
            if (table[index] == key) {
                cout << "Key already exists in the table." << endl;
                return;
            }
            index = (index + 1) % table_size;
        }
        table[index] = key;
    }

    void search(int key) {
        int index = hashfunction(key);
        while(table[index] != -1) {
            if(table[index] == key) {
                cout << "Key found in the table." << endl;
                return;
            }
            index = (index + 1) % table_size;
        }
        cout << "Key not found in the table." << endl;
    }

    void displaytable() {
        for(int i = 0; i < table_size; i++) {
            cout << "index " << i << ": " << table[i] << endl;
        }
    }
};

int main() {
    hashtable has;
    int choice, key;

    while(true) {
        cout << "1. Insert\n2. Display\n3. Search\n4. Exit\n";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter the value you want to store: ";
                cin >> key;
                has.insert(key);
                break;
            case 2:
                has.displaytable();
                break;
            case 3:
                cout << "Enter the key you want to search: ";
                cin >> key;
                has.search(key);
                break;
            case 4:
                cout << "Exit the Program" << endl;
                return 0;
            default:
                cout << "Enter a valid choice" << endl;
        }
    }

    return 0;
}

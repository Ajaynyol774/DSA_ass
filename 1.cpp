//Linear Chaining Without Replacement

#include <iostream>
using namespace std;

const int SIZE = 10;

int rollNo[SIZE];
int marks[SIZE];
int link[SIZE];  // Renamed from 'next' to avoid conflict

void initialize() {
    for (int i = 0; i < SIZE; i++) {
        rollNo[i] = -1;  // -1 means empty
        link[i] = -1;
    }
}

int hashFunc(int key) {
    return key % SIZE;
}

void insert(int key, int mark) {
    int index = hashFunc(key);

    if (rollNo[index] == -1) {
        // No collision, insert directly
        rollNo[index] = key;
        marks[index] = mark;
    } else {
        // Collision occurred
        int i;
        for (i = 1; i < SIZE; i++) {
            int newIndex = (index + i) % SIZE;
            if (rollNo[newIndex] == -1) {
                rollNo[newIndex] = key;
                marks[newIndex] = mark;

                // Link it to the chain starting at index
                int chain = index;
                while (link[chain] != -1) {
                    chain = link[chain];
                }
                link[chain] = newIndex;
                break;
            }
        }
        if (i == SIZE)
            cout << "Table full, can't insert " << key << endl;
    }
}

void display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < SIZE; i++) {
        if (rollNo[i] != -1) {
            cout << "Index " << i << ": RollNo " << rollNo[i] << ", Marks " << marks[i];
            if (link[i] != -1)
                cout << " -> " << link[i];
            cout << endl;
        } else {
            cout << "Index " << i << ": Empty\n";
        }
    }
}

int main() {
    initialize();

    int rolls[] = {31, 13, 14, 51, 15, 71, 48, 19};
    int mks[]   = {90, 85, 75, 88, 92, 67, 80, 89};

    for (int i = 0; i < 8; i++) {
        insert(rolls[i], mks[i]);
    }

    display();
    return 0;
}

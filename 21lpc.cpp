#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 10;

vector<int> PNR(SIZE, -1);
vector<int> marks(SIZE, -1);
vector<int> link(SIZE, -1);

int hashFunc(int p) {
    return p % SIZE;
}

void insert(int p, int m) {
    int i = hashFunc(p);

    if (PNR[i] == -1) {
        PNR[i] = p;
        marks[i] = m;
        return;
    }

    int h_exist = hashFunc(PNR[i]);

    if (h_exist != i) {
        // Replacement needed
        int old_p = PNR[i], old_m = marks[i];
        int old_link = link[i]; // Save link before overwriting

        // Insert new value at home
        PNR[i] = p;
        marks[i] = m;
        link[i] = -1;  // Reset link for new entry

        // Reinsert the replaced (displaced) value
        for (int j = 1; j < SIZE; j++) {
            int ni = (i + j) % SIZE;
            if (PNR[ni] == -1) {
                PNR[ni] = old_p;
                marks[ni] = old_m;
                link[ni] = old_link;

                // Update chain from old hash location
                int chain_head = h_exist;
                while (link[chain_head] != i && link[chain_head] != -1)
                    chain_head = link[chain_head];

                if (link[chain_head] == i)
                    link[chain_head] = ni;
                else
                    link[chain_head] = ni; // New chain start

                break;
            }
        }
    } else {
        // Normal chaining (no replacement)
        for (int j = 1; j < SIZE; j++) {
            int ni = (i + j) % SIZE;
            if (PNR[ni] == -1) {
                PNR[ni] = p;
                marks[ni] = m;
                link[ni] = -1;

                // Add to chain
                while (link[i] != -1) i = link[i];
                link[i] = ni;
                break;
            }
        }
    }
}

void display() {
    cout << "Index\tPNR\tMarks\tLink\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << "\t";
        if (PNR[i] != -1)
            cout << PNR[i] << "\t" << marks[i] << "\t" << link[i] << endl;
        else
            cout << "-\t-\t-\n";
    }
}

int main() {
    vector<int> pnrList = {11, 21, 31, 34, 55, 52, 33, 46};
    vector<int> markList = {70, 75, 80, 85, 60, 65, 78, 71};

    for (int i = 0; i < pnrList.size() && i < SIZE; i++)
        insert(pnrList[i], markList[i]);

    display();
    return 0;
}

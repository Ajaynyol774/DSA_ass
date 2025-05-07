#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string division;
    string address;
    
    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);
    }
    
    void display() const {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

// Add student
void addStudent() {
    ofstream file("students.txt", ios::app);
    Student s;
    s.input();
    file << s.rollNo << "," << s.name << "," << s.division << "," << s.address << endl;
    file.close();
    cout << "Student added successfully.\n";
}

// Display all students
void displayAllStudents() {
    ifstream file("students.txt");
    string line;
    cout << "\n--- All Students ---\n";
    bool found = false;
    
    while (getline(file, line)) {
        int fileRoll;
        string name, division, address;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        
        fileRoll = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        division = line.substr(pos2 + 1, pos3 - pos2 - 1);
        address = line.substr(pos3 + 1);
        
        Student s = {fileRoll, name, division, address};
        s.display();
        cout << "------------------------\n";
        found = true;
    }
    
    if (!found)
        cout << "No students found.\n";
    
    file.close();
}

// Search student by roll number
void searchStudent() {
    ifstream file("students.txt");
    int roll;
    bool found = false;
    cout << "Enter roll number to search: ";
    cin >> roll;
    string line;
    
    while (getline(file, line)) {
        int fileRoll;
        string name, division, address;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        
        fileRoll = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        division = line.substr(pos2 + 1, pos3 - pos2 - 1);
        address = line.substr(pos3 + 1);
        
        if (fileRoll == roll) {
            Student s = {fileRoll, name, division, address};
            cout << "\nStudent found:\n";
            s.display();
            found = true;
            break;
        }
    }
    
    if (!found)
        cout << "Student with roll number " << roll << " not found.\n";
    
    file.close();
}

// Delete student
void deleteStudent() {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    int roll;
    bool found = false;
    cout << "Enter roll number to delete: ";
    cin >> roll;
    string line;
    
    while (getline(inFile, line)) {
        int fileRoll;
        size_t pos1 = line.find(',');
        fileRoll = stoi(line.substr(0, pos1));
        
        if (fileRoll != roll) {
            outFile << line << endl;
        } else {
            found = true;
        }
    }
    
    inFile.close();
    outFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    
    if (found)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student with roll number " << roll << " not found.\n";
}

// Insert student function
void insertStudent() {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    Student s;
    s.input();
    string line;
    bool inserted = false;
    
    // Check if student with same roll number already exists
    inFile.clear();
    inFile.seekg(0, ios::beg);
    
    while (getline(inFile, line)) {
        int fileRoll;
        size_t pos1 = line.find(',');
        fileRoll = stoi(line.substr(0, pos1));
        
        if (fileRoll == s.rollNo) {
            cout << "Student with roll number " << s.rollNo << " already exists.\n";
            inFile.close();
            outFile.close();
            remove("temp.txt");
            return;
        }
    }
    
    // Insert student in sorted order by roll number
    inFile.clear();
    inFile.seekg(0, ios::beg);
    
    while (getline(inFile, line)) {
        int fileRoll;
        size_t pos1 = line.find(',');
        fileRoll = stoi(line.substr(0, pos1));
        
        if (!inserted && fileRoll > s.rollNo) {
            outFile << s.rollNo << "," << s.name << "," << s.division << "," << s.address << endl;
            inserted = true;
        }
        
        outFile << line << endl;
    }
    
    if (!inserted) {
        outFile << s.rollNo << "," << s.name << "," << s.division << "," << s.address << endl;
    }
    
    inFile.close();
    outFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    
    cout << "Student inserted successfully.\n";
}

// Main menu
int main() {
    int choice;
    
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Insert Student (Sorted by Roll No)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: insertStudent(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    
    return 0;
}
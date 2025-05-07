#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

// Employee structure with fixed-size fields for direct access
struct Employee {
    int empID;
    char name[50];
    char designation[50];
    float salary;
    bool isActive;  // Flag to mark if record is active or deleted

    // Default constructor
    Employee() {
        empID = 0;
        strcpy(name, "");
        strcpy(designation, "");
        salary = 0.0;
        isActive = false;
    }

    void input() {
        cout << "Enter Employee ID: ";
        cin >> empID;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Designation: ";
        cin.getline(designation, 50);
        cout << "Enter Salary: ";
        cin >> salary;
        isActive = true;
    }

    void display() const {
        cout << "Employee ID: " << empID << "\n"
             << "Name: " << name << "\n"
             << "Designation: " << designation << "\n"
             << "Salary: " << salary << "\n";
    }
};

const string FILENAME = "employee.dat";
const int MAX_RECORDS = 100;

// Initialize file with empty records
void initializeFile() {
    ifstream testFile(FILENAME, ios::binary);
    if (!testFile) {
        ofstream file(FILENAME, ios::binary);
        Employee emptyEmployee;
        
        for (int i = 0; i < MAX_RECORDS; i++) {
            file.write(reinterpret_cast<char*>(&emptyEmployee), sizeof(Employee));
        }
        file.close();
        cout << "File initialized with " << MAX_RECORDS << " empty records." << endl;
    }
    testFile.close();
}

// Build an index of employee IDs and their position in the file
map<int, int> buildIndex() {
    map<int, int> index;
    ifstream file(FILENAME, ios::binary);
    
    Employee emp;
    for (int pos = 0; pos < MAX_RECORDS; pos++) {
        file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        if (emp.isActive) {
            index[emp.empID] = pos;
        }
    }
    
    file.close();
    return index;
}

// Add an employee to the file
void addEmployee() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    emp.input();
    
    // Check if employee ID already exists
    map<int, int> index = buildIndex();
    if (index.find(emp.empID) != index.end()) {
        cout << "Error: Employee with ID " << emp.empID << " already exists!" << endl;
        file.close();
        return;
    }
    
    // Find first empty slot
    Employee temp;
    file.seekg(0, ios::beg);
    
    for (int i = 0; i < MAX_RECORDS; i++) {
        file.read(reinterpret_cast<char*>(&temp), sizeof(Employee));
        if (!temp.isActive) {
            // Found empty slot
            file.seekp(i * sizeof(Employee), ios::beg);
            file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
            cout << "Employee added successfully at position " << i << endl;
            file.close();
            return;
        }
    }
    
    cout << "Error: File is full! Cannot add more employees." << endl;
    file.close();
}

// Display all employees
void displayAllEmployees() {
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    bool found = false;
    cout << "\n--- All Employees ---\n";
    
    for (int i = 0; i < MAX_RECORDS; i++) {
        file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        if (emp.isActive) {
            cout << "\nRecord #" << i << ":\n";
            emp.display();
            cout << "------------------------\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "No employees found in the database.\n";
    }
    
    file.close();
}

// Display an employee by ID
void displayEmployee() {
    map<int, int> index = buildIndex();
    int id;
    cout << "Enter Employee ID to search: ";
    cin >> id;
    
    if (index.find(id) == index.end()) {
        cout << "Employee with ID " << id << " not found.\n";
        return;
    }
    
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    Employee emp;
    file.seekg(index[id] * sizeof(Employee), ios::beg);
    file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
    
    cout << "\nEmployee Found:\n";
    emp.display();
    
    file.close();
}

// Delete an employee by ID
void deleteEmployee() {
    map<int, int> index = buildIndex();
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;
    
    if (index.find(id) == index.end()) {
        cout << "Employee with ID " << id << " not found.\n";
        return;
    }
    
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    // Logical deletion - mark record as inactive
    Employee emp;
    file.seekg(index[id] * sizeof(Employee), ios::beg);
    file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
    
    emp.isActive = false;
    file.seekp(index[id] * sizeof(Employee), ios::beg);
    file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    
    cout << "Employee deleted successfully.\n";
    file.close();
}

// Update an employee by ID
void updateEmployee() {
    map<int, int> index = buildIndex();
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;
    
    if (index.find(id) == index.end()) {
        cout << "Employee with ID " << id << " not found.\n";
        return;
    }
    
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    // Get the current employee data
    Employee emp;
    file.seekg(index[id] * sizeof(Employee), ios::beg);
    file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
    
    cout << "\nCurrent Employee Details:\n";
    emp.display();
    
    cout << "\nEnter new details:\n";
    cin.ignore();
    
    cout << "Enter Name: ";
    cin.getline(emp.name, 50);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 50);
    cout << "Enter Salary: ";
    cin >> emp.salary;
    
    // Write back the updated record
    file.seekp(index[id] * sizeof(Employee), ios::beg);
    file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
    
    cout << "Employee updated successfully.\n";
    file.close();
}

// Main menu
void showMenu() {
    int choice;

    do {
        cout << "\n--- Employee Management System (Direct Access) ---\n"
             << "1. Add Employee\n"
             << "2. Display All Employees\n"
             << "3. Display Employee\n"
             << "4. Update Employee\n"
             << "5. Delete Employee\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayAllEmployees(); break;
            case 3: displayEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 6);
}

int main() {
    // Initialize the file if it doesn't exist
    initializeFile();
    showMenu();
    return 0;
}
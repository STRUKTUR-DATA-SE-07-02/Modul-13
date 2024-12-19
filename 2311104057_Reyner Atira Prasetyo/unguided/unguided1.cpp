#include <iostream>
#include <string>
using namespace std;

struct Project {
    string projectName;
    int duration;
    Project* nextProject;
};

struct Employee {
    string employeeName;
    string employeeID;
    Project* projectHead;
    Employee* nextEmployee;
};

// Head of the Employee List
Employee* employeeHead = nullptr;

// Function to create a new employee node
Employee* createEmployee(string name, string id) {
    Employee* newEmployee = new Employee;
    newEmployee->employeeName = name;
    newEmployee->employeeID = id;
    newEmployee->projectHead = nullptr;
    newEmployee->nextEmployee = nullptr;
    return newEmployee;
}

// Function to create a new project node
Project* createProject(string name, int duration) {
    Project* newProject = new Project;
    newProject->projectName = name;
    newProject->duration = duration;
    newProject->nextProject = nullptr;
    return newProject;
}

// Function to add an employee to the list
void addEmployee(string name, string id) {
    Employee* newEmployee = createEmployee(name, id);
    if (employeeHead == nullptr) {
        employeeHead = newEmployee;
    } else {
        Employee* temp = employeeHead;
        while (temp->nextEmployee != nullptr) {
            temp = temp->nextEmployee;
        }
        temp->nextEmployee = newEmployee;
    }
    cout << "Employee : " << name << " with ID : " << id << " added.\n";
}

// Function to add a project to an employee
void addProjectToEmployee(string employeeID, string projectName, int duration) {
    Employee* temp = employeeHead;
    while (temp != nullptr && temp->employeeID != employeeID) {
        temp = temp->nextEmployee;
    }

    if (temp == nullptr) {
        cout << "Employee with ID : " << employeeID << " not found.\n";
        return;
    }

    Project* newProject = createProject(projectName, duration);
    if (temp->projectHead == nullptr) {
        temp->projectHead = newProject;
    } else {
        Project* pTemp = temp->projectHead;
        while (pTemp->nextProject != nullptr) {
            pTemp = pTemp->nextProject;
        }
        pTemp->nextProject = newProject;
    }
    cout << "Project : " << projectName << " with duration : " << duration << " months added to employee : " << temp->employeeName << ".\n";
}

// Function to delete a project from an employee
void deleteProjectFromEmployee(string employeeID, string projectName) {
    Employee* temp = employeeHead;
    while (temp != nullptr && temp->employeeID != employeeID) {
        temp = temp->nextEmployee;
    }

    if (temp == nullptr) {
        cout << "Employee with ID : " << employeeID << " not found.\n";
        return;
    }

    Project* pTemp = temp->projectHead;
    Project* prev = nullptr;

    while (pTemp != nullptr && pTemp->projectName != projectName) {
        prev = pTemp;
        pTemp = pTemp->nextProject;
    }

    if (pTemp == nullptr) {
        cout << "Project : " << projectName << " not found for employee : " << temp->employeeName << ".\n";
        return;
    }

    if (prev == nullptr) {
        temp->projectHead = pTemp->nextProject;
    } else {
        prev->nextProject = pTemp->nextProject;
    }

    delete pTemp;
    cout << "Project : " << projectName << " removed from employee : " << temp->employeeName << ".\n";
}

// Function to display all employees and their projects
void displayEmployees() {
    Employee* temp = employeeHead;
    while (temp != nullptr) {
        cout << "Employee Name : " << temp->employeeName << ", ID : " << temp->employeeID << "\n";
        Project* pTemp = temp->projectHead;
        while (pTemp != nullptr) {
            cout << "Project : " << pTemp->projectName << ", Duration : " << pTemp->duration << " months\n";
            pTemp = pTemp->nextProject;
        }
        temp = temp->nextEmployee;
        cout << "\n";
    }
}

int main() {
    // Adding employees
    addEmployee("Andi", "P001");
    addEmployee("Budi", "P002");
    addEmployee("Citra", "P003");
    cout << "\n";
    displayEmployees();
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Adding projects to employees
    addProjectToEmployee("P001", "Aplikasi Mobile", 12);
    addProjectToEmployee("P002", "Sistem Akuntansi", 8);
    addProjectToEmployee("P003", "E-commerce", 10);
    cout << "\n";
    displayEmployees();
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Adding a new project to Andi
    addProjectToEmployee("P001", "Analisis Data", 6);
    cout << "\n";
    displayEmployees();
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Deleting a project from Andi
    deleteProjectFromEmployee("P001", "Aplikasi Mobile");
    cout << "\n";
    displayEmployees();

    return 0;
}
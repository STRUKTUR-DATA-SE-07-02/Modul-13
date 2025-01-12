#include <iostream>
#include <string>

using namespace std;

struct ProjectNode {
    string projectName;
    int duration; // in months
    ProjectNode* next;

    ProjectNode(string name, int dur) : projectName(name), duration(dur), next(nullptr) {}
};

struct EmployeeNode {
    string employeeName;
    string employeeID;
    EmployeeNode* next;
    ProjectNode* projectHead;

    EmployeeNode(string name, string id) : employeeName(name), employeeID(id), next(nullptr), projectHead(nullptr) {}
};

class EmployeeProjectList {
private:
    EmployeeNode* head;

public:
    EmployeeProjectList() : head(nullptr) {}

    void addEmployee(string name, string id) {
        EmployeeNode* newEmployee = new EmployeeNode(name, id);
        newEmployee->next = head;
        head = newEmployee;
    }

    void addProject(string employeeID, string projectName, int duration) {
        EmployeeNode* employee = head;
        while (employee != nullptr && employee->employeeID != employeeID) {
            employee = employee->next;
        }
        if (employee != nullptr) {
            ProjectNode* newProject = new ProjectNode(projectName, duration);
            newProject->next = employee->projectHead;
            employee->projectHead = newProject;
        } else {
            cout << "Employee not found!" << endl;
        }
    }

    void deleteProject(string employeeID, string projectName) {
        EmployeeNode* employee = head;
        while (employee != nullptr && employee->employeeID != employeeID) {
            employee = employee->next;
        }
        if (employee != nullptr) {
            ProjectNode** current = &(employee->projectHead);
            while (*current != nullptr && (*current)->projectName != projectName) {
                current = &((*current)->next);
            }
            if (*current != nullptr) {
                ProjectNode* toDelete = *current;
                *current = (*current)->next;
                delete toDelete;
                cout << "Project " << projectName << " deleted from " << employee->employeeName << "." << endl;
            } else {
                cout << "Project not found!" << endl;
            }
        } else {
            cout << "Employee not found!" << endl;
        }
    }

    void display() {
        EmployeeNode* current = head;
        while (current != nullptr) {
            cout << "Employee: " << current->employeeName << " (ID: " << current->employeeID << ") -> ";
            ProjectNode* project = current->projectHead;
            while (project != nullptr) {
                cout << "[" << project->projectName << ", " << project->duration << " months] ";
                project = project->next;
            }
            cout << endl;
            current = current->next;
        }
    }

    ~EmployeeProjectList() {
        while (head != nullptr) {
            EmployeeNode* temp = head;
            head = head->next;
            while (temp->projectHead != nullptr) {
                ProjectNode* projectTemp = temp->projectHead;
                temp->projectHead = temp->projectHead->next;
                delete projectTemp;
            }
            delete temp;
        }
    }
};

int main() {
    EmployeeProjectList empList;

    empList.addEmployee("Andi", "P001");
    empList.addEmployee("Budi", "P002");
    empList.addEmployee("Citra", "P003");

    empList.addProject("P001", "Aplikasi Mobile", 12);
    empList.addProject("P002", "Sistem Akuntansi", 8);
    empList.addProject("P003", "E-commerce", 10);

    cout << "Before adding new project:" << endl;
    empList.display();

    empList.addProject("P001", "Analisis Data", 6);

    cout << "\nAfter adding new project:" << endl;
    empList.display();

    empList.deleteProject("P001", "Aplikasi Mobile");

    cout << "\nAfter deleting a project:" << endl;
    empList.display();

    return 0;
}
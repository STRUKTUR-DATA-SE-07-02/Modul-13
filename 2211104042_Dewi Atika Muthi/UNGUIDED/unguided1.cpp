#include <iostream>
#include <string>
using namespace std;

struct Project {
    string name;
    int duration;
    Project* next;
};

struct Employee {
    string name;
    string id;
    Project* projects;
    Employee* next;
};

Employee* head = nullptr;

void addEmployee(string name, string id) {
    Employee* newEmployee = new Employee{name, id, nullptr, head};
    head = newEmployee;
}

void addProject(string empId, string projectName, int duration) {
    Employee* temp = head;
    while (temp && temp->id != empId) {
        temp = temp->next;
    }
    if (temp) {
        Project* newProject = new Project{projectName, duration, temp->projects};
        temp->projects = newProject;
    }
}

void removeProject(string empId, string projectName) {
    Employee* temp = head;
    while (temp && temp->id != empId) {
        temp = temp->next;
    }
    if (temp) {
        Project* curr = temp->projects;
        Project* prev = nullptr;
        while (curr && curr->name != projectName) {
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            if (prev) {
                prev->next = curr->next;
            } else {
                temp->projects = curr->next;
            }
            delete curr;
        }
    }
}

void displayData() {
    Employee* emp = head;
    while (emp) {
        cout << "Pegawai: " << emp->name << " (" << emp->id << ")\n";
        Project* proj = emp->projects;
        while (proj) {
            cout << "  - Proyek: " << proj->name << " (" << proj->duration << " bulan)\n";
            proj = proj->next;
        }
        emp = emp->next;
    }
}

int main() {
    addEmployee("Andi", "P001");
    addEmployee("Budi", "P002");
    addEmployee("Citra", "P003");

    addProject("P001", "Aplikasi Mobile", 12);
    addProject("P002", "Sistem Akuntansi", 8);
    addProject("P003", "E-commerce", 10);
    addProject("P001", "Analisis Data", 6);

    removeProject("P001", "Aplikasi Mobile");

    displayData();
    return 0;
}

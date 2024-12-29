#include <iostream>
#include <string>
using namespace std;

struct Project{
    string name;
    int duration;
    Project* next;

    Project(string n, int d) : name(n), duration(d), next(nullptr) {}
};

struct Employee {
    string name;
    string id;
    Project* projects;
    Employee* next;

    Employee(string n, string i) : name(n), id(i), projects(nullptr), next(nullptr) {}
};

// Kelas untuk mengelola sistem pegawai dan proyek
class EmployeeSystem {
private:
    Employee* head;

public:
    EmployeeSystem() : head(nullptr) {}

    void addEmployee(string name, string id) {
        Employee* newEmployee = new Employee(name, id);
        if (!head) {
            head = newEmployee;
        } else {
            Employee* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newEmployee;
        }
    }

    void addProject(string employeeId, string projectName, int duration) {
        Employee* emp = findEmployee(employeeId);
        if (emp) {
            Project* newProject = new Project(projectName, duration);
            if (!emp->projects) {
                emp->projects = newProject;
            } else {
                Project* current = emp->projects;
                while (current->next) {
                    current = current->next;
                }
                current->next = newProject;
            }
        }
    }

    void removeProject(string employeeId, string projectName) {
        Employee* emp = findEmployee(employeeId);
        if (emp && emp->projects) {
            Project* current = emp->projects;
            Project* prev = nullptr;

            while (current && current->name != projectName) {
                prev = current;
                current = current->next;
            }

            if (current) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    emp->projects = current->next;
                }
                delete current;
            }
        }
    }

    Employee* findEmployee(string id) {
        Employee* current = head;
        while (current && current->id != id) {
            current = current->next;
        }
        return current;
    }

    void displayAll() {
        Employee* current = head;
        while (current) {
            cout << "Pegawai: " << current->name << " (ID: " << current->id << ")" << endl;
            Project* proj = current->projects;
            while (proj) {
                cout << "  - Proyek: " << proj->name << " (" << proj->duration << " bulan)" << endl;
                proj = proj->next;
            }
            cout << endl;
            current = current->next;
        }
    }
};

int main(){
    cout << "=== Sistem Manajemen Pegawai dan Proyek ===" << endl;
    EmployeeSystem empSystem;
    empSystem.addEmployee("Andi", "P001");
    empSystem.addEmployee("Budi", "P002");
    empSystem.addEmployee("Andi", "P003");

    // Menambah proyek
    empSystem.addProject("P001", "Aplikasi Mobile", 12);
    empSystem.addProject("P002", "Sistem Akuntansi", 8);
    empSystem.addProject("P003", "E-commerce", 10);
    empSystem.addProject("P001", "Analisis Data", 6);

     // Menghapus proyek
    empSystem.removeProject("P001", "Aplikasi Mobile");

    // Menampilkan data
    empSystem.displayAll();

    return 0;
}

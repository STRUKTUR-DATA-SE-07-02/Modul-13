#include <iostream>
#include <string>
using namespace std;

struct Project {
    string projectName;
    int duration;
    Project* next;
};

struct Employee {
    string employeeName;
    string employeeID;
    Project* projectHead;
    Employee* next;
};

class MultiLinkedList {
private:
    Employee* head;

    Employee* findEmployee(const string& employeeID) {
        Employee* current = head;
        while (current != nullptr && current->employeeID != employeeID) {
            current = current->next;
        }
        return current;
    }

    void deleteProjects(Project* projectHead) {
        while (projectHead != nullptr) {
            Project* temp = projectHead;
            projectHead = projectHead->next;
            delete temp;
        }
    }

public:
    MultiLinkedList() : head(nullptr) {}

    ~MultiLinkedList() {
        while (head != nullptr) {
            Employee* temp = head;
            head = head->next;
            deleteProjects(temp->projectHead);
            delete temp;
        }
    }

    void addEmployee(const string& name, const string& id) {
        Employee* newEmployee = new Employee{name, id, nullptr, nullptr};
        if (head == nullptr) {
            head = newEmployee;
        } else {
            Employee* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newEmployee;
        }
    }

    void addProject(const string& employeeID, const string& projectName, int duration) {
        Employee* employee = findEmployee(employeeID);
        if (employee == nullptr) return;

        Project* newProject = new Project{projectName, duration, employee->projectHead};
        employee->projectHead = newProject;
    }

    void removeProject(const string& employeeID, const string& projectName) {
        Employee* employee = findEmployee(employeeID);
        if (employee == nullptr) return;

        Project* current = employee->projectHead;
        Project* previous = nullptr;

        while (current != nullptr && current->projectName != projectName) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous == nullptr) {
                employee->projectHead = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
        }
    }

    void display() {
        Employee* current = head;
        while (current != nullptr) {
            cout << "Nama Pegawai: " << current->employeeName << ", ID Pegawai: " << current->employeeID << endl;
            Project* project = current->projectHead;
            while (project != nullptr) {
                cout << "    Nama Proyek: " << project->projectName << ", Durasi: " << project->duration << " bulan" << endl;
                project = project->next;
            }
            current = current->next;
        }
    }
};

int main() {
    MultiLinkedList mll;

    // Masukkan data pegawai
    mll.addEmployee("Andi", "P001");
    mll.addEmployee("Budi", "P002");
    mll.addEmployee("Citra", "P003");

    // Tambahkan proyek ke pegawai
    mll.addProject("P001", "Aplikasi Mobile", 12);
    mll.addProject("P002", "Sistem Akuntansi", 8);
    mll.addProject("P003", "E-commerce", 10);

    // Tambahkan proyek baru
    mll.addProject("P001", "Analisis Data", 6);

    // Hapus proyek "Aplikasi Mobile" dari Andi
    mll.removeProject("P001", "Aplikasi Mobile");

    // Tampilkan data pegawai dan proyek mereka
    mll.display();

    return 0;
}

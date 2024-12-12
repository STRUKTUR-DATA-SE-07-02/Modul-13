#include <iostream>
#include <string>
using namespace std;

// Struktur untuk proyek
struct Project {
    string projectName;
    int duration; // dalam bulan
    Project* next;

    Project(string name, int dur) : projectName(name), duration(dur), next(nullptr) {}
};

// Struktur untuk pegawai
struct Employee {
    string name;
    string id;
    Project* projectHead; // Head pointer untuk proyek
    Employee* next;

    Employee(string empName, string empId) : name(empName), id(empId), projectHead(nullptr), next(nullptr) {}
};

// Tambahkan pegawai ke linked list pegawai
void addEmployee(Employee*& head, string name, string id) {
    Employee* newEmployee = new Employee(name, id);
    if (!head) {
        head = newEmployee;
        return;
    }
    Employee* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newEmployee;
}

// Tambahkan proyek ke pegawai tertentu
void addProject(Employee* employee, string projectName, int duration) {
    if (!employee) return;
    Project* newProject = new Project(projectName, duration);
    if (!employee->projectHead) {
        employee->projectHead = newProject;
        return;
    }
    Project* temp = employee->projectHead;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newProject;
}

// Hapus proyek dari pegawai tertentu
void removeProject(Employee* employee, string projectName) {
    if (!employee || !employee->projectHead) return;

    Project* temp = employee->projectHead;
    Project* prev = nullptr;

    // Jika proyek pertama yang harus dihapus
    if (temp->projectName == projectName) {
        employee->projectHead = temp->next;
        delete temp;
        return;
    }

    // Cari proyek yang sesuai
    while (temp && temp->projectName != projectName) {
        prev = temp;
        temp = temp->next;
    }

    // Jika proyek ditemukan
    if (temp) {
        prev->next = temp->next;
        delete temp;
    }
}

// Tampilkan data pegawai dan proyek
void displayEmployees(Employee* head) {
    Employee* temp = head;
    while (temp) {
        cout << "Pegawai: " << temp->name << " (ID: " << temp->id << ")\n";
        Project* projectTemp = temp->projectHead;
        while (projectTemp) {
            cout << "  - Proyek: " << projectTemp->projectName << ", Durasi: " << projectTemp->duration << " bulan\n";
            projectTemp = projectTemp->next;
        }
        temp = temp->next;
        cout << endl;
    }
}

int main() {
    Employee* employeeHead = nullptr;

    // 1. Masukkan data pegawai
    addEmployee(employeeHead, "Andi", "P001");
    addEmployee(employeeHead, "Budi", "P002");
    addEmployee(employeeHead, "Citra", "P003");

    // 2. Tambahkan proyek ke pegawai
    addProject(employeeHead, "Aplikasi Mobile", 12); // Proyek untuk Andi
    addProject(employeeHead->next, "Sistem Akuntansi", 8); // Proyek untuk Budi
    addProject(employeeHead->next->next, "E-commerce", 10); // Proyek untuk Citra

    // 3. Tambahkan proyek baru
    addProject(employeeHead, "Analisis Data", 6); // Proyek baru untuk Andi

    // 4. Hapus proyek "Aplikasi Mobile" dari Andi
    removeProject(employeeHead, "Aplikasi Mobile");

    // 5. Tampilkan data pegawai dan proyek mereka
    displayEmployees(employeeHead);

    return 0;
}

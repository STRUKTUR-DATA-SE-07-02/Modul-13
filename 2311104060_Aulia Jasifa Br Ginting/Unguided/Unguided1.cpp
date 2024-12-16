#include <iostream>
#include <string>
using namespace std;

// Struktur untuk Proyek
struct Project {
    string nama;
    int durasi;
    Project* nextProject;
    Project(string n, int d) : nama(n), durasi(d), nextProject(nullptr) {}
};

// Struktur untuk Pegawai
struct Employee {
    string nama;
    string id;
    Project* projects;
    Employee* nextEmployee;

    Employee(string n, string i) : nama(n), id(i), projects(nullptr), nextEmployee(nullptr) {}
};

// Kelas Manajemen Pegawai dan Proyek
class EmployeeProjectManagement {
private:
    Employee* head;

public:
    EmployeeProjectManagement() : head(nullptr) {}

    // Tambah Pegawai Baru
    void tambahPegawai(string nama, string id) {
        Employee* newEmployee = new Employee(nama, id);
        if (!head) {
            head = newEmployee;
        } else {
            Employee* temp = head;
            while (temp->nextEmployee) {
                temp = temp->nextEmployee;
            }
            temp->nextEmployee = newEmployee;
        }
    }

    // Tambah Proyek ke Pegawai
    void tambahProyek(string namaEmployee, string namaProyek, int durasi) {
        Employee* employee = cariPegawai(namaEmployee);
        if (employee) {
            Project* newProject = new Project(namaProyek, durasi);
            if (!employee->projects) {
                employee->projects = newProject;
            } else {
                Project* temp = employee->projects;
                while (temp->nextProject) {
                    temp = temp->nextProject;
                }
                temp->nextProject = newProject;
            }
        }
    }

    // Cari Pegawai berdasarkan Nama
    Employee* cariPegawai(string nama) {
        Employee* temp = head;
        while (temp) {
            if (temp->nama == nama) {
                return temp;
            }
            temp = temp->nextEmployee;
        }
        return nullptr;
    }

    // Hapus Proyek dari Pegawai
    void hapusProyek(string namaEmployee, string namaProyek) {
        Employee* employee = cariPegawai(namaEmployee);
        if (employee) {
            Project* current = employee->projects;
            Project* prev = nullptr;

            while (current) {
                if (current->nama == namaProyek) {
                    if (prev) {
                        prev->nextProject = current->nextProject;
                    } else {
                        employee->projects = current->nextProject;
                    }
                    delete current;
                    return;
                }
                prev = current;
                current = current->nextProject;
            }
        }
    }

    // Tampilkan Data Pegawai dan Proyek
    void tampilkanData() {
        Employee* employeeTemp = head;
        while (employeeTemp) {
            cout << "Pegawai: " << employeeTemp->nama << " (ID: " << employeeTemp->id << ")" << endl;
            
            Project* projectTemp = employeeTemp->projects;
            if (!projectTemp) {
                cout << "  Tidak memiliki proyek" << endl;
            } else {
                cout << "  Proyek:" << endl;
                while (projectTemp) {
                    cout << "  - " << projectTemp->nama << " (Durasi: " << projectTemp->durasi << " bulan)" << endl;
                    projectTemp = projectTemp->nextProject;
                }
            }
            cout << endl;
            employeeTemp = employeeTemp->nextEmployee;
        }
    }

    // Destruktor untuk membebaskan memori
    ~EmployeeProjectManagement() {
        while (head) {
            Employee* empTemp = head;
            head = head->nextEmployee;

            // Hapus semua proyek pegawai
            while (empTemp->projects) {
                Project* projTemp = empTemp->projects;
                empTemp->projects = empTemp->projects->nextProject;
                delete projTemp;
            }

            delete empTemp;
        }
    }
};

int main() {
    EmployeeProjectManagement manajemen;

    // 1. Masukkan data pegawai
    manajemen.tambahPegawai("Andi", "P001");
    manajemen.tambahPegawai("Budi", "P002");
    manajemen.tambahPegawai("Citra", "P003");

    // 2. Tambahkan proyek ke pegawai
    manajemen.tambahProyek("Andi", "Aplikasi Mobile", 12);
    manajemen.tambahProyek("Budi", "Sistem Akuntansi", 8);
    manajemen.tambahProyek("Citra", "E-commerce", 10);

    // 3. Tambahkan proyek baru untuk Andi
    manajemen.tambahProyek("Andi", "Analisis Data", 6);

    // 4. Hapus proyek "Aplikasi Mobile" dari Andi
    manajemen.hapusProyek("Andi", "Aplikasi Mobile");

    // 5. Tampilkan data pegawai dan proyek
    manajemen.tampilkanData();

    return 0;
}
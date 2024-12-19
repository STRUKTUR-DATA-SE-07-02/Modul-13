#include <iostream>
#include <string>
using namespace std;

// Struktur untuk proyek
struct Project
{
    string name;
    int duration;
    Project *next;
};

// Struktur untuk pegawai
struct Employee
{
    string name;
    string id;
    Project *firstProject;
    Employee *next;
};

class EmployeeManagement
{
private:
    Employee *head;

public:
    EmployeeManagement()
    {
        head = NULL;
    }

    // Fungsi untuk menambah pegawai baru
    void addEmployee(string name, string id)
    {
        Employee *newEmployee = new Employee;
        newEmployee->name = name;
        newEmployee->id = id;
        newEmployee->firstProject = NULL;
        newEmployee->next = NULL;

        if (head == NULL)
        {
            head = newEmployee;
        }
        else
        {
            Employee *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newEmployee;
        }
    }

    // Fungsi untuk menambah proyek ke pegawai
    void addProject(string employeeId, string projectName, int duration)
    {
        Employee *emp = findEmployee(employeeId);
        if (emp != NULL)
        {
            Project *newProject = new Project;
            newProject->name = projectName;
            newProject->duration = duration;
            newProject->next = NULL;

            if (emp->firstProject == NULL)
            {
                emp->firstProject = newProject;
            }
            else
            {
                Project *current = emp->firstProject;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newProject;
            }
        }
    }

    // Fungsi untuk mencari pegawai berdasarkan ID
    Employee *findEmployee(string id)
    {
        Employee *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    // Fungsi untuk menghapus proyek
    void deleteProject(string employeeId, string projectName)
    {
        Employee *emp = findEmployee(employeeId);
        if (emp != NULL && emp->firstProject != NULL)
        {
            Project *current = emp->firstProject;
            Project *prev = NULL;

            // Jika proyek yang akan dihapus ada di awal
            if (current->name == projectName)
            {
                emp->firstProject = current->next;
                delete current;
                return;
            }

            // Mencari proyek yang akan dihapus
            while (current != NULL && current->name != projectName)
            {
                prev = current;
                current = current->next;
            }

            // Jika proyek ditemukan
            if (current != NULL)
            {
                prev->next = current->next;
                delete current;
            }
        }
    }

    // Fungsi untuk menampilkan semua data
    void displayAll()
    {
        Employee *currentEmp = head;
        while (currentEmp != NULL)
        {
            cout << "\nPegawai: " << currentEmp->name << " (ID: " << currentEmp->id << ")" << endl;
            cout << "Proyek yang dikelola:" << endl;

            Project *currentProj = currentEmp->firstProject;
            if (currentProj == NULL)
            {
                cout << "- Tidak ada proyek" << endl;
            }
            while (currentProj != NULL)
            {
                cout << "- " << currentProj->name << " (" << currentProj->duration << " bulan)" << endl;
                currentProj = currentProj->next;
            }
            currentEmp = currentEmp->next;
        }
    }
};

int main()
{
    EmployeeManagement em;

    // 1. Menambahkan pegawai
    em.addEmployee("Andi", "P001");
    em.addEmployee("Budi", "P002");
    em.addEmployee("Citra", "P003");

    // 2. Menambahkan proyek ke pegawai
    em.addProject("P001", "Aplikasi Mobile", 12);
    em.addProject("P002", "Sistem Akuntansi", 8);
    em.addProject("P003", "E-commerce", 10);

    // 3. Menambahkan proyek baru untuk Andi
    em.addProject("P001", "Analisis Data", 6);

    cout << "Data sebelum menghapus proyek:" << endl;
    em.displayAll();

    // 4. Menghapus proyek "Aplikasi Mobile" dari Andi
    em.deleteProject("P001", "Aplikasi Mobile");

    cout << "\n\nData setelah menghapus proyek:" << endl;
    em.displayAll();

    return 0;
}

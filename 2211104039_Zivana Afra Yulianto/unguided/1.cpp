#include <iostream>
#include <string>

using namespace std;

// Struktur untuk node proyek
struct ProjectNode
{
    string projectName; // Nama proyek
    int duration;       // Durasi proyek (bulan)
    ProjectNode *next;  // Pointer ke proyek berikutnya

    ProjectNode(string name, int dur) : projectName(name), duration(dur), next(nullptr) {}
};

// Struktur untuk node pegawai
struct EmployeeNode
{
    string employeeName;   // Nama pegawai
    string employeeID;     // ID pegawai
    EmployeeNode *next;    // Pointer ke pegawai berikutnya
    ProjectNode *projects; // Pointer ke daftar proyek

    EmployeeNode(string name, string id) : employeeName(name), employeeID(id), next(nullptr), projects(nullptr) {}
};

// Kelas untuk mengelola Multi Linked List Pegawai dan Proyek
class EmployeeProjectList
{
private:
    EmployeeNode *head; // Pointer ke kepala daftar pegawai

public:
    EmployeeProjectList() : head(nullptr) {}

    // Menambahkan pegawai baru
    void addEmployee(string name, string id)
    {
        EmployeeNode *newEmployee = new EmployeeNode(name, id);
        newEmployee->next = head;
        head = newEmployee;
    }

    // Menambahkan proyek ke pegawai tertentu
    void addProject(string employeeID, string projectName, int duration)
    {
        EmployeeNode *employee = head;
        while (employee != nullptr && employee->employeeID != employeeID)
        {
            employee = employee->next;
        }

        if (employee != nullptr)
        { // Jika pegawai ditemukan
            ProjectNode *newProject = new ProjectNode(projectName, duration);
            newProject->next = employee->projects;
            employee->projects = newProject;
        }
        else
        {
            cout << "Employee not found!" << endl;
        }
    }

    // Menghapus proyek dari pegawai tertentu
    void deleteProject(string employeeID, string projectName)
    {
        EmployeeNode *employee = head;
        while (employee != nullptr && employee->employeeID != employeeID)
        {
            employee = employee->next;
        }

        if (employee != nullptr)
        { // Jika pegawai ditemukan
            ProjectNode **current = &(employee->projects);
            while (*current != nullptr && (*current)->projectName != projectName)
            {
                current = &((*current)->next);
            }

            if (*current != nullptr)
            { // Jika proyek ditemukan
                ProjectNode *toDelete = *current;
                *current = (*current)->next;
                delete toDelete;
                cout << "Project " << projectName << " deleted from " << employee->employeeName << "." << endl;
            }
            else
            {
                cout << "Project not found!" << endl;
            }
        }
        else
        {
            cout << "Employee not found!" << endl;
        }
    }

    // Menampilkan daftar pegawai dan proyek mereka
    void display()
    {
        EmployeeNode *current = head;
        while (current != nullptr)
        {
            cout << "Employee: " << current->employeeName << " (ID: " << current->employeeID << ")\nProjects: ";
            ProjectNode *project = current->projects;
            if (project == nullptr)
            {
                cout << "No projects assigned.";
            }
            else
            {
                while (project != nullptr)
                {
                    cout << project->projectName << " (" << project->duration << " months) ";
                    project = project->next;
                }
            }
            cout << "\n";
            current = current->next;
        }
    }

    ~EmployeeProjectList()
    {
        while (head != nullptr)
        {
            EmployeeNode *temp = head;
            head = head->next;

            while (temp->projects != nullptr)
            {
                ProjectNode *projectTemp = temp->projects;
                temp->projects = temp->projects->next;
                delete projectTemp;
            }
            delete temp;
        }
    }
};

int main()
{
    EmployeeProjectList empList;

    // Menambahkan data pegawai
    empList.addEmployee("Andi", "P001");
    empList.addEmployee("Budi", "P002");
    empList.addEmployee("Citra", "P003");

    // Menambahkan proyek ke pegawai
    empList.addProject("P001", "Aplikasi Mobile", 12);
    empList.addProject("P002", "Sistem Akuntansi", 8);
    empList.addProject("P003", "E-commerce", 10);

    // Menambahkan proyek baru
    empList.addProject("P001", "Analisis Data", 6);

    // Menghapus proyek dari pegawai
    empList.deleteProject("P001", "Aplikasi Mobile");

    // Menampilkan data pegawai dan proyek mereka
    cout << "\nData Pegawai dan Proyek:\n";
    empList.display();

    return 0;
}

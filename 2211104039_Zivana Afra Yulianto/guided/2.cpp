#include <iostream>
#include <string>

using namespace std;

// Struktur EmployeeNode untuk menyimpan nama karyawan, pointer ke node berikutnya, dan pointer ke subordinate
struct EmployeeNode
{
    string name;
    EmployeeNode *next;
    EmployeeNode *subordinate;

    // Constructor untuk inisialisasi node karyawan
    EmployeeNode(string empName) : name(empName), next(nullptr), subordinate(nullptr) {}
};

// Kelas EmployeeList untuk mengelola struktur hirarki karyawan
class EmployeeList
{
private:
    EmployeeNode *head; // Pointer ke head list

public:
    // Constructor untuk menginisialisasi list kosong
    EmployeeList() : head(nullptr) {}

    // Menambahkan karyawan baru ke awal list
    void addEmployee(string name)
    {
        EmployeeNode *newEmployee = new EmployeeNode(name);
        newEmployee->next = head;
        head = newEmployee;
    }

    // Menambahkan subordinate ke karyawan yang sesuai
    void addSubordinate(string managerName, string subordinateName)
    {
        EmployeeNode *manager = head;

        // Mencari manager berdasarkan nama
        while (manager != nullptr && manager->name != managerName)
        {
            manager = manager->next;
        }

        // Jika manager ditemukan, tambahkan subordinate
        if (manager != nullptr)
        {
            EmployeeNode *newSubordinate = new EmployeeNode(subordinateName);
            newSubordinate->next = manager->subordinate;
            manager->subordinate = newSubordinate;
        }
        else
        {
            cout << "Manager not found!" << endl;
        }
    }

    // Menampilkan semua manager beserta subordinate-nya
    void display()
    {
        EmployeeNode *current = head;

        while (current != nullptr)
        {
            cout << "Manager: " << current->name << " -> ";

            EmployeeNode *sub = current->subordinate;
            while (sub != nullptr)
            {
                cout << sub->name << " ";
                sub = sub->next;
            }

            cout << endl;
            current = current->next;
        }
    }

    // Destructor untuk membersihkan semua node
    ~EmployeeList()
    {
        while (head != nullptr)
        {
            EmployeeNode *temp = head;
            head = head->next;

            // Hapus semua subordinate dari manager
            while (temp->subordinate != nullptr)
            {
                EmployeeNode *subTemp = temp->subordinate;
                temp->subordinate = temp->subordinate->next;
                delete subTemp;
            }

            // Hapus manager
            delete temp;
        }
    }
};

// Fungsi utama untuk menguji EmployeeList
int main()
{
    EmployeeList empList;

    // Menambahkan manager
    empList.addEmployee("Alice");
    empList.addEmployee("Bob");
    empList.addEmployee("Charlie");

    // Menambahkan subordinate ke manager yang sesuai
    empList.addSubordinate("Alice", "David");
    empList.addSubordinate("Alice", "Eve");
    empList.addSubordinate("Bob", "Frank");
    empList.addSubordinate("Charlie", "Frans");
    empList.addSubordinate("Charlie", "Brian");

    // Menampilkan hasil
    empList.display();

    return 0;
}

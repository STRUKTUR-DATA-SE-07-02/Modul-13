#include <iostream>
#include <string>

using namespace std;


struct Node {
    int data;
    Node* next;
    Node* child;

    Node(int val) : data(val), next(nullptr), child(nullptr) {}
};


class MultiLinkedList {
private:
    Node* head;

public:
    MultiLinkedList() : head(nullptr) {}


    void addParent(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }


    void addChild(int parentData, int childData) {
        Node* parent = head;
        while (parent != nullptr && parent->data != parentData) {
            parent = parent->next;
        }
        if (parent != nullptr) {
            Node* newChild = new Node(childData);
            newChild->next = parent->child;
            parent->child = newChild;
        } else {
            cout << "Parent not found!" << endl;
        }
    }


    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Parent: " << current->data << " -> ";
            Node* child = current->child;
            while (child != nullptr) {
                cout << child->data << " ";
                child = child->next;
            }
            cout << endl;
            current = current->next;
        }
    }

    ~MultiLinkedList() {

        while (head != nullptr) {
            Node* temp = head;
            head = head->next;


            while (temp->child != nullptr) {
                Node* childTemp = temp->child;
                temp->child = temp->child->next;
                delete childTemp;
            }
            delete temp;
        }
    }
};

int main() {
    MultiLinkedList mList;

    mList.addParent(1);
    mList.addParent(2);
    mList.addParent(3);

    mList.addChild(1, 10);
    mList.addChild(1, 11);
    mList.addChild(2, 20);
    mList.addChild(2, 20);
    mList.addChild(3, 30);
    mList.addChild(3, 30);
    mList.display();

    return 0;
}


//#include <iostream>
//#include <string>
//
//using namespace std;
//
//
//struct EmployeeNode {
//    string name;
//    EmployeeNode* next;
//    EmployeeNode* subordinate;
//
//    EmployeeNode(string empName) : name(empName), next(nullptr), subordinate(nullptr) {}
//};
//
//
//class EmployeeList {
//private:
//    EmployeeNode* head;
//
//public:
//    EmployeeList() : head(nullptr) {}
//
//
//    void addEmployee(string name) {
//        EmployeeNode* newEmployee = new EmployeeNode(name);
//        newEmployee->next = head;
//        head = newEmployee;
//    }
//
//
//    void addSubordinate(string managerName, string subordinateName) {
//        EmployeeNode* manager = head;
//        while (manager != nullptr && manager->name != managerName) {
//            manager = manager->next;
//        }
//        if (manager != nullptr) {
//            EmployeeNode* newSubordinate = new EmployeeNode(subordinateName);
//            newSubordinate->next = manager->subordinate;
//            manager->subordinate = newSubordinate;
//        } else {
//            cout << "Manager not found!" << endl;
//        }
//    }
//
//
//    void display() {
//        EmployeeNode* current = head;
//        while (current != nullptr) {
//            cout << "Manager: " << current->name << " -> ";
//            EmployeeNode* sub = current->subordinate;
//            while (sub != nullptr) {
//                cout << sub->name << " ";
//                sub = sub->next;
//            }
//            cout << endl;
//            current = current->next;
//        }
//    }
//
//    ~EmployeeList() {
//
//        while (head != nullptr) {
//            EmployeeNode* temp = head;
//            head = head->next;
//
//
//            while (temp->subordinate != nullptr) {
//                EmployeeNode* subTemp = temp->subordinate;
//                temp->subordinate = temp->subordinate->next;
//                delete subTemp;
//            }
//            delete temp;
//        }
//    }
//};
//
//int main() {
//    EmployeeList empList;
//
//    empList.addEmployee("Alice");
//    empList.addEmployee("Bob");
//    empList.addEmployee("Charlie");
//
//    empList.addSubordinate("Alice", "David");
//    empList.addSubordinate("Alice", "Eve");
//    empList.addSubordinate("Bob", "Frank");
//
//    empList.addSubordinate("Charlie", "Frans");
//    empList.addSubordinate("Charlie", "Brian");
//
//    empList.display();
//
//    return 0;
//}

//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// Struktur untuk node karyawan
//struct EmployeeNode {
//    string name; // Nama karyawan
//    EmployeeNode* next; // Pointer ke karyawan berikutnya
//    EmployeeNode* subordinate; // Pointer ke subordinate pertama
//
//    EmployeeNode(string empName) : name(empName), next(nullptr), subordinate(nullptr) {}
//};
//
//// Kelas untuk Multi-Linked List Karyawan
//class EmployeeList {
//private:
//    EmployeeNode* head; // Pointer ke kepala list
//
//public:
//    EmployeeList() : head(nullptr) {}
//
//    // Menambahkan karyawan (induk)
//    void addEmployee(string name) {
//        EmployeeNode* newEmployee = new EmployeeNode(name);
//        newEmployee->next = head; // Menyambungkan ke karyawan sebelumnya
//        head = newEmployee; // Memperbarui head
//    }
//
//    // Menambahkan subordinate ke karyawan tertentu
//    void addSubordinate(string managerName, string subordinateName) {
//        EmployeeNode* manager = head;
//        while (manager != nullptr && manager->name != managerName) {
//            manager = manager->next;
//        }
//        if (manager != nullptr) { // Jika manajer ditemukan
//            EmployeeNode* newSubordinate = new EmployeeNode(subordinateName);
//            newSubordinate->next = manager->subordinate; // Menyambungkan ke subordinate sebelumnya
//            manager->subordinate = newSubordinate; // Memperbarui subordinate
//        } else {
//            cout << "Manager not found!" << endl;
//        }
//    }
//
//    // Menghapus karyawan (induk)
//    void deleteEmployee(string name) {
//        EmployeeNode** current = &head;
//        while (*current != nullptr && (*current)->name != name) {
//            current = &((*current)->next);
//        }
//
//        if (*current != nullptr) { // Jika karyawan ditemukan
//            EmployeeNode* toDelete = *current;
//            *current = (*current)->next;
//
//            // Hapus semua subordinate dari node ini
//            while (toDelete->subordinate != nullptr) {
//                EmployeeNode* subTemp = toDelete->subordinate;
//                toDelete->subordinate = toDelete->subordinate->next;
//                delete subTemp;
//            }
//            delete toDelete;
//            cout << "Employee " << name << " deleted." << endl;
//        } else {
//            cout << "Employee not found!" << endl;
//        }
//    }
//
//    // Menghapus subordinate dari karyawan tertentu
//    void deleteSubordinate(string managerName, string subordinateName) {
//        EmployeeNode* manager = head;
//        while (manager != nullptr && manager->name != managerName) {
//            manager = manager->next;
//        }
//
//        if (manager != nullptr) { // Jika manajer ditemukan
//            EmployeeNode** currentSub = &(manager->subordinate);
//            while (*currentSub != nullptr && (*currentSub)->name != subordinateName) {
//                currentSub = &((*currentSub)->next);
//            }
//
//            if (*currentSub != nullptr) { // Jika subordinate ditemukan
//                EmployeeNode* toDelete = *currentSub;
//                *currentSub = (*currentSub)->next; // Menghapus dari list
//
//                delete toDelete; // Menghapus node subordinate
//                cout << "Subordinate " << subordinateName << " deleted from " << managerName << "." << endl;
//            } else {
//                cout << "Subordinate not found!" << endl;
//            }
//        } else {
//            cout << "Manager not found!" << endl;
//        }
//    }
//
//    // Menampilkan daftar karyawan dan subordinate mereka
//    void display() {
//        EmployeeNode* current = head;
//        while (current != nullptr) {
//            cout << "Manager: " << current->name << " -> ";
//            EmployeeNode* sub = current->subordinate;
//            while (sub != nullptr) {
//                cout << sub->name << " ";
//                sub = sub->next;
//            }
//            cout << endl;
//            current = current->next;
//        }
//    }
//
//    ~EmployeeList() {
//        // Destructor untuk membersihkan memori
//        while (head != nullptr) {
//            EmployeeNode* temp = head;
//            head = head->next;
//
//            // Hapus semua subordinate dari node ini
//            while (temp->subordinate != nullptr) {
//                EmployeeNode* subTemp = temp->subordinate;
//                temp->subordinate = temp->subordinate->next;
//                delete subTemp;
//            }
//            delete temp;
//        }
//    }
//};
//
//int main() {
//    EmployeeList empList;
//
//    empList.addEmployee("Alice");
//    empList.addEmployee("Bob");
//    empList.addEmployee("Charlie");
//
//    empList.addSubordinate("Alice", "David");
//    empList.addSubordinate("Alice", "Eve");
//    empList.addSubordinate("Bob", "Frank");
//
//    cout << "Initial employee list:" << endl;
//    empList.display(); // Menampilkan isi daftar karyawan
//
//    empList.deleteSubordinate("Alice", "David"); // Menghapus David dari Alice
//    empList.deleteEmployee("Charlie"); // Menghapus Charlie
//
//    cout << "\nUpdated employee list:" << endl;
//    empList.display(); // Menampilkan isi daftar setelah penghapusan
//
//    return 0;
//}

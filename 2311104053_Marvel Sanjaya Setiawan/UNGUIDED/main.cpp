//#include <iostream>
//#include <iomanip>
//#include <string>
//using namespace std;
//
//// Struktur untuk Proyek
//struct Project {
//    string projectName;
//    int duration;
//    Project* nextProject;
//};
//
//// Struktur untuk Pegawai
//struct Employee {
//    string employeeName;
//    string employeeID;
//    Project* projectHead;
//    Employee* nextEmployee;
//};
//
//// Fungsi untuk membuat pegawai baru
//Employee* createEmployee(string name, string id) {
//    Employee* newEmployee = new Employee;
//    newEmployee->employeeName = name;
//    newEmployee->employeeID = id;
//    newEmployee->projectHead = nullptr;
//    newEmployee->nextEmployee = nullptr;
//    return newEmployee;
//}
//
//// Fungsi untuk membuat proyek baru
//Project* createProject(string name, int duration) {
//    Project* newProject = new Project;
//    newProject->projectName = name;
//    newProject->duration = duration;
//    newProject->nextProject = nullptr;
//    return newProject;
//}
//
//// Menambahkan proyek ke pegawai
//void addProject(Employee* employee, string projectName, int duration) {
//    Project* newProject = createProject(projectName, duration);
//    if (employee->projectHead == nullptr) {
//        employee->projectHead = newProject;
//    } else {
//        Project* temp = employee->projectHead;
//        while (temp->nextProject != nullptr) {
//            temp = temp->nextProject;
//        }
//        temp->nextProject = newProject;
//    }
//}
//
//// Menghapus proyek berdasarkan nama
//void removeProject(Employee* employee, string projectName) {
//    Project* temp = employee->projectHead;
//    Project* prev = nullptr;
//
//    while (temp != nullptr && temp->projectName != projectName) {
//        prev = temp;
//        temp = temp->nextProject;
//    }
//
//    if (temp == nullptr) {
//        cout << "Proyek tidak ditemukan.\n";
//        return;
//    }
//
//    if (prev == nullptr) {
//        employee->projectHead = temp->nextProject;
//    } else {
//        prev->nextProject = temp->nextProject;
//    }
//
//    delete temp;
//    cout << "Proyek " << projectName << " berhasil dihapus.\n";
//}
//
//// Menampilkan data pegawai dan proyek mereka dalam bentuk tabel
//void displayEmployees(Employee* head) {
//    cout << left << setw(15) << "Nama Pegawai" << setw(10) << "ID" << "Proyek dan Durasi\n";
//    cout << "---------------------------------------------\n";
//    Employee* tempEmployee = head;
//    while (tempEmployee != nullptr) {
//        cout << left << setw(15) << tempEmployee->employeeName << setw(10) << tempEmployee->employeeID;
//        Project* tempProject = tempEmployee->projectHead;
//        if (tempProject == nullptr) {
//            cout << "-\n";
//        } else {
//            cout << "- " << tempProject->projectName << " (" << tempProject->duration << " bulan)\n";
//            tempProject = tempProject->nextProject;
//            while (tempProject != nullptr) {
//                cout << setw(25) << "" << "- " << tempProject->projectName << " (" << tempProject->duration << " bulan)\n";
//                tempProject = tempProject->nextProject;
//            }
//        }
//        tempEmployee = tempEmployee->nextEmployee;
//    }
//    cout << endl;
//}
//
//// Fungsi untuk menambahkan pegawai ke daftar
//void addEmployee(Employee*& head, string name, string id) {
//    Employee* newEmployee = createEmployee(name, id);
//    if (head == nullptr) {
//        head = newEmployee;
//    } else {
//        Employee* temp = head;
//        while (temp->nextEmployee != nullptr) {
//            temp = temp->nextEmployee;
//        }
//        temp->nextEmployee = newEmployee;
//    }
//}
//
//int main() {
//    Employee* head = nullptr;
//
//    int choice;
//    string name, id, projectName;
//    int duration;
//
//    do {
//        cout << "Sistem Manajemen Data Proyek dan Pegawai:\n";
//        cout << "1. Tambahkan Pegawai\n";
//        cout << "2. Tambahkan Proyek ke Pegawai\n";
//        cout << "3. Tambahkan Proyek Baru\n";
//        cout << "4. Hapus Proyek\n";
//        cout << "5. Tampilkan Data Pegawai\n";
//        cout << "6. Keluar\n";
//        cout << "Pilih opsi: ";
//        cin >> choice;
//
//        switch (choice) {
//            case 1:
//                int numEmployees;
//                cout << "Masukkan jumlah pegawai yang ingin ditambahkan: ";
//                cin >> numEmployees;
//                for (int i = 0; i < numEmployees; i++) {
//                    cout << "Masukkan Nama Pegawai: ";
//                    cin.ignore();
//                    getline(cin, name);
//                    cout << "Masukkan ID Pegawai: ";
//                    cin >> id;
//                    addEmployee(head, name, id);
//                }
//                break;
//
//            case 2:
//                cout << "Masukkan ID Pegawai: ";
//                cin >> id;
//                cout << "Masukkan Nama Proyek: ";
//                cin.ignore();
//                getline(cin, projectName);
//                cout << "Masukkan Durasi Proyek (bulan): ";
//                cin >> duration;
//                {
//                    Employee* temp = head;
//                    while (temp != nullptr && temp->employeeID != id) {
//                        temp = temp->nextEmployee;
//                    }
//                    if (temp != nullptr) {
//                        addProject(temp, projectName, duration);
//                    } else {
//                        cout << "Pegawai dengan ID " << id << " tidak ditemukan.\n";
//                    }
//                }
//                break;
//
//            case 3:
//                cout << "Masukkan Nama Pegawai: ";
//                cin.ignore();
//                getline(cin, name);
//                cout << "Masukkan Nama Proyek: ";
//                getline(cin, projectName);
//                cout << "Masukkan Durasi Proyek (bulan): ";
//                cin >> duration;
//                {
//                    Employee* temp = head;
//                    while (temp != nullptr && temp->employeeName != name) {
//                        temp = temp->nextEmployee;
//                    }
//                    if (temp != nullptr) {
//                        addProject(temp, projectName, duration);
//                        cout << "Proyek " << projectName << " berhasil ditambahkan ke pegawai dengan nama " << name << ".\n";
//                    } else {
//                        cout << "Pegawai dengan nama " << name << " tidak ditemukan.\n";
//                    }
//                }
//                break;
//
//            case 4:
//                cout << "Masukkan ID Pegawai: ";
//                cin >> id;
//                cout << "Masukkan Nama Proyek yang akan dihapus: ";
//                cin.ignore();
//                getline(cin, projectName);
//                {
//                    Employee* temp = head;
//                    while (temp != nullptr && temp->employeeID != id) {
//                        temp = temp->nextEmployee;
//                    }
//                    if (temp != nullptr) {
//                        removeProject(temp, projectName);
//                    } else {
//                        cout << "Pegawai dengan ID " << id << " tidak ditemukan.\n";
//                    }
//                }
//                break;
//
//            case 5:
//                displayEmployees(head);
//                break;
//
//            case 6:
//                cout << "Keluar dari program.\n";
//                break;
//
//            default:
//                cout << "Pilihan tidak valid.\n";
//        }
//    } while (choice != 6);
//
//    return 0;
//}

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Struktur untuk Buku
struct Book {
    string title;
    string returnDate;
    Book* nextBook;
};

// Struktur untuk Anggota
struct Member {
    string memberName;
    string memberID;
    Book* bookHead;
    Member* nextMember;
};

// Fungsi untuk membuat anggota baru
Member* createMember(string name, string id) {
    Member* newMember = new Member;
    newMember->memberName = name;
    newMember->memberID = id;
    newMember->bookHead = nullptr;
    newMember->nextMember = nullptr;
    return newMember;
}

// Fungsi untuk membuat buku baru
Book* createBook(string title, string returnDate) {
    Book* newBook = new Book;
    newBook->title = title;
    newBook->returnDate = returnDate;
    newBook->nextBook = nullptr;
    return newBook;
}

// Menambahkan buku ke anggota
void addBook(Member* member, string title, string returnDate) {
    Book* newBook = createBook(title, returnDate);
    if (member->bookHead == nullptr) {
        member->bookHead = newBook;
    } else {
        Book* temp = member->bookHead;
        while (temp->nextBook != nullptr) {
            temp = temp->nextBook;
        }
        temp->nextBook = newBook;
    }
}

// Menghapus anggota beserta buku yang dipinjam
void removeMember(Member*& head, string id) {
    Member* temp = head;
    Member* prev = nullptr;

    while (temp != nullptr && temp->memberID != id) {
        prev = temp;
        temp = temp->nextMember;
    }

    if (temp == nullptr) {
        cout << "Anggota dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->nextMember;
    } else {
        prev->nextMember = temp->nextMember;
    }

    // Hapus semua buku yang dipinjam anggota
    Book* bookTemp = temp->bookHead;
    while (bookTemp != nullptr) {
        Book* toDelete = bookTemp;
        bookTemp = bookTemp->nextBook;
        delete toDelete;
    }

    delete temp;
    cout << "Anggota dengan ID " << id << " beserta buku yang dipinjam berhasil dihapus.\n";
}

// Menampilkan data anggota dan buku yang dipinjam
void displayMembers(Member* head) {
    Member* tempMember = head;
    int bookNumber = 1;
    while (tempMember != nullptr) {
        Book* tempBook = tempMember->bookHead;
        while (tempBook != nullptr) {
            cout << "- Buku " << bookNumber << ": Judul = \"" << tempBook->title << "\", Pengembalian = \"" << tempBook->returnDate << "\" (Untuk " << tempMember->memberName << ").\n";
            tempBook = tempBook->nextBook;
            bookNumber++;
        }
        tempMember = tempMember->nextMember;
    }
}

int main() {
    Member* head = nullptr;

    // Menambahkan data anggota
    head = createMember("Rani", "A001");
    head->nextMember = createMember("Dito", "A002");
    head->nextMember->nextMember = createMember("Vina", "A003");

    cout << "Data Awal Anggota Perpustakaan:\n\n";
    cout << "Anggota 1: Nama = \"Rani\", ID = \"A001\".\n";
    cout << "Anggota 2: Nama = \"Dito\", ID = \"A002\".\n";
    cout << "Anggota 3: Nama = \"Vina\", ID = \"A003\".\n\n";

    cout << "Setelah menambahkan buku yang dipinjam:\n\n";

    // Menambahkan buku yang dipinjam
    addBook(head, "Pemrograman C++", "01/12/2024");
    addBook(head->nextMember, "Algoritma Pemrograman", "15/12/2024");
    displayMembers(head);

    // Menambahkan buku baru untuk Rani
    cout << "\nSetelah menambahkan buku baru:\n\n";
    addBook(head, "Struktur Data", "10/12/2024");
    displayMembers(head);

    // Menghapus anggota Dito beserta buku yang dipinjam
    cout << "\nSetelah menghapus anggota Dito:\n\n";
    removeMember(head, "A002");
    displayMembers(head);

    return 0;
}

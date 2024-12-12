#include <iostream>
#include <string>
using namespace std;

// Struktur untuk buku
struct Book {
    string title;
    string returnDate; // Tanggal pengembalian
    Book* next;

    Book(string t, string rd) : title(t), returnDate(rd), next(nullptr) {}
};

// Struktur untuk anggota
struct Member {
    string name;
    string id;
    Book* bookHead; // Head pointer untuk buku
    Member* next;

    Member(string mName, string mId) : name(mName), id(mId), bookHead(nullptr), next(nullptr) {}
};

// Tambahkan anggota ke linked list anggota
void addMember(Member*& head, string name, string id) {
    Member* newMember = new Member(name, id);
    if (!head) {
        head = newMember;
        return;
    }
    Member* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newMember;
}

// Tambahkan buku ke anggota tertentu
void addBook(Member* member, string title, string returnDate) {
    if (!member) return;
    Book* newBook = new Book(title, returnDate);
    if (!member->bookHead) {
        member->bookHead = newBook;
        return;
    }
    Book* temp = member->bookHead;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newBook;
}

// Hapus anggota beserta buku yang dipinjam
void removeMember(Member*& head, string memberId) {
    if (!head) return;

    Member* temp = head;
    Member* prev = nullptr;

    // Jika anggota pertama yang harus dihapus
    if (temp->id == memberId) {
        head = temp->next;

        // Hapus semua buku yang dipinjam anggota
        while (temp->bookHead) {
            Book* bookTemp = temp->bookHead;
            temp->bookHead = bookTemp->next;
            delete bookTemp;
        }
        delete temp;
        return;
    }

    // Cari anggota yang sesuai
    while (temp && temp->id != memberId) {
        prev = temp;
        temp = temp->next;
    }

    // Jika anggota ditemukan
    if (temp) {
        prev->next = temp->next;

        // Hapus semua buku yang dipinjam anggota
        while (temp->bookHead) {
            Book* bookTemp = temp->bookHead;
            temp->bookHead = bookTemp->next;
            delete bookTemp;
        }
        delete temp;
    }
}

// Tampilkan data anggota dan buku yang dipinjam
void displayMembers(Member* head) {
    Member* temp = head;
    while (temp) {
        cout << "Anggota: " << temp->name << " (ID: " << temp->id << ")\n";
        Book* bookTemp = temp->bookHead;
        while (bookTemp) {
            cout << "  - Buku: " << bookTemp->title << ", Tanggal Pengembalian: " << bookTemp->returnDate << "\n";
            bookTemp = bookTemp->next;
        }
        temp = temp->next;
        cout << endl;
    }
}

int main() {
    Member* memberHead = nullptr;

    // 1. Masukkan data anggota
    addMember(memberHead, "Rani", "A001");
    addMember(memberHead, "Dito", "A002");
    addMember(memberHead, "Vina", "A003");

    // 2. Tambahkan buku yang dipinjam
    addBook(memberHead, "Pemrograman C++", "01/12/2024"); // Buku untuk Rani
    addBook(memberHead->next, "Algoritma Pemrograman", "15/12/2024"); // Buku untuk Dito

    // 3. Tambahkan buku baru
    addBook(memberHead, "Struktur Data", "10/12/2024"); // Buku baru untuk Rani

    // 4. Hapus anggota Dito beserta buku yang dipinjam
    removeMember(memberHead, "A002");

    // 5. Tampilkan seluruh data anggota dan buku yang dipinjam
    displayMembers(memberHead);

    return 0;
}

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
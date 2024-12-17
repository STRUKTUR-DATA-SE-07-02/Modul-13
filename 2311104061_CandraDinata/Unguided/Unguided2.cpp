#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Book {
    string title;
    string returnDate;
    Book* nextBook;
};
struct Member {
    string memberName;
    string memberID;
    Book* bookHead;
    Member* nextMember;
};
Member* createMember(string name, string id) {
    Member* newMember = new Member;
    newMember->memberName = name;
    newMember->memberID = id;
    newMember->bookHead = nullptr;
    newMember->nextMember = nullptr;
    return newMember;
}
Book* createBook(string title, string returnDate) {
    Book* newBook = new Book;
    newBook->title = title;
    newBook->returnDate = returnDate;
    newBook->nextBook = nullptr;
    return newBook;
}
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
    Book* bookTemp = temp->bookHead;
    while (bookTemp != nullptr) {
        Book* toDelete = bookTemp;
        bookTemp = bookTemp->nextBook;
        delete toDelete;
    }
    delete temp;
    cout << "Anggota dengan ID " << id << " Beserta buku yang dipinjam berhasil dihapus.\n";
}

void displayMembers(Member* head) {
    Member* tempMember = head;
    int memberNumber = 1;
    while (tempMember != nullptr) {
        cout << "Anggota " << memberNumber << ": Nama = \"" << tempMember->memberName << "\", ID = \"" << tempMember->memberID << "\".\n";
        Book* tempBook = tempMember->bookHead;
        int bookNumber = 1;
        while (tempBook != nullptr) {
            cout << "  - Buku " << bookNumber << ": Judul = \"" << tempBook->title << "\", Pengembalian = \"" << tempBook->returnDate << "\".\n";
            tempBook = tempBook->nextBook;
            bookNumber++;
        }
        tempMember = tempMember->nextMember;
        memberNumber++;
    }
}

int main() {
    Member* head = nullptr;

    head = createMember("Rani", "A001");
    head->nextMember = createMember("Dito", "A002");
    head->nextMember->nextMember = createMember("Vina", "A003");

    cout << "Data Awal Anggota Perpustakaan:\n\n";
    cout << "Anggota 1: Nama = \"Rani\", ID = \"A001\".\n";
    cout << "Anggota 2: Nama = \"Dito\", ID = \"A002\".\n";
    cout << "Anggota 3: Nama = \"Vina\", ID = \"A003\".\n\n";
    cout << "Setelah menambahkan buku yang dipinjam:\n\n";
    addBook(head, "Pemrograman C++", "01/12/2024");
    addBook(head->nextMember, "Algoritma Pemrograman", "15/12/2024");
    displayMembers(head);
    cout << "\nSetelah menambahkan buku baru:\n\n";
    addBook(head, "Struktur Data", "10/12/2024");
    displayMembers(head);
    cout << "\nSetelah menghapus anggota Dito:\n\n";
    removeMember(head, "A002");
    displayMembers(head);
    return 0;
}
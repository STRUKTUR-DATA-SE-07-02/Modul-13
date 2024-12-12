#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string returnDate;
    Book* next;
};

struct Member {
    string name;
    string id;
    Book* books;
    Member* next;
};

Member* memberHead = nullptr;

void addMember(string name, string id) {
    Member* newMember = new Member{name, id, nullptr, memberHead};
    memberHead = newMember;
}

void addBook(string memberId, string bookTitle, string returnDate) {
    Member* temp = memberHead;
    while (temp && temp->id != memberId) {
        temp = temp->next;
    }
    if (temp) {
        Book* newBook = new Book{bookTitle, returnDate, temp->books};
        temp->books = newBook;
    }
}

void removeMember(string memberId) {
    Member* curr = memberHead;
    Member* prev = nullptr;
    while (curr && curr->id != memberId) {
        prev = curr;
        curr = curr->next;
    }
    if (curr) {
        if (prev) {
            prev->next = curr->next;
        } else {
            memberHead = curr->next;
        }
        while (curr->books) {
            Book* toDelete = curr->books;
            curr->books = curr->books->next;
            delete toDelete;
        }
        delete curr;
    }
}

void displayMembers() {
    Member* member = memberHead;
    while (member) {
        cout << "Anggota: " << member->name << " (" << member->id << ")\\n";
        Book* book = member->books;
        while (book) {
            cout << "  - Buku: " << book->title << " (Kembali: " << book->returnDate << ")\\n";
            book = book->next;
        }
        member = member->next;
    }
}

int main() {
    addMember("Rani", "A001");
    addMember("Dito", "A002");
    addMember("Vina", "A003");

    addBook("A001", "Pemrograman C++", "01/12/2024");
    addBook("A002", "Algoritma Pemrograman", "15/12/2024");
    addBook("A001", "Struktur Data", "10/12/2024");

    removeMember("A002");

    displayMembers();
    return 0;
}

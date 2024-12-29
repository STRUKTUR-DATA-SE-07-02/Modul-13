#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string returnDate;
    Book* next;

    Book(string t, string rd) : title(t), returnDate(rd), next(nullptr) {}
};

struct Member {
    string name;
    string id;
    Book* books;
    Member* next;

    Member(string n, string i) : name(n), id(i), books(nullptr), next(nullptr) {}
};

class LibrarySystem {
private:
    Member* head;

public:
    LibrarySystem() : head(nullptr) {}

    void addMember(string name, string id) {
        Member* newMember = new Member(name, id);
        if (!head) {
            head = newMember;
        } else {
            Member* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newMember;
        }
    }

    void addBook(string memberId, string title, string returnDate) {
        Member* mem = findMember(memberId);
        if (mem) {
            Book* newBook = new Book(title, returnDate);
            if (!mem->books) {
                mem->books = newBook;
            } else {
                Book* current = mem->books;
                while (current->next) {
                    current = current->next;
                }
                current->next = newBook;
            }
        }
    }

    void removeMember(string id) {
        if (!head) return;

        if (head->id == id) {
            Member* temp = head;
            head = head->next;
            deleteBooks(temp->books);
            delete temp;
            return;
        }

        Member* current = head;
        while (current->next && current->next->id != id) {
            current = current->next;
        }

        if (current->next) {
            Member* temp = current->next;
            current->next = temp->next;
            deleteBooks(temp->books);
            delete temp;
        }
    }

    void deleteBooks(Book* book) {
        while (book) {
            Book* temp = book;
            book = book->next;
            delete temp;
        }
    }

    Member* findMember(string id) {
        Member* current = head;
        while (current && current->id != id) {
            current = current->next;
        }
        return current;
    }

    void displayAll() {
        Member* current = head;
        while (current) {
            cout << "Anggota: " << current->name << " (ID: " << current->id << ")" << endl;
            Book* book = current->books;
            while (book) {
                cout << "  - Buku: " << book->title << " (Kembali: " << book->returnDate << ")" << endl;
                book = book->next;
            }
            cout << endl;
            current = current->next;
        }
    }
};

int main() {
    cout << "\n=== Sistem Manajemen Perpustakaan ===" << endl;
    LibrarySystem libSystem;

    libSystem.addMember("Rani", "A001");
    libSystem.addMember("Dito", "A002");
    libSystem.addMember("Vina", "A003");

    libSystem.addBook("A001", "Pemrograman C++", "01/12/2024");
    libSystem.addBook("A002", "Algoritma Pemrograman", "15/12/2024");
    libSystem.addBook("A001", "Struktur Data", "10/12/2024");

    libSystem.removeMember("A002");

    libSystem.displayAll();

    return 0;
}

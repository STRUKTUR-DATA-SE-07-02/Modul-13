#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string returnDate;
    Book* next;
};

struct Member {
    string memberName;
    string memberID;
    Book* bookHead;
    Member* next;
};

class MultiLinkedList {
private:
    Member* head;

    Member* findMember(const string& memberID) {
        Member* current = head;
        while (current != nullptr && current->memberID != memberID) {
            current = current->next;
        }
        return current;
    }

    void deleteBooks(Book* bookHead) {
        while (bookHead != nullptr) {
            Book* temp = bookHead;
            bookHead = bookHead->next;
            delete temp;
        }
    }

    tm stringToDate(const string& dateStr) {
        tm tmDate = {};
        stringstream ss(dateStr);
        ss >> get_time(&tmDate, "%d/%m/%Y");
        return tmDate;
    }

    bool compareDates(const string& date1, const string& date2) {
        tm tmDate1 = stringToDate(date1);
        tm tmDate2 = stringToDate(date2);
        return mktime(&tmDate1) < mktime(&tmDate2);
    }

    void sortedInsert(Book*& head, Book* newBook) {
        if (head == nullptr || compareDates(newBook->returnDate, head->returnDate)) {
            newBook->next = head;
            head = newBook;
        } else {
            Book* current = head;
            while (current->next != nullptr && !compareDates(newBook->returnDate, current->next->returnDate)) {
                current = current->next;
            }
            newBook->next = current->next;
            current->next = newBook;
        }
    }

public:
    MultiLinkedList() : head(nullptr) {}

    ~MultiLinkedList() {
        while (head != nullptr) {
            Member* temp = head;
            head = head->next;
            deleteBooks(temp->bookHead);
            delete temp;
        }
    }

    void addMember(const string& name, const string& id) {
        Member* newMember = new Member{name, id, nullptr, nullptr};
        if (head == nullptr) {
            head = newMember;
        } else {
            Member* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newMember;
        }
    }

    void addBook(const string& memberID, const string& title, const string& returnDate) {
        Member* member = findMember(memberID);
        if (member == nullptr) return;

        Book* newBook = new Book{title, returnDate, nullptr};
        sortedInsert(member->bookHead, newBook);
    }

    void removeMember(const string& memberID) {
        Member* current = head;
        Member* previous = nullptr;

        while (current != nullptr && current->memberID != memberID) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            deleteBooks(current->bookHead);
            delete current;
        }
    }

    void display() {
        Member* current = head;
        while (current != nullptr) {
            cout << "Nama Anggota: " << current->memberName << ", ID Anggota: " << current->memberID << endl;
            Book* book = current->bookHead;
            while (book != nullptr) {
                cout << "    Judul Buku: " << book->title << ", Tanggal Pengembalian: " << book->returnDate << endl;
                book = book->next;
            }
            current = current->next;
        }
    }
};

int main() {
    MultiLinkedList mll;

    // Masukkan data anggota
    mll.addMember("Rani", "A001");
    mll.addMember("Dito", "A002");
    mll.addMember("Vina", "A003");

    // Tambahkan buku yang dipinjam
    mll.addBook("A001", "Pemrograman C++", "01/12/2024");
    mll.addBook("A002", "Algoritma Pemrograman", "15/12/2024");

    // Tambahkan buku baru
    mll.addBook("A001", "Struktur Data", "10/12/2024");

    // Hapus anggota Dito beserta buku yang dipinjam
    mll.removeMember("A002");

    // Tampilkan seluruh data anggota dan buku yang dipinjam
    mll.display();

    return 0;
}

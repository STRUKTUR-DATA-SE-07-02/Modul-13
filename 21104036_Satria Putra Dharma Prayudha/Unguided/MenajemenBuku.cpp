#include <iostream>
#include <string>

using namespace std;

struct BookNode {
    string bookTitle;
    string returnDate;
    BookNode* next;

    BookNode(string title, string date) : bookTitle(title), returnDate(date), next(nullptr) {}
};

struct MemberNode {
    string memberName;
    string memberID;
    MemberNode* next;
    BookNode* bookHead;

    MemberNode(string name, string id) : memberName(name), memberID(id), next(nullptr), bookHead(nullptr) {}
};

class LibraryManagement {
private:
    MemberNode* head;

public:
    LibraryManagement() : head(nullptr) {}

    void addMember(string name, string id) {
        MemberNode* newMember = new MemberNode(name, id);
        newMember->next = head;
        head = newMember;
    }

    void addBook(string memberID, string bookTitle, string returnDate) {
        MemberNode* member = head;
        while (member != nullptr && member->memberID != memberID) {
            member = member->next;
        }
        if (member != nullptr) {
            BookNode* newBook = new BookNode(bookTitle, returnDate);
            newBook->next = member->bookHead;
            member->bookHead = newBook;
        } else {
            cout << "Member not found!" << endl;
        }
    }

    void deleteMember(string memberID) {
        MemberNode** current = &head;
        while (*current != nullptr && (*current)->memberID != memberID) {
            current = &((*current)->next);
        }
        if (*current != nullptr) {
            MemberNode* toDelete = *current;
            *current = (*current)->next;
            while (toDelete->bookHead != nullptr) {
                BookNode* bookTemp = toDelete->bookHead;
                toDelete->bookHead = toDelete->bookHead->next;
                delete bookTemp;
            }
            delete toDelete;
            cout << "Member " << memberID << " deleted." << endl;
        } else {
            cout << "Member not found!" << endl;
        }
    }

    void display() {
        MemberNode* current = head;
        while (current != nullptr) {
            cout << "Member: " << current->memberName << " (ID: " << current->memberID << ") -> ";
            BookNode* book = current->bookHead;
            while (book != nullptr) {
                cout << "[" << book->bookTitle << ", Return: " << book->returnDate << "] ";
                book = book->next;
            }
            cout << endl;
            current = current->next;
        }
    }

    ~LibraryManagement() {
        while (head != nullptr) {
            MemberNode* temp = head;
            head = head->next;
            while (temp->bookHead != nullptr) {
                BookNode* bookTemp = temp->bookHead;
                temp->bookHead = temp->bookHead->next;
                delete bookTemp;
            }
            delete temp;
        }
    }
};

int main() {
    LibraryManagement libMgmt;

    libMgmt.addMember("Rani", "A001");
    libMgmt.addMember("Dito", "A002");
    libMgmt.addMember("Vina", "A003");

    cout << "Before adding any books:" << endl;
    libMgmt.display();

    libMgmt.addBook("A001", "Pemrograman C++", "01/12/2024");
    libMgmt.addBook("A002", "Algoritma Pemrograman", "15/12/2024");

    cout << "\nBefore adding new book:" << endl;
    libMgmt.display();

    libMgmt.addBook("A001", "Struktur Data", "10/12/2024");

    cout << "\nAfter adding new book:" << endl;
    libMgmt.display();

    libMgmt.deleteMember("A002");

    cout << "\nAfter deleting a member:" << endl;
    libMgmt.display();

    return 0;
}
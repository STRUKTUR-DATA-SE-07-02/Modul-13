#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string returnDate;
    Book* nextBook;
};

struct Member {
    string name;
    string id;
    Book* bookHead;
    Member* nextMember;
};

// Head of the Member List
Member* memberHead = nullptr;

// Function to create a new member node
Member* createMember(string name, string id) {
    Member* newMember = new Member;
    newMember->name = name;
    newMember->id = id;
    newMember->bookHead = nullptr;
    newMember->nextMember = nullptr;
    return newMember;
}

// Function to create a new book node
Book* createBook(string title, string returnDate) {
    Book* newBook = new Book;
    newBook->title = title;
    newBook->returnDate = returnDate;
    newBook->nextBook = nullptr;
    return newBook;
}

// Function to add a member to the list
void addMember(string name, string id) {
    Member* newMember = createMember(name, id);
    if (memberHead == nullptr) {
        memberHead = newMember;
    } else {
        Member* temp = memberHead;
        while (temp->nextMember != nullptr) {
            temp = temp->nextMember;
        }
        temp->nextMember = newMember;
    }
    cout << "Member : " << name << " with ID : " << id << " added.\n";
}

// Function to add a book to a member
void addBookToMember(string memberId, string title, string returnDate) {
    Member* temp = memberHead;
    while (temp != nullptr && temp->id != memberId) {
        temp = temp->nextMember;
    }

    if (temp == nullptr) {
        cout << "Member with ID " << memberId << " not found.\n";
        return;
    }

    Book* newBook = createBook(title, returnDate);
    if (temp->bookHead == nullptr) {
        temp->bookHead = newBook;
    } else {
        Book* bTemp = temp->bookHead;
        while (bTemp->nextBook != nullptr) {
            bTemp = bTemp->nextBook;
        }
        bTemp->nextBook = newBook;
    }
    cout << "Book : " << title << " with return date : " << returnDate << " added to member : " << temp->name << ".\n";
}

// Function to delete a member and all their books
void deleteMember(string memberId) {
    Member* temp = memberHead;
    Member* prev = nullptr;

    while (temp != nullptr && temp->id != memberId) {
        prev = temp;
        temp = temp->nextMember;
    }

    if (temp == nullptr) {
        cout << "Member with ID " << memberId << " not found.\n";
        return;
    }

    if (prev == nullptr) {
        memberHead = temp->nextMember;
    } else {
        prev->nextMember = temp->nextMember;
    }

    // Delete all books of the member
    Book* bTemp = temp->bookHead;
    while (bTemp != nullptr) {
        Book* toDelete = bTemp;
        bTemp = bTemp->nextBook;
        delete toDelete;
    }

    delete temp;
    cout << "Member with ID : " << memberId << " deleted.\n";
}

// Function to display all members and their books
void displayMembers() {
    Member* temp = memberHead;
    while (temp != nullptr) {
        cout << "Member Name: " << temp->name << ", ID: " << temp->id << "\n";
        Book* bTemp = temp->bookHead;
        while (bTemp != nullptr) {
            cout << "  Book Title: " << bTemp->title << ", Return Date: " << bTemp->returnDate << "\n";
            bTemp = bTemp->nextBook;
        }
        temp = temp->nextMember;
        cout << "\n";
    }
}

int main() {
    // Adding members
    addMember("Rani", "A001");
    addMember("Dito", "A002");
    addMember("Vina", "A003");
    cout << "\n";
    displayMembers();
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Adding books to members
    addBookToMember("A001", "Pemrograman C++", "01/12/2024");
    addBookToMember("A002", "Algoritma Pemrograman", "15/12/2024");
    cout << "\n";
    displayMembers();
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Adding a new book to Rani
    addBookToMember("A001", "Struktur Data", "10/12/2024");
    cout << "\n";
    displayMembers();
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Deleting member Dito
    deleteMember("A002");
    cout << "\n";
    displayMembers();

    return 0;
}
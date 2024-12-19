#include <iostream>
#include <string>
using namespace std;

struct Book
{
    string title;
    string returnDate;
    Book *nextBook;
};

struct Member
{
    string name;
    string id;
    Book *borrowedBooks;
    Member *nextMember;
};

void addMember(Member *&head, const string &name, const string &id)
{
    Member *newMember = new Member{name, id, nullptr, nullptr};
    if (!head)
    {
        head = newMember;
    }
    else
    {
        Member *temp = head;
        while (temp->nextMember)
        {
            temp = temp->nextMember;
        }
        temp->nextMember = newMember;
    }
}

void addBook(Member *head, const string &memberId, const string &title, const string &returnDate)
{
    Member *temp = head;
    while (temp)
    {
        if (temp->id == memberId)
        {
            Book *newBook = new Book{title, returnDate, nullptr};
            if (!temp->borrowedBooks)
            {
                temp->borrowedBooks = newBook;
            }
            else
            {
                Book *bookTemp = temp->borrowedBooks;
                while (bookTemp->nextBook)
                {
                    bookTemp = bookTemp->nextBook;
                }
                bookTemp->nextBook = newBook;
            }
            return;
        }
        temp = temp->nextMember;
    }
    cout << "Member with ID " << memberId << " not found.\n";
}

void removeMember(Member *&head, const string &memberId)
{
    Member *temp = head;
    Member *prev = nullptr;

    while (temp)
    {
        if (temp->id == memberId)
        {
            if (prev)
            {
                prev->nextMember = temp->nextMember;
            }
            else
            {
                head = temp->nextMember;
            }

            Book *bookTemp = temp->borrowedBooks;
            while (bookTemp)
            {
                Book *toDelete = bookTemp;
                bookTemp = bookTemp->nextBook;
                delete toDelete;
            }

            delete temp;
            cout << "Member with ID " << memberId << " has been removed.\n";
            return;
        }
        prev = temp;
        temp = temp->nextMember;
    }
    cout << "Member with ID " << memberId << " not found.\n";
}

void displayAllMembers(Member *head)
{
    Member *temp = head;
    while (temp)
    {
        cout << "Name: " << temp->name << ", ID: " << temp->id << "\n";
        Book *bookTemp = temp->borrowedBooks;
        while (bookTemp)
        {
            cout << "  Book Title: " << bookTemp->title << ", Return Date: " << bookTemp->returnDate << "\n";
            bookTemp = bookTemp->nextBook;
        }
        temp = temp->nextMember;
        cout << "-----------------------\n";
    }
}

int main()
{
    Member *library = nullptr;

    // 1. Masukkan data anggota
    addMember(library, "Rani", "A001");
    addMember(library, "Dito", "A002");
    addMember(library, "Vina", "A003");

    // 2. Tambahkan buku yang dipinjam
    addBook(library, "A001", "Pemrograman C++", "01/12/2024");
    addBook(library, "A002", "Algoritma Pemrograman", "15/12/2024");

    // 3. Tambahkan buku baru
    addBook(library, "A001", "Struktur Data", "10/12/2024");

    // 4. Hapus anggota Dito beserta buku yang dipinjam
    removeMember(library, "A002");

    // 5. Tampilkan seluruh data anggota dan buku yang dipinjam
    displayAllMembers(library);

    return 0;
}
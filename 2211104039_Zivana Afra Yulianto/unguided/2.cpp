#include <iostream>
#include <string>
using namespace std;

// Struktur untuk data buku
struct Book
{
    string title;
    string returnDate;
    Book *nextBook;

    Book(string t, string r) : title(t), returnDate(r), nextBook(nullptr) {}
};

// Struktur untuk data anggota
struct Member
{
    string name;
    string id;
    Book *borrowedBooks;
    Member *nextMember;

    Member(string n, string i) : name(n), id(i), borrowedBooks(nullptr), nextMember(nullptr) {}
};

// Kelas untuk mengelola sistem perpustakaan
class Library
{
private:
    Member *head;

public:
    Library() : head(nullptr) {}

    // Menambahkan anggota baru
    void addMember(string name, string id)
    {
        Member *newMember = new Member(name, id);
        newMember->nextMember = head;
        head = newMember;
    }

    // Menambahkan buku ke anggota tertentu
    void addBook(string memberId, string title, string returnDate)
    {
        Member *member = findMember(memberId);
        if (member)
        {
            Book *newBook = new Book(title, returnDate);
            newBook->nextBook = member->borrowedBooks;
            member->borrowedBooks = newBook;
        }
        else
        {
            cout << "Anggota dengan ID " << memberId << " tidak ditemukan!\n";
        }
    }

    // Menghapus anggota beserta buku yang dipinjam
    void deleteMember(string memberId)
    {
        Member *current = head;
        Member *previous = nullptr;

        while (current && current->id != memberId)
        {
            previous = current;
            current = current->nextMember;
        }

        if (!current)
        {
            cout << "Anggota dengan ID " << memberId << " tidak ditemukan!\n";
            return;
        }

        // Hapus semua buku yang dipinjam oleh anggota
        Book *book = current->borrowedBooks;
        while (book)
        {
            Book *temp = book;
            book = book->nextBook;
            delete temp;
        }

        // Hapus anggota dari daftar
        if (previous)
        {
            previous->nextMember = current->nextMember;
        }
        else
        {
            head = current->nextMember;
        }

        delete current;
        cout << "Anggota dengan ID " << memberId << " berhasil dihapus.\n";
    }

    // Menampilkan data anggota dan buku yang dipinjam
    void displayData()
    {
        Member *current = head;
        while (current)
        {
            cout << "Nama: " << current->name << ", ID: " << current->id << "\n";
            Book *book = current->borrowedBooks;
            while (book)
            {
                cout << "  - Judul Buku: " << book->title << ", Tanggal Pengembalian: " << book->returnDate << "\n";
                book = book->nextBook;
            }
            current = current->nextMember;
        }
    }

private:
    // Mencari anggota berdasarkan ID
    Member *findMember(string memberId)
    {
        Member *current = head;
        while (current)
        {
            if (current->id == memberId)
            {
                return current;
            }
            current = current->nextMember;
        }
        return nullptr;
    }
};

int main()
{
    Library library;

    // Menambahkan data anggota
    library.addMember("Rani", "A001");
    library.addMember("Dito", "A002");
    library.addMember("Vina", "A003");

    // Menambahkan buku yang dipinjam
    library.addBook("A001", "Pemrograman C++", "01/12/2024");
    library.addBook("A002", "Algoritma Pemrograman", "15/12/2024");

    // Menambahkan buku baru untuk Rani
    library.addBook("A001", "Struktur Data", "10/12/2024");

    // Menghapus anggota Dito beserta buku yang dipinjam
    library.deleteMember("A002");

    // Menampilkan seluruh data anggota dan buku yang dipinjam
    cout << "\nData Anggota dan Buku yang Dipinjam:\n";
    library.displayData();

    return 0;
}

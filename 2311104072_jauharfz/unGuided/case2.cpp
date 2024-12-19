#include <iostream>
#include <string>
using namespace std;

// Struktur untuk buku
struct Book
{
    string title;
    string returnDate;
    Book *next;
};

// Struktur untuk anggota
struct Member
{
    string name;
    string id;
    Book *firstBook;
    Member *next;
};

class LibraryManagement
{
private:
    Member *head;

public:
    LibraryManagement()
    {
        head = NULL;
    }

    // Fungsi untuk menambah anggota baru
    void addMember(string name, string id)
    {
        Member *newMember = new Member;
        newMember->name = name;
        newMember->id = id;
        newMember->firstBook = NULL;
        newMember->next = NULL;

        if (head == NULL)
        {
            head = newMember;
        }
        else
        {
            Member *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newMember;
        }
    }

    // Fungsi untuk menambah buku ke anggota
    void addBook(string memberId, string bookTitle, string returnDate)
    {
        Member *member = findMember(memberId);
        if (member != NULL)
        {
            Book *newBook = new Book;
            newBook->title = bookTitle;
            newBook->returnDate = returnDate;
            newBook->next = NULL;

            if (member->firstBook == NULL)
            {
                member->firstBook = newBook;
            }
            else
            {
                Book *current = member->firstBook;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newBook;
            }
        }
    }

    // Fungsi untuk mencari anggota berdasarkan ID
    Member *findMember(string id)
    {
        Member *current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    // Fungsi untuk menghapus anggota beserta bukunya
    void deleteMember(string id)
    {
        if (head == NULL)
            return;

        Member *current = head;
        Member *prev = NULL;

        // Jika anggota yang akan dihapus ada di awal
        if (current != NULL && current->id == id)
        {
            head = current->next;
            // Hapus semua buku
            while (current->firstBook != NULL)
            {
                Book *temp = current->firstBook;
                current->firstBook = current->firstBook->next;
                delete temp;
            }
            delete current;
            return;
        }

        // Mencari anggota yang akan dihapus
        while (current != NULL && current->id != id)
        {
            prev = current;
            current = current->next;
        }

        // Jika anggota ditemukan
        if (current != NULL)
        {
            prev->next = current->next;
            // Hapus semua buku
            while (current->firstBook != NULL)
            {
                Book *temp = current->firstBook;
                current->firstBook = current->firstBook->next;
                delete temp;
            }
            delete current;
        }
    }

    // Fungsi untuk menampilkan semua data
    void displayAll()
    {
        Member *currentMember = head;
        while (currentMember != NULL)
        {
            cout << "\nAnggota: " << currentMember->name << " (ID: " << currentMember->id << ")" << endl;
            cout << "Buku yang dipinjam:" << endl;

            Book *currentBook = currentMember->firstBook;
            if (currentBook == NULL)
            {
                cout << "- Tidak ada buku yang dipinjam" << endl;
            }
            while (currentBook != NULL)
            {
                cout << "- " << currentBook->title << " (Pengembalian: " << currentBook->returnDate << ")" << endl;
                currentBook = currentBook->next;
            }
            currentMember = currentMember->next;
        }
    }
};

int main()
{
    LibraryManagement lm;

    // 1. Menambahkan anggota
    lm.addMember("Rani", "A001");
    lm.addMember("Dito", "A002");
    lm.addMember("Vina", "A003");

    // 2. Menambahkan buku yang dipinjam
    lm.addBook("A001", "Pemrograman C++", "01/12/2024");
    lm.addBook("A002", "Algoritma Pemrograman", "15/12/2024");

    // 3. Menambahkan buku baru untuk Rani
    lm.addBook("A001", "Struktur Data", "10/12/2024");

    cout << "Data sebelum menghapus anggota Dito:" << endl;
    lm.displayAll();

    // 4. Menghapus anggota Dito beserta buku yang dipinjam
    lm.deleteMember("A002");

    cout << "\n\nData setelah menghapus anggota Dito:" << endl;
    lm.displayAll();

    return 0;
}

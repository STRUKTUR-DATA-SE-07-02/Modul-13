#include <iostream>
#include <string>
using namespace std;

// Struktur untuk Buku
struct Book {
    string judul;
    string tanggalPengembalian;
    Book* nextBook;
    Book(string j, string t) : judul(j), tanggalPengembalian(t), nextBook(nullptr) {}
};

// Struktur untuk Anggota
struct Member {
    string nama;
    string id;
    Book* buku;
    Member* nextMember;

    Member(string n, string i) : nama(n), id(i), buku(nullptr), nextMember(nullptr) {}
};

// Kelas Sistem Manajemen Buku Perpustakaan
class LibraryManagementSystem {
private:
    Member* head;

public:
    LibraryManagementSystem() : head(nullptr) {}

    // Tambah Anggota Baru
    void tambahAnggota(string nama, string id) {
        Member* newMember = new Member(nama, id);
        if (!head) {
            head = newMember;
        } else {
            Member* temp = head;
            while (temp->nextMember) {
                temp = temp->nextMember;
            }
            temp->nextMember = newMember;
        }
    }

    // Tambah Buku ke Anggota
    void tambahBuku(string namaAnggota, string judulBuku, string tanggalPengembalian) {
        Member* member = cariAnggota(namaAnggota);
        if (member) {
            Book* newBook = new Book(judulBuku, tanggalPengembalian);
            if (!member->buku) {
                member->buku = newBook;
            } else {
                Book* temp = member->buku;
                while (temp->nextBook) {
                    temp = temp->nextBook;
                }
                temp->nextBook = newBook;
            }
        }
    }

    // Cari Anggota berdasarkan Nama
    Member* cariAnggota(string nama) {
        Member* temp = head;
        while (temp) {
            if (temp->nama == nama) {
                return temp;
            }
            temp = temp->nextMember;
        }
        return nullptr;
    }

    // Hapus Anggota dan Buku yang Dipinjam
    void hapusAnggota(string nama) {
        Member* prev = nullptr;
        Member* current = head;

        while (current) {
            if (current->nama == nama) {
                // Hapus semua buku yang dipinjam
                while (current->buku) {
                    Book* bookTemp = current->buku;
                    current->buku = current->buku->nextBook;
                    delete bookTemp;
                }

                if (prev) {
                    prev->nextMember = current->nextMember;
                } else {
                    head = current->nextMember;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->nextMember;
        }
    }

    // Tampilkan Data Anggota dan Buku
    void tampilkanData() {
        Member* memberTemp = head;
        while (memberTemp) {
            cout << "Anggota: " << memberTemp->nama << " (ID: " << memberTemp->id << ")" << endl;

            Book* bookTemp = memberTemp->buku;
            if (!bookTemp) {
                cout << "  Tidak ada buku yang dipinjam" << endl;
            } else {
                cout << "  Buku yang dipinjam:" << endl;
                while (bookTemp) {
                    cout << "  - " << bookTemp->judul << " (Tanggal Pengembalian: " << bookTemp->tanggalPengembalian << ")" << endl;
                    bookTemp = bookTemp->nextBook;
                }
            }
            cout << endl;
            memberTemp = memberTemp->nextMember;
        }
    }

    // Destruktor untuk membebaskan memori
    ~LibraryManagementSystem() {
        while (head) {
            Member* memTemp = head;
            head = head->nextMember;

            // Hapus semua buku yang dipinjam anggota
            while (memTemp->buku) {
                Book* bookTemp = memTemp->buku;
                memTemp->buku = memTemp->buku->nextBook;
                delete bookTemp;
            }

            delete memTemp;
        }
    }
};

int main() {
    LibraryManagementSystem perpustakaan;

    // 1. Masukkan data anggota
    perpustakaan.tambahAnggota("Rani", "A001");
    perpustakaan.tambahAnggota("Dito", "A002");
    perpustakaan.tambahAnggota("Vina", "A003");

    // 2. Tambahkan buku yang dipinjam
    perpustakaan.tambahBuku("Rani", "Pemrograman C++", "01/12/2024");
    perpustakaan.tambahBuku("Dito", "Algoritma Pemrograman", "15/12/2024");

    // 3. Tambahkan buku baru
    perpustakaan.tambahBuku("Rani", "Struktur Data", "10/12/2024");

    // 4. Hapus anggota Dito beserta buku yang dipinjam
    perpustakaan.hapusAnggota("Dito");

    // 5. Tampilkan seluruh data anggota dan buku yang dipinjam
    perpustakaan.tampilkanData();

    return 0;
}
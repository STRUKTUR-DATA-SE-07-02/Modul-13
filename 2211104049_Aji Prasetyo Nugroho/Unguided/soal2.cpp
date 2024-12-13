#include <iostream>
#include <string>
#include <list>
using namespace std;

// Struktur data untuk Buku
struct Book {
    string title;
    string returnDate;
};

// Struktur data untuk Anggota
struct Member {
    string name;
    string id;
    list<Book> borrowedBooks;
};

// Fungsi untuk menampilkan data anggota dan buku yang dipinjam
void displayMembers(const list<Member>& members) {
    for (const auto& member : members) {
        cout << "Nama Anggota: " << member.name << ", ID: " << member.id << endl;
        if (!member.borrowedBooks.empty()) {
            cout << "  Buku yang dipinjam:" << endl;
            for (const auto& book : member.borrowedBooks) {
                cout << "    Judul: " << book.title << ", Tanggal Pengembalian: " << book.returnDate << endl;
            }
        } else {
            cout << "  Tidak ada buku yang dipinjam." << endl;
        }
        cout << endl;
    }
}

// Fungsi untuk menghapus anggota beserta buku yang dipinjam
void removeMember(list<Member>& members, const string& memberId) {
    members.remove_if([&](const Member& member) {
        return member.id == memberId;
    });
}

int main() {
    list<Member> members;

    // 1. Tambahkan data anggota
    members.push_back({"Rani", "A001"});
    members.push_back({"Dito", "A002"});
    members.push_back({"Vina", "A003"});

    // 2. Tambahkan buku yang dipinjam
    for (auto& member : members) {
        if (member.id == "A001") {
            member.borrowedBooks.push_back({"Pemrograman C++", "01/12/2024"});
        } else if (member.id == "A002") {
            member.borrowedBooks.push_back({"Algoritma Pemrograman", "15/12/2024"});
        }
    }

    // 3. Tambahkan buku baru untuk Rani
    for (auto& member : members) {
        if (member.id == "A001") {
            member.borrowedBooks.push_back({"Struktur Data", "10/12/2024"});
        }
    }

    // 4. Hapus anggota Dito beserta buku yang dipinjam
    removeMember(members, "A002");

    // 5. Tampilkan seluruh data anggota dan buku yang dipinjam
    displayMembers(members);

    return 0;
}
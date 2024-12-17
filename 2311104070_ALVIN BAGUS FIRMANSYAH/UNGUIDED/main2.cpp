#include <iostream>
#include <string>

using namespace std;

// Struktur untuk menyimpan data buku
struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* next; // pointer ke buku berikutnya
};

// Struktur untuk menyimpan data anggota
struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* listBuku; // list anak untuk buku
    Anggota* next; // pointer ke anggota berikutnya
};

// Fungsi untuk menambahkan buku ke anggota
void tambahBuku(Anggota* anggota, string judulBuku, string tanggalPengembalian) {
    Buku* bukuBaru = new Buku;
    bukuBaru->judulBuku = judulBuku;
    bukuBaru->tanggalPengembalian = tanggalPengembalian;
    bukuBaru->next = nullptr;

    if (anggota->listBuku == nullptr) {
        anggota->listBuku = bukuBaru;
    } else {
        Buku* temp = anggota->listBuku;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = bukuBaru;
    }
}

// Fungsi untuk menghapus anggota beserta buku yang dipinjam
void hapusAnggota(Anggota*& head, string idAnggota) {
    Anggota* current = head;
    Anggota* previous = nullptr;

    while (current != nullptr && current->idAnggota != idAnggota) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        Buku* bukuTemp = current->listBuku;
        while (bukuTemp != nullptr) {
            Buku* bukuHapus = bukuTemp;
            bukuTemp = bukuTemp->next;
            delete bukuHapus;
        }
        delete current;
    }
}

// Fungsi untuk menampilkan data anggota dan buku yang dipinjam
void tampilkanData(Anggota* anggota) {
    while (anggota != nullptr) {
        cout << "Nama Anggota: " << anggota->namaAnggota << ", ID: " << anggota->idAnggota << endl;
        Buku* buku = anggota->listBuku;
        while (buku != nullptr) {
            cout << "\tBuku: " << buku->judulBuku << ", Tanggal Pengembalian: " << buku->tanggalPengembalian << endl;
            buku = buku->next;
        }
        anggota = anggota->next;
    }
}

int main() {
    // Membuat list anggota
    Anggota* head = nullptr;

    // Menambahkan anggota
    Anggota* anggota1 = new Anggota{"Rani", "A001", nullptr, nullptr};
    Anggota* anggota2 = new Anggota{"Dito", "A002", nullptr, nullptr};
    Anggota* anggota3 = new Anggota{"Vina", "A003", nullptr, nullptr};

    head = anggota1;
    anggota1->next = anggota2;
    anggota2->next = anggota3;

    // Menambahkan buku yang dipinjam
    tambahBuku(anggota1, "Pemrograman C++", "01/12/2024");
    tambahBuku(anggota2, "Algoritma Pemrograman", "15/12/2024");
    tambahBuku(anggota3, "Struktur Data", "10/12/2024");

    // Menambahkan buku baru untuk Rani
    tambahBuku(anggota1, "Basis Data", "20/12/2024");

    // Menghapus anggota Dito beserta buku yang dipinjam
    hapusAnggota(head, "A002");

    // Menampilkan data anggota dan buku yang dipinjam
    tampilkanData(head);

    return 0;
}

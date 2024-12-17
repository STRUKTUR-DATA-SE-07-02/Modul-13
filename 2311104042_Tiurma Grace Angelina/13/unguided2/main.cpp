#include <iostream>
#include <string>
using namespace std;

// Struktur data untuk buku
struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* nextBuku;
};

// Struktur data untuk anggota
struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* daftarBuku;
    Anggota* nextAnggota;
};

// Fungsi untuk menambahkan anggota baru
void tambahAnggota(Anggota*& head, string nama, string id) {
    Anggota* anggotaBaru = new Anggota{nama, id, nullptr, head};
    head = anggotaBaru;
}

// Fungsi untuk menambahkan buku ke anggota
void tambahBuku(Anggota* head, string idAnggota, string judulBuku, string tanggalPengembalian) {
    while (head && head->idAnggota != idAnggota) {
        head = head->nextAnggota;
    }
    if (head) {
        Buku* bukuBaru = new Buku{judulBuku, tanggalPengembalian, head->daftarBuku};
        head->daftarBuku = bukuBaru;
    }
}

// Fungsi untuk menghapus anggota beserta buku yang dipinjam
void hapusAnggota(Anggota*& head, string idAnggota) {
    Anggota* prev = nullptr;
    Anggota* curr = head;

    while (curr && curr->idAnggota != idAnggota) {
        prev = curr;
        curr = curr->nextAnggota;
    }

    if (curr) {
        if (prev) {
            prev->nextAnggota = curr->nextAnggota;
        } else {
            head = curr->nextAnggota;
        }

        // Hapus semua buku yang dipinjam anggota
        Buku* buku = curr->daftarBuku;
        while (buku) {
            Buku* temp = buku;
            buku = buku->nextBuku;
            delete temp;
        }

        delete curr;
    }
}

// Fungsi untuk menampilkan data anggota dan buku yang dipinjam
void tampilkanData(Anggota* head) {
    while (head) {
        cout << "Nama Anggota: " << head->namaAnggota << ", ID: " << head->idAnggota << endl;
        Buku* buku = head->daftarBuku;
        while (buku) {
            cout << "  - Judul Buku: " << buku->judulBuku << ", Pengembalian: " << buku->tanggalPengembalian << endl;
            buku = buku->nextBuku;
        }
        head = head->nextAnggota;
    }
}

int main() {
    Anggota* daftarAnggota = nullptr;

    // Tambahkan anggota
    tambahAnggota(daftarAnggota, "Rani", "A001");
    tambahAnggota(daftarAnggota, "Dito", "A002");
    tambahAnggota(daftarAnggota, "Vina", "A003");

    // Tambahkan buku yang dipinjam
    tambahBuku(daftarAnggota, "A001", "Pemrograman C++", "01/12/2024");
    tambahBuku(daftarAnggota, "A002", "Algoritma Pemrograman", "15/12/2024");

    // Tambahkan buku baru ke Rani
    tambahBuku(daftarAnggota, "A001", "Struktur Data", "10/12/2024");

    // Hapus anggota Dito beserta buku yang dipinjam
    hapusAnggota(daftarAnggota, "A002");

    // Tampilkan data anggota dan buku
    tampilkanData(daftarAnggota);

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// Struktur data buku
struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* nextBuku;
};

// Struktur data anggota
struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* daftarBuku;
    Anggota* nextAnggota;
};

// Fungsi untuk membuat anggota baru
Anggota* buatAnggota(string nama, string id) {
    Anggota* anggotaBaru = new Anggota;
    anggotaBaru->namaAnggota = nama;
    anggotaBaru->idAnggota = id;
    anggotaBaru->daftarBuku = nullptr;
    anggotaBaru->nextAnggota = nullptr;
    return anggotaBaru;
}

// Fungsi untuk menambahkan buku yang dipinjam oleh anggota
void tambahkanBuku(Anggota* anggota, string judulBuku, string tanggalPengembalian) {
    Buku* bukuBaru = new Buku;
    bukuBaru->judulBuku = judulBuku;
    bukuBaru->tanggalPengembalian = tanggalPengembalian;
    bukuBaru->nextBuku = anggota->daftarBuku;
    anggota->daftarBuku = bukuBaru;
}

// Fungsi untuk menghapus anggota beserta buku yang dipinjam
Anggota* hapusAnggota(Anggota* head, string idAnggota) {
    Anggota* curr = head;
    Anggota* prev = nullptr;

    while (curr != nullptr && curr->idAnggota != idAnggota) {
        prev = curr;
        curr = curr->nextAnggota;
    }

    if (curr != nullptr) {
        if (prev == nullptr) {
            head = curr->nextAnggota;
        } else {
            prev->nextAnggota = curr->nextAnggota;
        }

        Buku* currBuku = curr->daftarBuku;
        while (currBuku != nullptr) {
            Buku* temp = currBuku;
            currBuku = currBuku->nextBuku;
            delete temp;
        }
        delete curr;
    }
    return head;
}

// Fungsi untuk menampilkan data anggota dan buku yang dipinjam
void tampilkanData(Anggota* head) {
    Anggota* currAnggota = head;
    while (currAnggota != nullptr) {
        cout << "Anggota: " << currAnggota->namaAnggota << " (ID: " << currAnggota->idAnggota << ")\n";
        Buku* currBuku = currAnggota->daftarBuku;
        if (currBuku == nullptr) {
            cout << "  Tidak ada buku yang dipinjam.\n";
        } else {
            while (currBuku != nullptr) {
                cout << "  Buku: " << currBuku->judulBuku << ", Pengembalian: " << currBuku->tanggalPengembalian << "\n";
                currBuku = currBuku->nextBuku;
            }
        }
        currAnggota = currAnggota->nextAnggota;
        cout << endl;
    }
}

int main() {
    // Membuat daftar anggota
    Anggota* head = buatAnggota("Rani", "A001");
    head->nextAnggota = buatAnggota("Dito", "A002");
    head->nextAnggota->nextAnggota = buatAnggota("Vina", "A003");

    // Menambahkan buku yang dipinjam
    tambahkanBuku(head, "Pemrograman C++", "01/12/2024"); // Untuk Rani
    tambahkanBuku(head->nextAnggota, "Algoritma Pemrograman", "15/12/2024"); // Untuk Dito

    // Menambahkan buku baru untuk Rani
    tambahkanBuku(head, "Struktur Data", "10/12/2024");

    // Menghapus anggota Dito beserta buku yang dipinjam
    head = hapusAnggota(head, "A002");

    // Menampilkan data anggota dan buku yang dipinjam
    tampilkanData(head);

    return 0;
}
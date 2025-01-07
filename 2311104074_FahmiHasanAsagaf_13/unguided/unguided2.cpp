#include <iostream>
#include <string>
using namespace std;

// Struktur untuk Node Buku
struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* next; // Pointer ke buku berikutnya
};

// Struktur untuk Node Anggota
struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* headBuku; // Pointer ke buku pertama
    Anggota* next;  // Pointer ke anggota berikutnya
};

// Fungsi untuk membuat node anggota baru
Anggota* buatAnggota(string nama, string id) {
    Anggota* anggotaBaru = new Anggota;
    anggotaBaru->namaAnggota = nama;
    anggotaBaru->idAnggota = id;
    anggotaBaru->headBuku = NULL;
    anggotaBaru->next = NULL;
    return anggotaBaru;
}

// Fungsi untuk membuat node buku baru
Buku* buatBuku(string judul, string tanggal) {
    Buku* bukuBaru = new Buku;
    bukuBaru->judulBuku = judul;
    bukuBaru->tanggalPengembalian = tanggal;
    bukuBaru->next = NULL;
    return bukuBaru;
}

// Fungsi untuk menambahkan buku ke anggota tertentu
void tambahBuku(Anggota* anggota, string judul, string tanggal) {
    Buku* bukuBaru = buatBuku(judul, tanggal);
    if (anggota->headBuku == NULL) {
        anggota->headBuku = bukuBaru;
    } else {
        Buku* temp = anggota->headBuku;
        while (temp->next != NULL) {
            temp = temp->next; // Cari buku terakhir
        }
        temp->next = bukuBaru;
    }
}

// Fungsi untuk menghapus anggota beserta semua buku yang dipinjam
void hapusAnggota(Anggota*& head, string id) {
    Anggota* temp = head;
    Anggota* prev = NULL;

    while (temp != NULL && temp->idAnggota != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Anggota dengan ID \"" << id << "\" tidak ditemukan.\n";
        return;
    }

    // Hapus semua buku yang dipinjam oleh anggota
    Buku* currentBuku = temp->headBuku;
    while (currentBuku != NULL) {
        Buku* toDelete = currentBuku;
        currentBuku = currentBuku->next;
        delete toDelete;
    }

    // Hapus anggota dari daftar
    if (prev == NULL) {
        head = temp->next; // Anggota pertama dihapus
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Anggota dengan ID \"" << id << "\" berhasil dihapus beserta bukunya.\n";
}

// Fungsi untuk menampilkan seluruh data anggota dan buku yang dipinjam
void tampilkanData(Anggota* head) {
    Anggota* tempAnggota = head;
    while (tempAnggota != NULL) {
        cout << "Anggota: " << tempAnggota->namaAnggota 
             << " (ID: " << tempAnggota->idAnggota << ")\n";
        Buku* tempBuku = tempAnggota->headBuku;
        if (tempBuku == NULL) {
            cout << "  Tidak ada buku yang dipinjam.\n";
        } else {
            while (tempBuku != NULL) {
                cout << "  - Buku: " << tempBuku->judulBuku 
                     << ", Pengembalian: " << tempBuku->tanggalPengembalian << endl;
                tempBuku = tempBuku->next;
            }
        }
        tempAnggota = tempAnggota->next;
        cout << endl;
    }
}

int main() {
    // Membuat daftar anggota perpustakaan
    Anggota* headAnggota = buatAnggota("Rani", "A001");
    headAnggota->next = buatAnggota("Dito", "A002");
    headAnggota->next->next = buatAnggota("Vina", "A003");

    // Menambahkan buku yang dipinjam
    tambahBuku(headAnggota, "Pemrograman C++", "01/12/2024"); // Untuk Rani
    tambahBuku(headAnggota->next, "Algoritma Pemrograman", "15/12/2024"); // Untuk Dito

    // Menambahkan buku baru untuk Rani
    tambahBuku(headAnggota, "Struktur Data", "10/12/2024");

    // Menghapus anggota Dito beserta bukunya
    hapusAnggota(headAnggota, "A002");

    // Menampilkan seluruh data anggota dan buku
    cout << "\nData Anggota Perpustakaan dan Buku yang Dipinjam:\n";
    tampilkanData(headAnggota);

    return 0;
}
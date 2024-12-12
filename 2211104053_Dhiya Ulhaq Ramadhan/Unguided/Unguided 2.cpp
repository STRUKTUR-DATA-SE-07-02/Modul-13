#include <iostream>
#include <string>
using namespace std;

// Struktur untuk node Buku
struct Buku {
    string judul;
    string tanggalPengembalian;
    Buku* next;
};

// Struktur untuk node Anggota
struct Anggota {
    string nama;
    string id;
    Buku* daftarBuku;
    Anggota* next;
};

// Fungsi untuk membuat anggota baru
Anggota* buatAnggota(string nama, string id) {
    Anggota* anggotaBaru = new Anggota;
    anggotaBaru->nama = nama;
    anggotaBaru->id = id;
    anggotaBaru->daftarBuku = NULL;
    anggotaBaru->next = NULL;
    return anggotaBaru;
}

// Fungsi untuk membuat buku baru
Buku* buatBuku(string judul, string tanggalPengembalian) {
    Buku* bukuBaru = new Buku;
    bukuBaru->judul = judul;
    bukuBaru->tanggalPengembalian = tanggalPengembalian;
    bukuBaru->next = NULL;
    return bukuBaru;
}

// Fungsi untuk menambahkan buku ke anggota
void tambahBuku(Anggota* anggota, string judul, string tanggalPengembalian) {
    Buku* bukuBaru = buatBuku(judul, tanggalPengembalian);

    if (anggota->daftarBuku == NULL) {
        anggota->daftarBuku = bukuBaru;
    } else {
        Buku* current = anggota->daftarBuku;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = bukuBaru;
    }
}

// Fungsi untuk menghapus anggota dan buku-bukunya
void hapusAnggota(Anggota*& kepala, string id) {
    if (kepala == NULL) return;

    if (kepala->id == id) {
        Anggota* temp = kepala;
        kepala = kepala->next;

        // Hapus semua buku anggota
        Buku* currentBuku = temp->daftarBuku;
        while (currentBuku != NULL) {
            Buku* tempBuku = currentBuku;
            currentBuku = currentBuku->next;
            delete tempBuku;
        }

        delete temp;
        return;
    }

    Anggota* current = kepala;
    while (current->next != NULL && current->next->id != id) {
        current = current->next;
    }

    if (current->next != NULL) {
        Anggota* temp = current->next;
        current->next = current->next->next;

        // Hapus semua buku anggota
        Buku* currentBuku = temp->daftarBuku;
        while (currentBuku != NULL) {
            Buku* tempBuku = currentBuku;
            currentBuku = currentBuku->next;
            delete tempBuku;
        }

        delete temp;
    }
}

// Fungsi untuk menampilkan data anggota dan buku
void tampilkanData(Anggota* kepala) {
    Anggota* currentAnggota = kepala;
    while (currentAnggota != NULL) {
        cout << "\nAnggota: " << currentAnggota->nama << " (ID: " << currentAnggota->id << ")" << endl;
        cout << "Buku yang dipinjam:" << endl;

        Buku* currentBuku = currentAnggota->daftarBuku;
        if (currentBuku == NULL) {
            cout << "- Tidak ada buku yang dipinjam" << endl;
        }
        while (currentBuku != NULL) {
            cout << "- " << currentBuku->judul << " (Pengembalian: " << currentBuku->tanggalPengembalian << ")" << endl;
            currentBuku = currentBuku->next;
        }
        currentAnggota = currentAnggota->next;
    }
}

int main() {
    // Membuat daftar anggota
    Anggota* kepala = buatAnggota("Rani", "A001");
    kepala->next = buatAnggota("Dito", "A002");
    kepala->next->next = buatAnggota("Vina", "A003");

    // Menambahkan buku untuk Rani
    tambahBuku(kepala, "Pemrograman C++", "01/12/2024");
    tambahBuku(kepala, "Struktur Data", "10/12/2024");

    // Menambahkan buku untuk Dito
    tambahBuku(kepala->next, "Algoritma Pemrograman", "15/12/2024");

    cout << "Data Awal Perpustakaan:" << endl;
    tampilkanData(kepala);

    cout << "\nSetelah menghapus anggota Dito:" << endl;
    hapusAnggota(kepala, "A002");
    tampilkanData(kepala);

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

// Struktur untuk menyimpan data buku
struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* nextBuku; // Pointer ke buku berikutnya
};

// Struktur untuk menyimpan data anggota perpustakaan
struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* bukuHead; // Pointer ke linked list buku
    Anggota* nextAnggota; // Pointer ke anggota berikutnya
};

// Fungsi untuk membuat node anggota baru
Anggota* buatAnggota(string nama, string id) {
    Anggota* anggotaBaru = new Anggota;
    anggotaBaru->namaAnggota = nama;
    anggotaBaru->idAnggota = id;
    anggotaBaru->bukuHead = nullptr;
    anggotaBaru->nextAnggota = nullptr;
    return anggotaBaru;
}

// Fungsi untuk membuat node buku baru
Buku* buatBuku(string judul, string tanggal) {
    Buku* bukuBaru = new Buku;
    bukuBaru->judulBuku = judul;
    bukuBaru->tanggalPengembalian = tanggal;
    bukuBaru->nextBuku = nullptr;
    return bukuBaru;
}

// Fungsi untuk menambahkan buku yang dipinjam oleh anggota
void tambahBuku(Anggota* anggota, string judul, string tanggal) {
    Buku* bukuBaru = buatBuku(judul, tanggal);
    bukuBaru->nextBuku = anggota->bukuHead;
    anggota->bukuHead = bukuBaru;
}

// Fungsi untuk menghapus anggota beserta semua buku yang dipinjam
Anggota* hapusAnggota(Anggota* head, string id) {
    Anggota* temp = head;
    Anggota* prev = nullptr;

    while (temp != nullptr && temp->idAnggota != id) {
        prev = temp;
        temp = temp->nextAnggota;
    }

    if (temp == nullptr) {
        cout << "Anggota dengan ID " << id << " tidak ditemukan.\n";
        return head;
    }

    // Menghapus semua buku yang dipinjam anggota
    Buku* bukuTemp = temp->bukuHead;
    while (bukuTemp != nullptr) {
        Buku* hapusBuku = bukuTemp;
        bukuTemp = bukuTemp->nextBuku;
        delete hapusBuku;
    }

    // Hapus node anggota
    if (prev == nullptr) { // Jika anggota berada di awal list
        head = temp->nextAnggota;
    } else {
        prev->nextAnggota = temp->nextAnggota;
    }
    delete temp;
    cout << "Anggota dengan ID " << id << " beserta bukunya berhasil dihapus.\n";
    return head;
}

// Fungsi untuk menampilkan data anggota dan buku yang dipinjam
void tampilkanData(Anggota* head) {
    Anggota* tempAnggota = head;
    while (tempAnggota != nullptr) {
        cout << "Anggota: " << tempAnggota->namaAnggota << " (ID: " << tempAnggota->idAnggota << ")\n";
        Buku* tempBuku = tempAnggota->bukuHead;

        if (tempBuku == nullptr) {
            cout << "  Tidak ada buku yang dipinjam.\n";
        } else {
            while (tempBuku != nullptr) {
                cout << "  - Judul Buku: " << tempBuku->judulBuku
                     << ", Tanggal Pengembalian: " << tempBuku->tanggalPengembalian << "\n";
                tempBuku = tempBuku->nextBuku;
            }
        }
        tempAnggota = tempAnggota->nextAnggota;
        cout << endl;
    }
}

int main() {
    Anggota* head = nullptr;
    Anggota* tail = nullptr;

    // 1. Masukkan data anggota
    head = buatAnggota("Rani", "A001");
    tail = head;
    tail->nextAnggota = buatAnggota("Dito", "A002");
    tail = tail->nextAnggota;
    tail->nextAnggota = buatAnggota("Vina", "A003");
    tail = tail->nextAnggota;

    // 2. Tambahkan buku yang dipinjam
    tambahBuku(head, "Pemrograman C++", "01/12/2024"); // Buku untuk Rani
    tambahBuku(head->nextAnggota, "Algoritma Pemrograman", "15/12/2024"); // Buku untuk Dito

    // 3. Tambahkan buku baru untuk Rani
    tambahBuku(head, "Struktur Data", "10/12/2024");

    // Tampilkan data awal
    cout << "=== Data Anggota dan Buku ===\n";
    tampilkanData(head);

    // 4. Hapus anggota Dito beserta bukunya
    cout << "\n=== Menghapus Anggota Dito ===\n";
    head = hapusAnggota(head, "A002");

    // 5. Tampilkan data setelah penghapusan
    cout << "\n=== Data Setelah Penghapusan ===\n";
    tampilkanData(head);

    return 0;
}


#include <iostream>
#include <string>
using namespace std;

// Struktur untuk node Proyek
struct Proyek {
    string nama;
    int durasi;
    Proyek* next;
};

// Struktur untuk node Pegawai
struct Pegawai {
    string nama;
    string id;
    Proyek* proyek;
    Pegawai* next;
};

// Fungsi untuk membuat pegawai baru
Pegawai* buatPegawai(string nama, string id) {
    Pegawai* pegawaiBaru = new Pegawai;
    pegawaiBaru->nama = nama;
    pegawaiBaru->id = id;
    pegawaiBaru->proyek = NULL;
    pegawaiBaru->next = NULL;
    return pegawaiBaru;
}

// Fungsi untuk membuat proyek baru
Proyek* buatProyek(string nama, int durasi) {
    Proyek* proyekBaru = new Proyek;
    proyekBaru->nama = nama;
    proyekBaru->durasi = durasi;
    proyekBaru->next = NULL;
    return proyekBaru;
}

// Fungsi untuk menambahkan proyek ke pegawai
void tambahProyek(Pegawai* peg, string namaProyek, int durasi) {
    Proyek* proyekBaru = buatProyek(namaProyek, durasi);

    if (peg->proyek == NULL) {
        peg->proyek = proyekBaru;
    } else {
        Proyek* current = peg->proyek;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = proyekBaru;
    }
}

// Fungsi untuk menghapus proyek dari pegawai
void hapusProyek(Pegawai* peg, string namaProyek) {
    if (peg->proyek == NULL) return;

    if (peg->proyek->nama == namaProyek) {
        Proyek* temp = peg->proyek;
        peg->proyek = peg->proyek->next;
        delete temp;
        return;
    }

    Proyek* current = peg->proyek;
    while (current->next != NULL && current->next->nama != namaProyek) {
        current = current->next;
    }

    if (current->next != NULL) {
        Proyek* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Fungsi untuk menampilkan proyek-proyek seorang pegawai
void tampilkanProyek(Pegawai* peg) {
    cout << "Proyek untuk " << peg->nama << " (ID: " << peg->id << "):" << endl;
    Proyek* current = peg->proyek;
    while (current != NULL) {
        cout << "- Proyek: " << current->nama << ", Durasi: " << current->durasi << " bulan" << endl;
        current = current->next;
    }
    cout << endl;
}

int main() {
    // Membuat daftar pegawai
    Pegawai* kepala = buatPegawai("Andi", "P001");
    kepala->next = buatPegawai("Budi", "P002");
    kepala->next->next = buatPegawai("Citra", "P003");

    // Menambahkan proyek ke Andi
    tambahProyek(kepala, "Aplikasi Mobile", 12);
    tambahProyek(kepala, "Analisis Data", 6);

    // Menambahkan proyek ke Budi
    tambahProyek(kepala->next, "Sistem Akuntansi", 8);

    // Menambahkan proyek ke Citra
    tambahProyek(kepala->next->next, "E-commerce", 10);

    // Menampilkan data proyek awal
    cout << "Data Proyek Awal:" << endl;
    tampilkanProyek(kepala);
    tampilkanProyek(kepala->next);
    tampilkanProyek(kepala->next->next);

    // Menghapus proyek "Aplikasi Mobile" dari Andi
    cout << "Setelah menghapus 'Aplikasi Mobile' dari Andi:" << endl;
    hapusProyek(kepala, "Aplikasi Mobile");
    tampilkanProyek(kepala);

    return 0;
}

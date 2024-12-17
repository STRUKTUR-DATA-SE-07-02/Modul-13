#include <iostream>
#include <string>
using namespace std;

// Struktur data untuk proyek
struct Proyek {
    string namaProyek;
    int durasi;
    Proyek* nextProyek;
};

// Struktur data untuk pegawai
struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* daftarProyek;
    Pegawai* nextPegawai;
};

// Fungsi untuk menambahkan pegawai baru
void tambahPegawai(Pegawai*& head, string nama, string id) {
    Pegawai* pegawaiBaru = new Pegawai{nama, id, nullptr, head};
    head = pegawaiBaru;
}

// Fungsi untuk menambahkan proyek ke pegawai
void tambahProyek(Pegawai* head, string idPegawai, string namaProyek, int durasi) {
    while (head && head->idPegawai != idPegawai) {
        head = head->nextPegawai;
    }
    if (head) {
        Proyek* proyekBaru = new Proyek{namaProyek, durasi, head->daftarProyek};
        head->daftarProyek = proyekBaru;
    }
}

// Fungsi untuk menghapus proyek dari pegawai
void hapusProyek(Pegawai* head, string idPegawai, string namaProyek) {
    while (head && head->idPegawai != idPegawai) {
        head = head->nextPegawai;
    }
    if (head) {
        Proyek* prev = nullptr;
        Proyek* curr = head->daftarProyek;
        while (curr && curr->namaProyek != namaProyek) {
            prev = curr;
            curr = curr->nextProyek;
        }
        if (curr) {
            if (prev) {
                prev->nextProyek = curr->nextProyek;
            } else {
                head->daftarProyek = curr->nextProyek;
            }
            delete curr;
        }
    }
}

// Fungsi untuk menampilkan data pegawai dan proyek mereka
void tampilkanData(Pegawai* head) {
    while (head) {
        cout << "Nama Pegawai: " << head->namaPegawai << ", ID: " << head->idPegawai << endl;
        Proyek* proyek = head->daftarProyek;
        while (proyek) {
            cout << "  - Nama Proyek: " << proyek->namaProyek << ", Durasi: " << proyek->durasi << " bulan" << endl;
            proyek = proyek->nextProyek;
        }
        head = head->nextPegawai;
    }
}

int main() {
    Pegawai* daftarPegawai = nullptr;

    // Tambahkan pegawai
    tambahPegawai(daftarPegawai, "Andi", "P001");
    tambahPegawai(daftarPegawai, "Budi", "P002");
    tambahPegawai(daftarPegawai, "Citra", "P003");

    // Tambahkan proyek ke pegawai
    tambahProyek(daftarPegawai, "P001", "Aplikasi Mobile", 12);
    tambahProyek(daftarPegawai, "P002", "Sistem Akuntansi", 8);
    tambahProyek(daftarPegawai, "P003", "E-commerce", 10);

    // Tambahkan proyek baru ke Andi
    tambahProyek(daftarPegawai, "P001", "Analisis Data", 6);

    // Hapus proyek "Aplikasi Mobile" dari Andi
    hapusProyek(daftarPegawai, "P001", "Aplikasi Mobile");

    // Tampilkan data pegawai dan proyek
    tampilkanData(daftarPegawai);

    return 0;
}

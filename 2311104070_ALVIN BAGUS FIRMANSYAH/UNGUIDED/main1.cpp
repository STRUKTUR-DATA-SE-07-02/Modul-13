#include <iostream>
#include <string>

using namespace std;

// Struktur untuk menyimpan data proyek
struct Proyek {
    string namaProyek;
    int durasi; // durasi dalam bulan
    Proyek* next; // pointer ke proyek berikutnya
};

// Struktur untuk menyimpan data pegawai
struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* listProyek; // list anak untuk proyek
    Pegawai* next; // pointer ke pegawai berikutnya
};

// Fungsi untuk menambahkan proyek ke pegawai
void tambahProyek(Pegawai* pegawai, string namaProyek, int durasi) {
    Proyek* proyekBaru = new Proyek;
    proyekBaru->namaProyek = namaProyek;
    proyekBaru->durasi = durasi;
    proyekBaru->next = nullptr;

    if (pegawai->listProyek == nullptr) {
        pegawai->listProyek = proyekBaru;
    } else {
        Proyek* temp = pegawai->listProyek;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = proyekBaru;
    }
}

// Fungsi untuk menghapus proyek berdasarkan nama proyek
void hapusProyek(Pegawai* pegawai, string namaProyek) {
    Proyek* current = pegawai->listProyek;
    Proyek* previous = nullptr;

    while (current != nullptr && current->namaProyek != namaProyek) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous == nullptr) {
            pegawai->listProyek = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }
}

// Fungsi untuk menampilkan data pegawai dan proyek
void tampilkanData(Pegawai* pegawai) {
    while (pegawai != nullptr) {
        cout << "Nama Pegawai: " << pegawai->namaPegawai << ", ID: " << pegawai->idPegawai << endl;
        Proyek* proyek = pegawai->listProyek;
        while (proyek != nullptr) {
            cout << "\tProyek: " << proyek->namaProyek << ", Durasi: " << proyek->durasi << " bulan" << endl;
            proyek = proyek->next;
        }
        pegawai = pegawai->next;
    }
}

int main() {
    // Membuat list pegawai
    Pegawai* head = nullptr;

    // Menambahkan pegawai
    Pegawai* pegawai1 = new Pegawai{"Andi", "P001", nullptr, nullptr};
    Pegawai* pegawai2 = new Pegawai{"Budi", "P002", nullptr, nullptr};
    Pegawai* pegawai3 = new Pegawai{"Citra", "P003", nullptr, nullptr};

    head = pegawai1;
    pegawai1->next = pegawai2;
    pegawai2->next = pegawai3;

    // Menambahkan proyek ke pegawai
    tambahProyek(pegawai1, "Aplikasi Mobile", 12);
    tambahProyek(pegawai2, "Sistem Akuntansi", 8);
    tambahProyek(pegawai3, "E-commerce", 10);

    // Menambahkan proyek baru untuk Andi
    tambahProyek(pegawai1, "Analisis Data", 6);

    // Menghapus proyek "Aplikasi Mobile" dari Andi
    hapusProyek(pegawai1, "Aplikasi Mobile");

    // Menampilkan data pegawai dan proyek
    tampilkanData(head);

    return 0;
}

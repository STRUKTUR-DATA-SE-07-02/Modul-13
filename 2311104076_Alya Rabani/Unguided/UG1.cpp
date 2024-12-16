#include <iostream>
#include <string>
using namespace std;

// Struktur data proyek
struct Proyek {
    string namaProyek;
    int durasi;
    Proyek* nextProyek;
};

// Struktur data pegawai
struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* daftarProyek;
    Pegawai* nextPegawai;
};

// Fungsi untuk membuat pegawai baru
Pegawai* buatPegawai(string nama, string id) {
    Pegawai* pegawaiBaru = new Pegawai;
    pegawaiBaru->namaPegawai = nama;
    pegawaiBaru->idPegawai = id;
    pegawaiBaru->daftarProyek = nullptr;
    pegawaiBaru->nextPegawai = nullptr;
    return pegawaiBaru;
}

// Fungsi untuk menambahkan proyek ke pegawai
void tambahkanProyek(Pegawai* pegawai, string namaProyek, int durasi) {
    Proyek* proyekBaru = new Proyek;
    proyekBaru->namaProyek = namaProyek;
    proyekBaru->durasi = durasi;
    proyekBaru->nextProyek = pegawai->daftarProyek;
    pegawai->daftarProyek = proyekBaru;
}

// Fungsi untuk menghapus proyek dari pegawai
void hapusProyek(Pegawai* pegawai, string namaProyek) {
    Proyek* curr = pegawai->daftarProyek;
    Proyek* prev = nullptr;

    while (curr != nullptr && curr->namaProyek != namaProyek) {
        prev = curr;
        curr = curr->nextProyek;
    }

    if (curr != nullptr) {
        if (prev == nullptr) {
            pegawai->daftarProyek = curr->nextProyek;
        } else {
            prev->nextProyek = curr->nextProyek;
        }
        delete curr;
    }
}

// Fungsi untuk menampilkan data pegawai dan proyeknya
void tampilkanData(Pegawai* head) {
    Pegawai* currPegawai = head;
    while (currPegawai != nullptr) {
        cout << "Pegawai: " << currPegawai->namaPegawai << " (ID: " << currPegawai->idPegawai << ")\n";
        Proyek* currProyek = currPegawai->daftarProyek;
        if (currProyek == nullptr) {
            cout << "  Tidak ada proyek.\n";
        } else {
            while (currProyek != nullptr) {
                cout << "  Proyek: " << currProyek->namaProyek << ", Durasi: " << currProyek->durasi << " bulan\n";
                currProyek = currProyek->nextProyek;
            }
        }
        currPegawai = currPegawai->nextPegawai;
        cout << endl;
    }
}

int main() {
    // Membuat daftar pegawai
    Pegawai* head = buatPegawai("Andi", "P001");
    head->nextPegawai = buatPegawai("Budi", "P002");
    head->nextPegawai->nextPegawai = buatPegawai("Citra", "P003");

    // Menambahkan proyek ke pegawai
    tambahkanProyek(head, "Aplikasi Mobile", 12); // Untuk Andi
    tambahkanProyek(head->nextPegawai, "Sistem Akuntansi", 8); // Untuk Budi
    tambahkanProyek(head->nextPegawai->nextPegawai, "E-commerce", 10); // Untuk Citra

    // Menambahkan proyek baru ke Andi
    tambahkanProyek(head, "Analisis Data", 6);

    // Menghapus proyek "Aplikasi Mobile" dari Andi
    hapusProyek(head, "Aplikasi Mobile");

    // Menampilkan data pegawai dan proyek mereka
    tampilkanData(head);

    return 0;
}
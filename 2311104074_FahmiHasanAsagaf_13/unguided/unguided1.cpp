#include <iostream>
#include <string>
using namespace std;

// Struktur untuk Node Proyek
struct Proyek {
    string namaProyek;
    int durasi; // durasi dalam bulan
    Proyek* next; // pointer ke proyek berikutnya
};

// Struktur untuk Node Pegawai
struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* headProyek; // pointer ke proyek pertama
    Pegawai* next; // pointer ke pegawai berikutnya
};

// Fungsi untuk membuat node pegawai baru
Pegawai* buatPegawai(string nama, string id) {
    Pegawai* pegawaiBaru = new Pegawai;
    pegawaiBaru->namaPegawai = nama;
    pegawaiBaru->idPegawai = id;
    pegawaiBaru->headProyek = NULL;
    pegawaiBaru->next = NULL;
    return pegawaiBaru;
}

// Fungsi untuk membuat node proyek baru
Proyek* buatProyek(string namaProyek, int durasi) {
    Proyek* proyekBaru = new Proyek;
    proyekBaru->namaProyek = namaProyek;
    proyekBaru->durasi = durasi;
    proyekBaru->next = NULL;
    return proyekBaru;
}

// Fungsi untuk menambahkan proyek ke pegawai tertentu
void tambahProyek(Pegawai* pegawai, string namaProyek, int durasi) {
    Proyek* proyekBaru = buatProyek(namaProyek, durasi);
    if (pegawai->headProyek == NULL) {
        pegawai->headProyek = proyekBaru; // proyek pertama
    } else {
        Proyek* temp = pegawai->headProyek;
        while (temp->next != NULL) {
            temp = temp->next; // cari proyek terakhir
        }
        temp->next = proyekBaru;
    }
}

// Fungsi untuk menghapus proyek tertentu dari pegawai
void hapusProyek(Pegawai* pegawai, string namaProyek) {
    Proyek* temp = pegawai->headProyek;
    Proyek* prev = NULL;

    while (temp != NULL && temp->namaProyek != namaProyek) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Proyek \"" << namaProyek << "\" tidak ditemukan.\n";
        return;
    }

    if (prev == NULL) { // proyek yang dihapus adalah proyek pertama
        pegawai->headProyek = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Proyek \"" << namaProyek << "\" berhasil dihapus.\n";
}

// Fungsi untuk menampilkan data pegawai dan proyek mereka
void tampilkanData(Pegawai* headPegawai) {
    Pegawai* tempPegawai = headPegawai;
    while (tempPegawai != NULL) {
        cout << "Pegawai: " << tempPegawai->namaPegawai 
             << " (ID: " << tempPegawai->idPegawai << ")\n";
        Proyek* tempProyek = tempPegawai->headProyek;
        if (tempProyek == NULL) {
            cout << "  Tidak ada proyek.\n";
        } else {
            while (tempProyek != NULL) {
                cout << "  - Proyek: " << tempProyek->namaProyek
                     << ", Durasi: " << tempProyek->durasi << " bulan\n";
                tempProyek = tempProyek->next;
            }
        }
        tempPegawai = tempPegawai->next;
        cout << endl;
    }
}

int main() {
    // Membuat daftar pegawai
    Pegawai* headPegawai = buatPegawai("Andi", "P001");
    headPegawai->next = buatPegawai("Budi", "P002");
    headPegawai->next->next = buatPegawai("Citra", "P003");

    // Menambahkan proyek ke pegawai
    tambahProyek(headPegawai, "Aplikasi Mobile", 12); // Proyek untuk Andi
    tambahProyek(headPegawai->next, "Sistem Akuntansi", 8); // Proyek untuk Budi
    tambahProyek(headPegawai->next->next, "E-commerce", 10); // Proyek untuk Citra

    // Menambahkan proyek baru ke Andi
    tambahProyek(headPegawai, "Analisis Data", 6);

    // Menghapus proyek "Aplikasi Mobile" dari Andi
    hapusProyek(headPegawai, "Aplikasi Mobile");

    // Menampilkan data pegawai dan proyek mereka
    cout << "\nData Pegawai dan Proyek:\n";
    tampilkanData(headPegawai);

    return 0;
}
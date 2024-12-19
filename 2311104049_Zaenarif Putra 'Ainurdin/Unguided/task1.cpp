// Program Management Data Pegawai dan Proyek

#include <iostream>
#include <string>
using namespace std;

struct Proyek {
    string namaProyek;
    int durasi;
    Proyek* nextProyek;
};

struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* headProyek;
    Pegawai* nextPegawai;
};

Pegawai* headPegawai = nullptr;

void tambahPegawai(string nama, string id) {
    Pegawai* pegawaiBaru = new Pegawai;
    pegawaiBaru->namaPegawai = nama;
    pegawaiBaru->idPegawai = id;
    pegawaiBaru->headProyek = nullptr;
    pegawaiBaru->nextPegawai = headPegawai;
    headPegawai = pegawaiBaru;
}

void tambahProyek(string idPegawai, string namaProyek, int durasi) {
    Pegawai* currPegawai = headPegawai;
    while (currPegawai != nullptr) {
        if (currPegawai->idPegawai == idPegawai) {
            Proyek* proyekBaru = new Proyek;
            proyekBaru->namaProyek = namaProyek;
            proyekBaru->durasi = durasi;
            proyekBaru->nextProyek = currPegawai->headProyek;
            currPegawai->headProyek = proyekBaru;
            return;
        }
        currPegawai = currPegawai->nextPegawai;
    }
    cout << "Pegawai dengan ID : " << idPegawai << " tidak dapat ditemukan!\n";
}

void hapusProyek(string idPegawai, string namaProyek) {
    Pegawai* currPegawai = headPegawai;
    while (currPegawai != nullptr) {
        if (currPegawai->idPegawai == idPegawai) {
            Proyek* currProyek = currPegawai->headProyek;
            Proyek* prevProyek = nullptr;
            while (currProyek != nullptr) {
                if (currProyek->namaProyek == namaProyek) {
                    if (prevProyek == nullptr) {
                        currPegawai->headProyek = currProyek->nextProyek;
                    } else {
                        prevProyek->nextProyek = currProyek->nextProyek;
                    }
                    delete currProyek;
                    return;
                }
                prevProyek = currProyek;
                currProyek = currProyek->nextProyek;
            }
        }
        currPegawai = currPegawai->nextPegawai;
    }
    cout << "Proyek : " << namaProyek << " tidak ditemukan untuk pegawai dengan ID : " << idPegawai << "!\n";
}

void tampilkanData() {
    Pegawai* currPegawai = headPegawai;
    while (currPegawai != nullptr) {
        cout << "Pegawai : " << currPegawai->namaPegawai << " (ID: " << currPegawai->idPegawai << ")\n";
        Proyek* currProyek = currPegawai->headProyek;
        while (currProyek != nullptr) {
            cout << "  Proyek : " << currProyek->namaProyek << " (Durasi : " << currProyek->durasi << " bulan)\n";
            currProyek = currProyek->nextProyek;
        }
        currPegawai = currPegawai->nextPegawai;
    }
}

int main() {
    int menu;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Nama Pegawai\n";
        cout << "2. Tambah Nama Proyek\n";
        cout << "3. Hapus Nama Proyek\n";
        cout << "4. Tampilkan Data Pegawai & Proyek\n";
        cout << "5. Keluar\n";
        cout << "Menu: ";
        cin >> menu;
        cin.ignore();

        if (menu == 1) {
            string nama, id;
            cout << "Masukkan Nama Pegawai : ";
            getline(cin, nama);
            cout << "Masukkan ID Pegawai : ";
            getline(cin, id);
            tambahPegawai(nama, id);
        } else if (menu == 2) {
            string id, namaProyek;
            int durasi;
            cout << "Masukkan ID Pegawai : ";
            getline(cin, id);
            cout << "Masukkan Nama Proyek : ";
            getline(cin, namaProyek);
            cout << "Masukkan Durasi Proyek (bulan) : ";
            cin >> durasi;
            cin.ignore();
            tambahProyek(id, namaProyek, durasi);
        } else if (menu == 3) {
            string id, namaProyek;
            cout << "Masukkan ID Pegawai : ";
            getline(cin, id);
            cout << "Masukkan Nama Proyek yang akan dihapus : ";
            getline(cin, namaProyek);
            hapusProyek(id, namaProyek);
        } else if (menu == 4) {
            tampilkanData();
        } else if (menu != 5) {
            cout << "Pilihan tidak tersedia.\n";
        }
    } while (menu != 5);

    return 0;
}
#include <iostream>
#include <string>
using namespace std;

struct Pustaka {
    string judulPustaka;
    string jadwalPengembalian;
    Pustaka* pustakaBerikutnya;
};

struct Pemustaka {
    string namaPemustaka;
    string idPemustaka;
    Pustaka* kepalaPustaka;
    Pemustaka* pemustakaBerikutnya;
};

Pemustaka* kepalaPemustaka = nullptr;

void tambahPemustaka(string nama, string id) {
    Pemustaka* pemustakaBaru = new Pemustaka;
    pemustakaBaru->namaPemustaka = nama;
    pemustakaBaru->idPemustaka = id;
    pemustakaBaru->kepalaPustaka = nullptr;
    pemustakaBaru->pemustakaBerikutnya = kepalaPemustaka;
    kepalaPemustaka = pemustakaBaru;
}

void tambahPustaka(string idPemustaka, string judulPustaka, string jadwalPengembalian) {
    Pemustaka* pemustakaSaatIni = kepalaPemustaka;
    while (pemustakaSaatIni != nullptr) {
        if (pemustakaSaatIni->idPemustaka == idPemustaka) {
            Pustaka* pustakaBaru = new Pustaka;
            pustakaBaru->judulPustaka = judulPustaka;
            pustakaBaru->jadwalPengembalian = jadwalPengembalian;
            pustakaBaru->pustakaBerikutnya = pemustakaSaatIni->kepalaPustaka;
            pemustakaSaatIni->kepalaPustaka = pustakaBaru;
            return;
        }
        pemustakaSaatIni = pemustakaSaatIni->pemustakaBerikutnya;
    }
    cout << "Pemustaka dengan ID : " << idPemustaka << " tidak dapat ditemukan!\n";
}

void hapusPemustaka(string idPemustaka) {
    Pemustaka* pemustakaSaatIni = kepalaPemustaka;
    Pemustaka* pemustakaSebelumnya = nullptr;
    while (pemustakaSaatIni != nullptr) {
        if (pemustakaSaatIni->idPemustaka == idPemustaka) {
            if (pemustakaSebelumnya == nullptr) {
                kepalaPemustaka = pemustakaSaatIni->pemustakaBerikutnya;
            } else {
                pemustakaSebelumnya->pemustakaBerikutnya = pemustakaSaatIni->pemustakaBerikutnya;
            }
            Pustaka* pustakaSaatIni = pemustakaSaatIni->kepalaPustaka;
            while (pustakaSaatIni != nullptr) {
                Pustaka* temp = pustakaSaatIni;
                pustakaSaatIni = pustakaSaatIni->pustakaBerikutnya;
                delete temp;
            }
            delete pemustakaSaatIni;
            return;
        }
        pemustakaSebelumnya = pemustakaSaatIni;
        pemustakaSaatIni = pemustakaSaatIni->pemustakaBerikutnya;
    }
    cout << "Pemustaka dengan ID : " << idPemustaka << " tidak dapat ditemukan!\n";
}

void tampilkanDataPerpustakaan() {
    Pemustaka* pemustakaSaatIni = kepalaPemustaka;
    while (pemustakaSaatIni != nullptr) {
        cout << "Pemustaka : " << pemustakaSaatIni->namaPemustaka << " (ID : " << pemustakaSaatIni->idPemustaka << ")\n";
        Pustaka* pustakaSaatIni = pemustakaSaatIni->kepalaPustaka;
        while (pustakaSaatIni != nullptr) {
            cout << "  Pustaka : " << pustakaSaatIni->judulPustaka << " (Pengembalian : " << pustakaSaatIni->jadwalPengembalian << ")\n";
            pustakaSaatIni = pustakaSaatIni->pustakaBerikutnya;
        }
        pemustakaSaatIni = pemustakaSaatIni->pemustakaBerikutnya;
    }
}

int main() {
    int menu;
    do {
        cout << "Program Sistem Manajemen Buku Perpustakaan";
        cout << "\nMenu Peminjaman Perpustakaan:\n";
        cout << "1. Tambah Nama Pemustaka\n";
        cout << "2. Tambah Nama Pustaka\n";
        cout << "3. Hapus Nama Pemustaka\n";
        cout << "4. Tampilkan Data\n";
        cout << "5. Keluar\n";
        cout << "Menu : ";
        cin >> menu;
        cin.ignore();

        if (menu == 1) {
            string nama, id;
            cout << "Masukkan Nama Pemustaka: ";
            getline(cin, nama);
            cout << "Masukkan ID Pemustaka: ";
            getline(cin, id);
            tambahPemustaka(nama, id);
        } else if (menu == 2) {
            string id, judulPustaka, jadwalPengembalian;
            cout << "Masukkan ID Pemustaka: ";
            getline(cin, id);
            cout << "Masukkan Judul Pustaka: ";
            getline(cin, judulPustaka);
            cout << "Masukkan Jadwal Pengembalian: ";
            getline(cin, jadwalPengembalian);
            tambahPustaka(id, judulPustaka, jadwalPengembalian);
        } else if (menu == 3) {
            string id;
            cout << "Masukkan ID Pemustaka yang akan dihapus: ";
            getline(cin, id);
            hapusPemustaka(id);
        } else if (menu == 4) {
            tampilkanDataPerpustakaan();
        } else if (menu != 5) {
            cout << "Pilihan tidak valid.\n";
        }
    } while (menu != 5);

    return 0;
}

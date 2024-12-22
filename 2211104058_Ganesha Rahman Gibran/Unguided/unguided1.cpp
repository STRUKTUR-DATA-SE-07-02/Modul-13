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
    Proyek* daftarProyek;
    Pegawai* nextPegawai;
};

class MultiLinkedList {
private:
    Pegawai* head;

public:
    MultiLinkedList() : head(nullptr) {}

    void tambahPegawai(string nama, string id) {
        Pegawai* pegawaiBaru = new Pegawai{nama, id, nullptr, head};
        head = pegawaiBaru;
    }

    void tambahProyek(string idPegawai, string namaProyek, int durasi) {
        Pegawai* pegawai = cariPegawai(idPegawai);
        if (pegawai) {
            Proyek* proyekBaru = new Proyek{namaProyek, durasi, pegawai->daftarProyek};
            pegawai->daftarProyek = proyekBaru;
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void hapusProyek(string idPegawai, string namaProyek) {
        Pegawai* pegawai = cariPegawai(idPegawai);
        if (pegawai) {
            Proyek* prev = nullptr;
            Proyek* curr = pegawai->daftarProyek;

            while (curr) {
                if (curr->namaProyek == namaProyek) {
                    if (prev) {
                        prev->nextProyek = curr->nextProyek;
                    } else {
                        pegawai->daftarProyek = curr->nextProyek;
                    }
                    delete curr;
                    cout << "Proyek " << namaProyek << " berhasil dihapus dari " << pegawai->namaPegawai << "\n";
                    return;
                }
                prev = curr;
                curr = curr->nextProyek;
            }
            cout << "Proyek " << namaProyek << " tidak ditemukan untuk " << pegawai->namaPegawai << "\n";
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void tampilkanData() {
        Pegawai* currPegawai = head;
        while (currPegawai) {
            cout << "Nama Pegawai: " << currPegawai->namaPegawai << ", ID: " << currPegawai->idPegawai << "\n";
            Proyek* currProyek = currPegawai->daftarProyek;
            while (currProyek) {
                cout << "  - Proyek: " << currProyek->namaProyek << ", Durasi: " << currProyek->durasi << " bulan\n";
                currProyek = currProyek->nextProyek;
            }
            currPegawai = currPegawai->nextPegawai;
        }
    }

private:
    Pegawai* cariPegawai(string idPegawai) {
        Pegawai* curr = head;
        while (curr) {
            if (curr->idPegawai == idPegawai) {
                return curr;
            }
            curr = curr->nextPegawai;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedList mll;

    mll.tambahPegawai("Andi", "P001");
    mll.tambahPegawai("Budi", "P002");
    mll.tambahPegawai("Citra", "P003");

    mll.tambahProyek("P001", "Aplikasi Mobile", 12);
    mll.tambahProyek("P002", "Sistem Akuntansi", 8);
    mll.tambahProyek("P003", "E-commerce", 10);

    mll.tambahProyek("P001", "Analisis Data", 6);

    mll.hapusProyek("P001", "Aplikasi Mobile");

    mll.tampilkanData();

    return 0;
}
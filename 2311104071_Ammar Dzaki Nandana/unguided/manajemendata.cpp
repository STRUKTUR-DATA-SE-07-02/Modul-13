#include <iostream>
#include <string>
using namespace std;

struct Proyek {
    string namaProyek;
    int durasi; // dalam bulan
    Proyek* next;
};

struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* proyekHead;
    Pegawai* next;
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
            Proyek* proyekBaru = new Proyek{namaProyek, durasi, pegawai->proyekHead};
            pegawai->proyekHead = proyekBaru;
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void hapusProyek(string idPegawai, string namaProyek) {
        Pegawai* pegawai = cariPegawai(idPegawai);
        if (pegawai) {
            Proyek* current = pegawai->proyekHead;
            Proyek* prev = nullptr;
            while (current && current->namaProyek != namaProyek) {
                prev = current;
                current = current->next;
            }
            if (current) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    pegawai->proyekHead = current->next;
                }
                delete current;
                cout << "Proyek " << namaProyek << " berhasil dihapus.\n";
            } else {
                cout << "Proyek " << namaProyek << " tidak ditemukan.\n";
            }
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void tampilkanData() {
        Pegawai* currentPegawai = head;
        while (currentPegawai) {
            cout << "Pegawai: " << currentPegawai->namaPegawai
                 << " (ID: " << currentPegawai->idPegawai << ")\n";
            Proyek* currentProyek = currentPegawai->proyekHead;
            while (currentProyek) {
                cout << "  - Proyek: " << currentProyek->namaProyek
                     << ", Durasi: " << currentProyek->durasi << " bulan\n";
                currentProyek = currentProyek->next;
            }
            currentPegawai = currentPegawai->next;
        }
    }

private:
    Pegawai* cariPegawai(string id) {
        Pegawai* current = head;
        while (current) {
            if (current->idPegawai == id) return current;
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedList mll;

    // Tambah Pegawai
    mll.tambahPegawai("Andi", "P001");
    mll.tambahPegawai("Budi", "P002");
    mll.tambahPegawai("Citra", "P003");

    // Tambah Proyek
    mll.tambahProyek("P001", "Aplikasi Mobile", 12);
    mll.tambahProyek("P002", "Sistem Akuntansi", 8);
    mll.tambahProyek("P003", "E-commerce", 10);
    mll.tambahProyek("P001", "Analisis Data", 6);

    // Hapus Proyek
    mll.hapusProyek("P001", "Aplikasi Mobile");

    // Tampilkan Data
    mll.tampilkanData();

    return 0;
}

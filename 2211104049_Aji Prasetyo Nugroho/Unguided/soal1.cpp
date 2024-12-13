#include <iostream>
#include <string>
using namespace std;

struct Proyek {
    string namaProyek;
    int durasi;
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

    void tambahPegawai(const string& nama, const string& id) {
        Pegawai* pegawaiBaru = new Pegawai{nama, id, nullptr, head};
        head = pegawaiBaru;
    }

    void tambahProyek(const string& idPegawai, const string& namaProyek, int durasi) {
        Pegawai* pegawai = cariPegawai(idPegawai);
        if (pegawai) {
            Proyek* proyekBaru = new Proyek{namaProyek, durasi, pegawai->proyekHead};
            pegawai->proyekHead = proyekBaru;
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void hapusProyek(const string& idPegawai, const string& namaProyek) {
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
                cout << "Proyek " << namaProyek << " tidak ditemukan pada pegawai " << pegawai->namaPegawai << ".\n";
            }
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void tampilkanData() {
        Pegawai* currentPegawai = head;
        while (currentPegawai) {
            cout << "Pegawai: " << currentPegawai->namaPegawai << " (ID: " << currentPegawai->idPegawai << ")\n";
            Proyek* currentProyek = currentPegawai->proyekHead;
            while (currentProyek) {
                cout << "  - Proyek: " << currentProyek->namaProyek << ", Durasi: " << currentProyek->durasi << " bulan\n";
                currentProyek = currentProyek->next;
            }
            currentPegawai = currentPegawai->next;
            cout << endl;
        }
    }

private:
    Pegawai* cariPegawai(const string& idPegawai) {
        Pegawai* current = head;
        while (current) {
            if (current->idPegawai == idPegawai) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedList mll;

    // Menambahkan data pegawai
    mll.tambahPegawai("Andi", "P001");
    mll.tambahPegawai("Budi", "P002");
    mll.tambahPegawai("Citra", "P003");

    // Menambahkan proyek ke pegawai
    mll.tambahProyek("P001", "Aplikasi Mobile", 12);
    mll.tambahProyek("P002", "Sistem Akuntansi", 8);
    mll.tambahProyek("P003", "E-commerce", 10);

    // Menambahkan proyek baru
    mll.tambahProyek("P001", "Analisis Data", 6);

    // Menghapus proyek
    mll.hapusProyek("P001", "Aplikasi Mobile");

    // Menampilkan data pegawai dan proyek
    mll.tampilkanData();

    return 0;
}
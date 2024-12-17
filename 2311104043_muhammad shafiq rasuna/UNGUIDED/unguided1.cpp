#include <iostream>
#include <string>
using namespace std;

// Node untuk proyek
struct ProyekNode {
    string namaProyek;
    int durasi;
    ProyekNode* next;

    ProyekNode(string nama, int dur) : namaProyek(nama), durasi(dur), next(nullptr) {}
};

// Node untuk pegawai
struct PegawaiNode {
    string nama;
    string idPegawai;
    PegawaiNode* next;
    ProyekNode* proyekHead;

    PegawaiNode(string namaPeg, string id) : nama(namaPeg), idPegawai(id), next(nullptr), proyekHead(nullptr) {}
};

class ManajemenPegawaiProyek {
private:
    PegawaiNode* head;

public:
    ManajemenPegawaiProyek() : head(nullptr) {}

    // Menambah pegawai baru
    void tambahPegawai(string nama, string idPegawai) {
        PegawaiNode* newPegawai = new PegawaiNode(nama, idPegawai);
        if (!head) {
            head = newPegawai;
        } else {
            PegawaiNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newPegawai;
        }
    }

    // Menambah proyek ke pegawai berdasarkan ID
    void tambahProyek(string idPegawai, string namaProyek, int durasi) {
        PegawaiNode* current = head;
        while (current) {
            if (current->idPegawai == idPegawai) {
                ProyekNode* newProyek = new ProyekNode(namaProyek, durasi);
                if (!current->proyekHead) {
                    current->proyekHead = newProyek;
                } else {
                    ProyekNode* proyekCurrent = current->proyekHead;
                    while (proyekCurrent->next) {
                        proyekCurrent = proyekCurrent->next;
                    }
                    proyekCurrent->next = newProyek;
                }
                return;
            }
            current = current->next;
        }
        cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan." << endl;
    }

    // Menghapus proyek dari pegawai berdasarkan ID pegawai dan nama proyek
    void hapusProyek(string idPegawai, string namaProyek) {
        PegawaiNode* current = head;
        while (current) {
            if (current->idPegawai == idPegawai) {
                ProyekNode* proyekCurrent = current->proyekHead;
                ProyekNode* prev = nullptr;
                while (proyekCurrent) {
                    if (proyekCurrent->namaProyek == namaProyek) {
                        if (prev) {
                            prev->next = proyekCurrent->next;
                        } else {
                            current->proyekHead = proyekCurrent->next;
                        }
                        delete proyekCurrent;
                        cout << "Proyek '" << namaProyek << "' berhasil dihapus dari " << current->nama << "." << endl;
                        return;
                    }
                    prev = proyekCurrent;
                    proyekCurrent = proyekCurrent->next;
                }
                cout << "Proyek '" << namaProyek << "' tidak ditemukan untuk pegawai " << current->nama << "." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan." << endl;
    }

    // Menampilkan data pegawai dan proyek mereka
    void tampilkanData() {
        PegawaiNode* current = head;
        while (current) {
            cout << "Pegawai: " << current->nama << " (ID: " << current->idPegawai << ")" << endl;
            ProyekNode* proyekCurrent = current->proyekHead;
            if (proyekCurrent) {
                while (proyekCurrent) {
                    cout << "  - Proyek: " << proyekCurrent->namaProyek << ", Durasi: " << proyekCurrent->durasi << " bulan" << endl;
                    proyekCurrent = proyekCurrent->next;
                }
            } else {
                cout << "  Tidak ada proyek." << endl;
            }
            current = current->next;
            cout << "-" << endl;
        }
    }
};

int main() {
    ManajemenPegawaiProyek manajemen;

    // 1. Menambahkan data pegawai
    manajemen.tambahPegawai("Andi", "P001");
    manajemen.tambahPegawai("Budi", "P002");
    manajemen.tambahPegawai("Citra", "P003");

    // 2. Menambahkan proyek ke pegawai
    manajemen.tambahProyek("P001", "Aplikasi Mobile", 12);
    manajemen.tambahProyek("P002", "Sistem Akuntansi", 8);
    manajemen.tambahProyek("P003", "E-commerce", 10);

    // 3. Menambahkan proyek baru untuk Andi
    manajemen.tambahProyek("P001", "Analisis Data", 6);

    // 4. Menghapus proyek "Aplikasi Mobile" dari Andi
    manajemen.hapusProyek("P001", "Aplikasi Mobile");

    // 5. Menampilkan data pegawai dan proyek mereka
    manajemen.tampilkanData();

    return 0;
}

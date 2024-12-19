#include <iostream>
#include <string>

using namespace std;

class Proyek {
public:
    string nama;
    int durasi;
    Proyek* next;

    Proyek(string n, int d) : nama(n), durasi(d), next(nullptr) {}
};

class Pegawai {
public:
    string nama;
    string id;
    Proyek* proyek_head;
    Pegawai* next;

    Pegawai(string n, string i) : nama(n), id(i), proyek_head(nullptr), next(nullptr) {}
};

class ManajemenPegawai {
private:
    Pegawai* pegawai_head;

public:
    ManajemenPegawai() : pegawai_head(nullptr) {}

    void tambahPegawai(string nama, string id) {
        Pegawai* pegawai = new Pegawai(nama, id);
        if (!pegawai_head) {
            pegawai_head = pegawai;
        } else {
            Pegawai* current = pegawai_head;
            while (current->next) {
                current = current->next;
            }
            current->next = pegawai;
        }
    }

    void tambahProyek(string id_pegawai, string nama_proyek, int durasi) {
        Pegawai* current = pegawai_head;
        while (current) {
            if (current->id == id_pegawai) {
                Proyek* proyek = new Proyek(nama_proyek, durasi);
                proyek->next = current->proyek_head;
                current->proyek_head = proyek;
                return;
            }
            current = current->next;
        }
    }

    void hapusProyek(string id_pegawai, string nama_proyek) {
        Pegawai* current = pegawai_head;
        while (current) {
            if (current->id == id_pegawai) {
                Proyek* proyek = current->proyek_head;
                Proyek* prev = nullptr;
                while (proyek) {
                    if (proyek->nama == nama_proyek) {
                        if (prev) {
                            prev->next = proyek->next;
                        } else {
                            current->proyek_head = proyek->next;
                        }
                        delete proyek;
                        return;
                    }
                    prev = proyek;
                    proyek = proyek->next;
                }
            }
            current = current->next;
        }
    }

    void tampilkanData() {
        Pegawai* current = pegawai_head;
        while (current) {
            cout << "Pegawai: " << current->nama << ", ID: " << current->id << endl;
            Proyek* proyek = current->proyek_head;
            while (proyek) {
                cout << "  Proyek: " << proyek->nama << ", Durasi: " << proyek->durasi << " bulan" << endl;
                proyek = proyek->next;
            }
            current = current->next;
        }
    }
};

int main() {
    ManajemenPegawai manajemen;
    manajemen.tambahPegawai("Andi", "P001");
    manajemen.tambahPegawai("Budi", "P002");
    manajemen.tambahPegawai("Citra", "P003");

    manajemen.tambahProyek("P001", "Aplikasi Mobile", 12);
    manajemen.tambahProyek("P002", "Sistem Akuntansi", 8);
    manajemen.tambahProyek("P003", "E-commerce", 10);

    manajemen.tambahProyek("P001", "Analisis Data", 6);
    manajemen.hapusProyek("P001", "Aplikasi Mobile");

    cout << "Data Pegawai dan Proyek:" << endl;
    manajemen.tampilkanData();

    return 0;
}
#include <iostream>
#include <string>
using namespace std;

struct Proyek {
    string namaProyek;
    int durasi;
    Proyek* proyekBerikutnya;

    Proyek(string nama, int dur) : namaProyek(nama), durasi(dur), proyekBerikutnya(nullptr) {}
};

struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* kepalaProyek;
    Pegawai* pegawaiBerikutnya;

    Pegawai(string nama, string id) : namaPegawai(nama), idPegawai(id), kepalaProyek(nullptr), pegawaiBerikutnya(nullptr) {}
};

class MultiLinkedList {
private:
    Pegawai* kepalaPegawai;

public:
    MultiLinkedList() : kepalaPegawai(nullptr) {}

    void tambahPegawai(string nama, string id) {
        Pegawai* pegawaiBaru = new Pegawai(nama, id);
        if (!kepalaPegawai) {
            kepalaPegawai = pegawaiBaru;
        } else {
            Pegawai* temp = kepalaPegawai;
            while (temp->pegawaiBerikutnya) temp = temp->pegawaiBerikutnya;
            temp->pegawaiBerikutnya = pegawaiBaru;
        }
    }

    void tambahProyek(string id, string namaProyek, int durasi) {
        Pegawai* pegawai = cariPegawai(id);
        if (pegawai) {
            Proyek* proyekBaru = new Proyek(namaProyek, durasi);
            if (!pegawai->kepalaProyek) {
                pegawai->kepalaProyek = proyekBaru;
            } else {
                Proyek* temp = pegawai->kepalaProyek;
                while (temp->proyekBerikutnya) temp = temp->proyekBerikutnya;
                temp->proyekBerikutnya = proyekBaru;
            }
        }
    }

    void hapusProyek(string id, string namaProyek) {
        Pegawai* pegawai = cariPegawai(id);
        if (pegawai && pegawai->kepalaProyek) {
            Proyek* temp = pegawai->kepalaProyek;
            Proyek* prev = nullptr;

            while (temp) {
                if (temp->namaProyek == namaProyek) {
                    if (prev) {
                        prev->proyekBerikutnya = temp->proyekBerikutnya;
                    } else {
                        pegawai->kepalaProyek = temp->proyekBerikutnya;
                    }
                    delete temp;
                    return;
                }
                prev = temp;
                temp = temp->proyekBerikutnya;
            }
        }
    }

    void tampilkanData() {
        Pegawai* temp = kepalaPegawai;
        while (temp) {
            cout << "Pegawai: " << temp->namaPegawai << " (ID: " << temp->idPegawai << ")\n";
            Proyek* proyekTemp = temp->kepalaProyek;
            while (proyekTemp) {
                cout << "  -> Proyek: " << proyekTemp->namaProyek << ", Durasi: " << proyekTemp->durasi << " bulan\n";
                proyekTemp = proyekTemp->proyekBerikutnya;
            }
            temp = temp->pegawaiBerikutnya;
            cout << endl;
        }
    }

private:
    Pegawai* cariPegawai(string id) {
        Pegawai* temp = kepalaPegawai;
        while (temp) {
            if (temp->idPegawai == id) return temp;
            temp = temp->pegawaiBerikutnya;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedList daftar;

    daftar.tambahPegawai("Andi", "P001");
    daftar.tambahPegawai("Budi", "P002");
    daftar.tambahPegawai("Citra", "P003");

    daftar.tambahProyek("P001", "Aplikasi Mobile", 12);
    daftar.tambahProyek("P002", "Sistem Akuntansi", 8);
    daftar.tambahProyek("P003", "E-commerce", 10);

    daftar.tambahProyek("P001", "Analisis Data", 6);

    daftar.hapusProyek("P001", "Aplikasi Mobile");

    cout << "Data Pegawai dan Proyek:\n";
    daftar.tampilkanData();

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

struct NodeProyek {
    string namaProyek;
    int durasi;
    NodeProyek* next;

    NodeProyek(string nama, int dur) : namaProyek(nama), durasi(dur), next(nullptr) {}
};
struct NodePegawai {
    string namaPegawai;
    string idPegawai;
    NodeProyek* headProyek; 
    NodePegawai* next;

    NodePegawai(string nama, string id) : namaPegawai(nama), idPegawai(id), headProyek(nullptr), next(nullptr) {}
};
class MultiLinkedList {
private:
    NodePegawai* headPegawai; 

public:
    MultiLinkedList() : headPegawai(nullptr) {}
    void tambahPegawai(string nama, string id) {
        NodePegawai* pegawaiBaru = new NodePegawai(nama, id);
        pegawaiBaru->next = headPegawai;
        headPegawai = pegawaiBaru;
    }
    void tambahProyek(string idPegawai, string namaProyek, int durasi) {
        NodePegawai* pegawai = cariPegawai(idPegawai);
        if (pegawai) {
            NodeProyek* proyekBaru = new NodeProyek(namaProyek, durasi);
            proyekBaru->next = pegawai->headProyek;
            pegawai->headProyek = proyekBaru;
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }
    void hapusProyek(string idPegawai, string namaProyek) {
        NodePegawai* pegawai = cariPegawai(idPegawai);
        if (pegawai) {
            NodeProyek* prev = nullptr;
            NodeProyek* curr = pegawai->headProyek;
            while (curr) {
                if (curr->namaProyek == namaProyek) {
                    if (prev) {
                        prev->next = curr->next;
                    } else {
                        pegawai->headProyek = curr->next;
                    }
                    delete curr;
                    cout << "Proyek " << namaProyek << " berhasil dihapus dari pegawai " << pegawai->namaPegawai << ".\n";
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
            cout << "Proyek " << namaProyek << " tidak ditemukan pada pegawai " << pegawai->namaPegawai << ".\n";
        } else {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }
    void tampilkanData() {
        NodePegawai* pegawai = headPegawai;
        while (pegawai) {
            cout << "Pegawai: " << pegawai->namaPegawai << " (ID: " << pegawai->idPegawai << ")\n";
            NodeProyek* proyek = pegawai->headProyek;
            if (!proyek) {
                cout << "  Tidak ada proyek.\n";
            }
            while (proyek) {
                cout << "  - Proyek: " << proyek->namaProyek << ", Durasi: " << proyek->durasi << " bulan\n";
                proyek = proyek->next;
            }
            pegawai = pegawai->next;
        }
    }

private:
    NodePegawai* cariPegawai(string id) {
        NodePegawai* curr = headPegawai;
        while (curr) {
            if (curr->idPegawai == id) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }
};
int main() {
    MultiLinkedList daftarPegawai;

    daftarPegawai.tambahPegawai("Andi", "P001");
    daftarPegawai.tambahPegawai("Budi", "P002");
    daftarPegawai.tambahPegawai("Citra", "P003");

    daftarPegawai.tambahProyek("P001", "Aplikasi Mobile", 12);
    daftarPegawai.tambahProyek("P002", "Sistem Akuntansi", 8);
    daftarPegawai.tambahProyek("P003", "E-commerce", 10);

    daftarPegawai.tambahProyek("P001", "Analisis Data", 6);

    daftarPegawai.hapusProyek("P001", "Aplikasi Mobile");

    cout << "\nData Pegawai dan Proyek:\n";
    daftarPegawai.tampilkanData();

    return 0;
}

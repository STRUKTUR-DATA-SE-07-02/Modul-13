#include <iostream>
#include <string>
using namespace std;

struct NodeBuku {
    string judulBuku;
    string tanggalPengembalian;
    NodeBuku* next;

    NodeBuku(string judul, string tanggal) : judulBuku(judul), tanggalPengembalian(tanggal), next(nullptr) {}
};
struct NodeAnggota {
    string namaAnggota;
    string idAnggota;
    NodeBuku* headBuku; 
    NodeAnggota* next;

    NodeAnggota(string nama, string id) : namaAnggota(nama), idAnggota(id), headBuku(nullptr), next(nullptr) {}
};

class MultiLinkedList {
private:
    NodeAnggota* headAnggota; 
public:
    MultiLinkedList() : headAnggota(nullptr) {}
    void tambahAnggota(string nama, string id) {
        NodeAnggota* anggotaBaru = new NodeAnggota(nama, id);
        anggotaBaru->next = headAnggota;
        headAnggota = anggotaBaru;
    }
    void tambahBuku(string idAnggota, string judulBuku, string tanggalPengembalian) {
        NodeAnggota* anggota = cariAnggota(idAnggota);
        if (anggota) {
            NodeBuku* bukuBaru = new NodeBuku(judulBuku, tanggalPengembalian);
            bukuBaru->next = anggota->headBuku;
            anggota->headBuku = bukuBaru;
        } else {
            cout << "Anggota dengan ID " << idAnggota << " tidak ditemukan.\n";
        }
    }
    void hapusAnggota(string idAnggota) {
        NodeAnggota* prev = nullptr;
        NodeAnggota* curr = headAnggota;
        while (curr) {
            if (curr->idAnggota == idAnggota) {
                hapusSemuaBuku(curr);
                if (prev) {
                    prev->next = curr->next;
                } else {
                    headAnggota = curr->next;
                }
                delete curr;
                cout << "Anggota dengan ID " << idAnggota << " berhasil dihapus beserta buku yang dipinjam.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Anggota dengan ID " << idAnggota << " tidak ditemukan.\n";
    }
    void tampilkanData() {
        NodeAnggota* anggota = headAnggota;
        while (anggota) {
            cout << "Anggota: " << anggota->namaAnggota << " (ID: " << anggota->idAnggota << ")\n";
            NodeBuku* buku = anggota->headBuku;
            if (!buku) {
                cout << "  Tidak ada buku yang dipinjam.\n";
            }
            while (buku) {
                cout << "  - Buku: " << buku->judulBuku << ", Pengembalian: " << buku->tanggalPengembalian << "\n";
                buku = buku->next;
            }
            anggota = anggota->next;
        }
    }

private:
    NodeAnggota* cariAnggota(string id) {
        NodeAnggota* curr = headAnggota;
        while (curr) {
            if (curr->idAnggota == id) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }
    void hapusSemuaBuku(NodeAnggota* anggota) {
        NodeBuku* curr = anggota->headBuku;
        while (curr) {
            NodeBuku* temp = curr;
            curr = curr->next;
            delete temp;
        }
        anggota->headBuku = nullptr;
    }
};

int main() {
    MultiLinkedList daftarAnggota;

    daftarAnggota.tambahAnggota("Rani", "A001");
    daftarAnggota.tambahAnggota("Dito", "A002");
    daftarAnggota.tambahAnggota("Vina", "A003");

    daftarAnggota.tambahBuku("A001", "Pemrograman C++", "01/12/2024");
    daftarAnggota.tambahBuku("A002", "Algoritma Pemrograman", "15/12/2024");

    daftarAnggota.tambahBuku("A001", "Struktur Data", "10/12/2024");

    daftarAnggota.hapusAnggota("A002");

    cout << "\nData Anggota dan Buku yang Dipinjam:\n";
    daftarAnggota.tampilkanData();

    return 0;
}

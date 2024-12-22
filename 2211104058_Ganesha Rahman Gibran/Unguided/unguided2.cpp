#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* nextBuku;
};

struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* daftarBuku;
    Anggota* nextAnggota;
};

class MultiLinkedList {
private:
    Anggota* head;

public:
    MultiLinkedList() : head(nullptr) {}

    void tambahAnggota(string nama, string id) {
        Anggota* anggotaBaru = new Anggota{nama, id, nullptr, head};
        head = anggotaBaru;
    }

    void tambahBuku(string idAnggota, string judulBuku, string tanggalPengembalian) {
        Anggota* anggota = cariAnggota(idAnggota);
        if (anggota) {
            Buku* bukuBaru = new Buku{judulBuku, tanggalPengembalian, anggota->daftarBuku};
            anggota->daftarBuku = bukuBaru;
        } else {
            cout << "Anggota dengan ID " << idAnggota << " tidak ditemukan.\n";
        }
    }

    void hapusAnggota(string idAnggota) {
        Anggota* prev = nullptr;
        Anggota* curr = head;

        while (curr) {
            if (curr->idAnggota == idAnggota) {
                if (prev) {
                    prev->nextAnggota = curr->nextAnggota;
                } else {
                    head = curr->nextAnggota;
                }

                // Hapus semua buku yang dipinjam oleh anggota ini
                Buku* bukuCurr = curr->daftarBuku;
                while (bukuCurr) {
                    Buku* temp = bukuCurr;
                    bukuCurr = bukuCurr->nextBuku;
                    delete temp;
                }

                delete curr;
                cout << "Anggota dengan ID " << idAnggota << " beserta buku yang dipinjam telah dihapus.\n";
                return;
            }
            prev = curr;
            curr = curr->nextAnggota;
        }
        cout << "Anggota dengan ID " << idAnggota << " tidak ditemukan.\n";
    }

    void tampilkanData() {
        Anggota* currAnggota = head;
        while (currAnggota) {
            cout << "Nama Anggota: " << currAnggota->namaAnggota << ", ID: " << currAnggota->idAnggota << "\n";
            Buku* currBuku = currAnggota->daftarBuku;
            while (currBuku) {
                cout << "  - Buku: " << currBuku->judulBuku << ", Pengembalian: " << currBuku->tanggalPengembalian << "\n";
                currBuku = currBuku->nextBuku;
            }
            currAnggota = currAnggota->nextAnggota;
        }
    }

private:
    Anggota* cariAnggota(string idAnggota) {
        Anggota* curr = head;
        while (curr) {
            if (curr->idAnggota == idAnggota) {
                return curr;
            }
            curr = curr->nextAnggota;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedList mll;

    mll.tambahAnggota("Rani", "A001");
    mll.tambahAnggota("Dito", "A002");
    mll.tambahAnggota("Vina", "A003");

    mll.tambahBuku("A001", "Pemrograman C++", "01/12/2024");
    mll.tambahBuku("A002", "Algoritma Pemrograman", "15/12/2024");

    mll.tambahBuku("A001", "Struktur Data", "10/12/2024");

    mll.hapusAnggota("A002");

    mll.tampilkanData();

    return 0;
}

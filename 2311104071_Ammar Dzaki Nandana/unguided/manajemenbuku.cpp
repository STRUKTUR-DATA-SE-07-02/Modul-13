#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* next;
};

struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* bukuHead;
    Anggota* next;
};

class MultiLinkedListPerpustakaan {
private:
    Anggota* head;

public:
    MultiLinkedListPerpustakaan() : head(nullptr) {}

    void tambahAnggota(string nama, string id) {
        Anggota* anggotaBaru = new Anggota{nama, id, nullptr, head};
        head = anggotaBaru;
    }

    void tambahBuku(string idAnggota, string judul, string tanggal) {
        Anggota* anggota = cariAnggota(idAnggota);
        if (anggota) {
            Buku* bukuBaru = new Buku{judul, tanggal, anggota->bukuHead};
            anggota->bukuHead = bukuBaru;
        } else {
            cout << "Anggota dengan ID " << idAnggota << " tidak ditemukan.\n";
        }
    }

    void hapusAnggota(string idAnggota) {
        Anggota* current = head;
        Anggota* prev = nullptr;
        while (current && current->idAnggota != idAnggota) {
            prev = current;
            current = current->next;
        }
        if (current) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            Buku* bukuCurrent = current->bukuHead;
            while (bukuCurrent) {
                Buku* temp = bukuCurrent;
                bukuCurrent = bukuCurrent->next;
                delete temp;
            }
            delete current;
            cout << "Anggota dengan ID " << idAnggota << " berhasil dihapus.\n";
        } else {
            cout << "Anggota dengan ID " << idAnggota << " tidak ditemukan.\n";
        }
    }

    void tampilkanData() {
        Anggota* currentAnggota = head;
        while (currentAnggota) {
            cout << "Anggota: " << currentAnggota->namaAnggota
                 << " (ID: " << currentAnggota->idAnggota << ")\n";
            Buku* currentBuku = currentAnggota->bukuHead;
            while (currentBuku) {
                cout << "  - Buku: " << currentBuku->judulBuku
                     << ", Pengembalian: " << currentBuku->tanggalPengembalian << "\n";
                currentBuku = currentBuku->next;
            }
            currentAnggota = currentAnggota->next;
        }
    }

private:
    Anggota* cariAnggota(string id) {
        Anggota* current = head;
        while (current) {
            if (current->idAnggota == id) return current;
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedListPerpustakaan perpustakaan;

    // Tambah Anggota
    perpustakaan.tambahAnggota("Rani", "A001");
    perpustakaan.tambahAnggota("Dito", "A002");
    perpustakaan.tambahAnggota("Vina", "A003");

    // Tambah Buku
    perpustakaan.tambahBuku("A001", "Pemrograman C++", "01/12/2024");
    perpustakaan.tambahBuku("A002", "Algoritma Pemrograman", "15/12/2024");
    perpustakaan.tambahBuku("A001", "Struktur Data", "10/12/2024");

    // Hapus Anggota
    perpustakaan.hapusAnggota("A002");

    // Tampilkan Data
    perpustakaan.tampilkanData();

    return 0;
}

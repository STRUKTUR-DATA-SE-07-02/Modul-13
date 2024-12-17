#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string judulBuku;
    string tanggalPengembalian;
    Buku* bukuBerikutnya;

    Buku(string judul, string tanggal) : judulBuku(judul), tanggalPengembalian(tanggal), bukuBerikutnya(nullptr) {}
};

struct Anggota {
    string namaAnggota;
    string idAnggota;
    Buku* kepalaBuku;
    Anggota* anggotaBerikutnya;

    Anggota(string nama, string id) : namaAnggota(nama), idAnggota(id), kepalaBuku(nullptr), anggotaBerikutnya(nullptr) {}
};

class MultiLinkedList {
private:
    Anggota* kepalaAnggota;

public:
    MultiLinkedList() : kepalaAnggota(nullptr) {}

    void tambahAnggota(string nama, string id) {
        Anggota* anggotaBaru = new Anggota(nama, id);
        if (!kepalaAnggota) {
            kepalaAnggota = anggotaBaru;
        } else {
            Anggota* temp = kepalaAnggota;
            while (temp->anggotaBerikutnya) temp = temp->anggotaBerikutnya;
            temp->anggotaBerikutnya = anggotaBaru;
        }
    }

    void tambahBuku(string id, string judulBuku, string tanggalPengembalian) {
        Anggota* anggota = cariAnggota(id);
        if (anggota) {
            Buku* bukuBaru = new Buku(judulBuku, tanggalPengembalian);
            if (!anggota->kepalaBuku) {
                anggota->kepalaBuku = bukuBaru;
            } else {
                Buku* temp = anggota->kepalaBuku;
                while (temp->bukuBerikutnya) temp = temp->bukuBerikutnya;
                temp->bukuBerikutnya = bukuBaru;
            }
        }
    }

    void hapusAnggota(string id) {
        Anggota* temp = kepalaAnggota;
        Anggota* prev = nullptr;

        while (temp) {
            if (temp->idAnggota == id) {
                Buku* bukuTemp = temp->kepalaBuku;
                while (bukuTemp) {
                    Buku* hapus = bukuTemp;
                    bukuTemp = bukuTemp->bukuBerikutnya;
                    delete hapus;
                }

                if (prev) {
                    prev->anggotaBerikutnya = temp->anggotaBerikutnya;
                } else {
                    kepalaAnggota = temp->anggotaBerikutnya;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->anggotaBerikutnya;
        }
    }

    void tampilkanData() {
        Anggota* temp = kepalaAnggota;
        while (temp) {
            cout << "Anggota: " << temp->namaAnggota << " (ID: " << temp->idAnggota << ")\n";
            Buku* bukuTemp = temp->kepalaBuku;
            while (bukuTemp) {
                cout << "  -> Buku: " << bukuTemp->judulBuku << ", Pengembalian: " << bukuTemp->tanggalPengembalian << "\n";
                bukuTemp = bukuTemp->bukuBerikutnya;
            }
            temp = temp->anggotaBerikutnya;
            cout << endl;
        }
    }

private:
    Anggota* cariAnggota(string id) {
        Anggota* temp = kepalaAnggota;
        while (temp) {
            if (temp->idAnggota == id) return temp;
            temp = temp->anggotaBerikutnya;
        }
        return nullptr;
    }
};

int main() {
    MultiLinkedList perpustakaan;

    // 1. Menambahkan anggota
    perpustakaan.tambahAnggota("Rani", "A001");
    perpustakaan.tambahAnggota("Dito", "A002");
    perpustakaan.tambahAnggota("Vina", "A003");

    // 2. Menambahkan buku yang dipinjam
    perpustakaan.tambahBuku("A001", "Pemrograman C++", "01/12/2024");
    perpustakaan.tambahBuku("A002", "Algoritma Pemrograman", "15/12/2024");

    // 3. Menambahkan buku baru
    perpustakaan.tambahBuku("A001", "Struktur Data", "10/12/2024");

    // 4. Menghapus anggota Dito
    perpustakaan.hapusAnggota("A002");

    // 5. Menampilkan data anggota dan buku yang dipinjam
    cout << "Data Anggota dan Buku yang Dipinjam:\n";
    perpustakaan.tampilkanData();

    return 0;
}
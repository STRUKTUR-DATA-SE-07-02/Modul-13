#include <iostream>
#include <string>

using namespace std;

class Buku {
public:
    string judul;
    string tanggal_pengembalian;
    Buku* next;

    Buku(string j, string t) : judul(j), tanggal_pengembalian(t), next(nullptr) {}
};

class Anggota {
public:
    string nama;
    string id;
    Buku* buku_head;
    Anggota* next;

    Anggota(string n, string i) : nama(n), id(i), buku_head(nullptr), next(nullptr) {}
};

class ManajemenPerpustakaan {
private:
    Anggota* anggota_head;

public:
    ManajemenPerpustakaan() : anggota_head(nullptr) {}

    void tambahAnggota(string nama, string id) {
        Anggota* anggota = new Anggota(nama, id);
        if (!anggota_head) {
            anggota_head = anggota;
        } else {
            Anggota* current = anggota_head;
            while (current->next) {
                current = current->next;
            }
            current->next = anggota;
        }
    }

    void tambahBuku(string id_anggota, string judul, string tanggal_pengembalian) {
        Anggota* current = anggota_head;
        while (current) {
            if (current->id == id_anggota) {
                Buku* buku = new Buku(judul, tanggal_pengembalian);
                buku->next = current->buku_head;
                current->buku_head = buku;
                return;
            }
            current = current->next;
        }
    }

    void hapusAnggota(string id_anggota) {
        Anggota* current = anggota_head;
        Anggota* prev = nullptr;
        while (current) {
            if (current->id == id_anggota) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    anggota_head = current->next;
                }
                Buku* buku = current->buku_head;
                while (buku) {
                    Buku* temp = buku;
                    buku = buku->next;
                    delete temp;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void tampilkanData() {
        Anggota* current = anggota_head;
        while (current) {
            cout << "Anggota: " << current->nama << ", ID: " << current->id << endl;
            Buku* buku = current->buku_head;
            while (buku) {
                cout << "  Buku: " << buku->judul << ", Tanggal Pengembalian: " << buku->tanggal_pengembalian << endl;
                buku = buku->next;
            }
            current = current->next;
        }
    }
};


int main() {
    ManajemenPerpustakaan manajemen;
    manajemen.tambahAnggota("Rani", "A001");
    manajemen.tambahAnggota("Dito", "A002");
    manajemen.tambahAnggota("Vina", "A003");

    manajemen.tambahBuku("A001", "Pemrograman C++", "01/12/2024");
    manajemen.tambahBuku("A002", "Algoritma Pemrograman", "15/12/2024");
    manajemen.tambahBuku("A001", "Struktur Data", "10/12/2024");

    manajemen.hapusAnggota("A002");

    cout << "Data Anggota dan Buku yang Dipinjam:" << endl;
    manajemen.tampilkanData();

    return 0;
}
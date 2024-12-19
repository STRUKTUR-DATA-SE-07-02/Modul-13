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

class MultiLinkedList {
private:
    Anggota* head;

public:
    MultiLinkedList() : head(nullptr) {}

    void tambahAnggota(string nama, string id) {
        Anggota* newAnggota = new Anggota{nama, id, nullptr, nullptr};
        if (!head) {
            head = newAnggota;
        } else {
            Anggota* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newAnggota;
        }
    }

    void tambahBuku(string id, string judulBuku, string tanggalPengembalian) {
        Anggota* temp = head;
        while (temp && temp->idAnggota != id) temp = temp->next;
        if (temp) {
            Buku* newBuku = new Buku{judulBuku, tanggalPengembalian, nullptr};
            if (!temp->bukuHead) {
                temp->bukuHead = newBuku;
            } else {
                Buku* bTemp = temp->bukuHead;
                while (bTemp->next) bTemp = bTemp->next;
                bTemp->next = newBuku;
            }
        }
    }

    void hapusAnggota(string id) {
        Anggota* temp = head;
        Anggota* prev = nullptr;
        while (temp && temp->idAnggota != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp) {
            if (!prev) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            Buku* bTemp = temp->bukuHead;
            while (bTemp) {
                Buku* toDelete = bTemp;
                bTemp = bTemp->next;
                delete toDelete;
            }
            delete temp;
        }
    }

    void tampilkanData() {
        Anggota* temp = head;
        while (temp) {
            cout << "Anggota: " << temp->namaAnggota << " (" << temp->idAnggota << ")\n";
            Buku* bTemp = temp->bukuHead;
            while (bTemp) {
                cout << "  - Buku: " << bTemp->judulBuku << ", Pengembalian: " << bTemp->tanggalPengembalian << "\n";
                bTemp = bTemp->next;
            }
            temp = temp->next;
        }
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
#include <iostream>
#include <string>
using namespace std;

struct Proyek {
    string namaProyek;
    int durasi;
    Proyek* next;
};

struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* proyekHead;
    Pegawai* next;
};

class MultiLinkedList {
private:
    Pegawai* head;

public:
    MultiLinkedList() : head(nullptr) {}

    void tambahPegawai(string nama, string id) {
        Pegawai* newPegawai = new Pegawai{nama, id, nullptr, nullptr};
        if (!head) {
            head = newPegawai;
        } else {
            Pegawai* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newPegawai;
        }
    }

    void tambahProyek(string id, string namaProyek, int durasi) {
        Pegawai* temp = head;
        while (temp && temp->idPegawai != id) temp = temp->next;
        if (temp) {
            Proyek* newProyek = new Proyek{namaProyek, durasi, nullptr};
            if (!temp->proyekHead) {
                temp->proyekHead = newProyek;
            } else {
                Proyek* pTemp = temp->proyekHead;
                while (pTemp->next) pTemp = pTemp->next;
                pTemp->next = newProyek;
            }
        }
    }

    void hapusProyek(string id, string namaProyek) {
        Pegawai* temp = head;
        while (temp && temp->idPegawai != id) temp = temp->next;
        if (temp) {
            Proyek* pTemp = temp->proyekHead;
            Proyek* prev = nullptr;
            while (pTemp && pTemp->namaProyek != namaProyek) {
                prev = pTemp;
                pTemp = pTemp->next;
            }
            if (pTemp) {
                if (!prev) {
                    temp->proyekHead = pTemp->next;
                } else {
                    prev->next = pTemp->next;
                }
                delete pTemp;
            }
        }
    }

    void tampilkanData() {
        Pegawai* temp = head;
        while (temp) {
            cout << "Pegawai: " << temp->namaPegawai << " (" << temp->idPegawai << ")\n";
            Proyek* pTemp = temp->proyekHead;
            while (pTemp) {
                cout << "  - Proyek: " << pTemp->namaProyek << ", Durasi: " << pTemp->durasi << " bulan\n";
                pTemp = pTemp->next;
            }
            temp = temp->next;
        }
    }
};

int main() {
    MultiLinkedList mll;

    mll.tambahPegawai("Andi", "P001");
    mll.tambahPegawai("Budi", "P002");
    mll.tambahPegawai("Citra", "P003");

    mll.tambahProyek("P001", "Aplikasi Mobile", 12);
    mll.tambahProyek("P002", "Sistem Akuntansi", 8);
    mll.tambahProyek("P003", "E-commerce", 10);
    mll.tambahProyek("P001", "Analisis Data", 6);

    mll.hapusProyek("P001", "Aplikasi Mobile");

    mll.tampilkanData();

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

// Struktur untuk menyimpan data proyek
struct Proyek {
    string namaProyek;
    int durasi;
    Proyek* nextProyek;
};

// Struktur untuk menyimpan data pegawai
struct Pegawai {
    string namaPegawai;
    string idPegawai;
    Proyek* proyekHead;
    Pegawai* nextPegawai;
};

// Fungsi untuk membuat node pegawai baru
Pegawai* buatPegawai(string nama, string id) {
    Pegawai* pegawaiBaru = new Pegawai;
    pegawaiBaru->namaPegawai = nama;
    pegawaiBaru->idPegawai = id;
    pegawaiBaru->proyekHead = nullptr;
    pegawaiBaru->nextPegawai = nullptr;
    return pegawaiBaru;
}

// Fungsi untuk membuat node proyek baru
Proyek* buatProyek(string nama, int durasi) {
    Proyek* proyekBaru = new Proyek;
    proyekBaru->namaProyek = nama;
    proyekBaru->durasi = durasi;
    proyekBaru->nextProyek = nullptr;
    return proyekBaru;
}

// Fungsi untuk menambahkan proyek ke seorang pegawai
void tambahProyek(Pegawai* pegawai, string namaProyek, int durasi) {
    Proyek* proyekBaru = buatProyek(namaProyek, durasi);
    proyekBaru->nextProyek = pegawai->proyekHead;
    pegawai->proyekHead = proyekBaru;
}

// Fungsi untuk menghapus proyek tertentu dari seorang pegawai
void hapusProyek(Pegawai* pegawai, string namaProyek) {
    Proyek* temp = pegawai->proyekHead;
    Proyek* prev = nullptr;

    while (temp != nullptr && temp->namaProyek != namaProyek) {
        prev = temp;
        temp = temp->nextProyek;
    }

    if (temp == nullptr) {
        cout << "Proyek " << namaProyek << " tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        pegawai->proyekHead = temp->nextProyek;
    } else {
        prev->nextProyek = temp->nextProyek;
    }
    delete temp;
    cout << "Proyek " << namaProyek << " berhasil dihapus.\n";
}

// Fungsi untuk menampilkan data pegawai dan proyek mereka
void tampilkanData(Pegawai* head) {
    Pegawai* tempPegawai = head;
    while (tempPegawai != nullptr) {
        cout << "Pegawai: " << tempPegawai->namaPegawai << " (ID: " << tempPegawai->idPegawai << ")\n";
        Proyek* tempProyek = tempPegawai->proyekHead;

        if (tempProyek == nullptr) {
            cout << "  Tidak ada proyek.\n";
        } else {
            while (tempProyek != nullptr) {
                cout << "  - Proyek: " << tempProyek->namaProyek << ", Durasi: " << tempProyek->durasi << " bulan\n";
                tempProyek = tempProyek->nextProyek;
            }
        }
        tempPegawai = tempPegawai->nextPegawai;
        cout << endl;
    }
}

// Fungsi untuk mencari pegawai berdasarkan ID
Pegawai* cariPegawai(Pegawai* head, string id) {
    Pegawai* temp = head;
    while (temp != nullptr) {
        if (temp->idPegawai == id) {
            return temp;
        }
        temp = temp->nextPegawai;
    }
    return nullptr;
}

int main() {
    Pegawai* head = nullptr;
    Pegawai* tail = nullptr;

    int pilihan;
    do {
        cout << "\n=== Menu Manajemen Data Pegawai dan Proyek ===\n";
        cout << "1. Memasukkan Data Pegawai\n";
        cout << "2. Menambahkan Proyek ke Pegawai\n";
        cout << "3. Menambahkan Proyek Baru\n";
        cout << "4. Menghapus Proyek dari Pegawai\n";
        cout << "5. Tampilkan Data Pegawai dan Proyek\n";
        cout << "6. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nama, id;
            cout << "Masukkan Nama Pegawai: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan ID Pegawai: ";
            cin >> id;

            Pegawai* pegawaiBaru = buatPegawai(nama, id);
            if (head == nullptr) {
                head = tail = pegawaiBaru;
            } else {
                tail->nextPegawai = pegawaiBaru;
                tail = pegawaiBaru;
            }
            cout << "Pegawai berhasil ditambahkan.\n";
        } else if (pilihan == 2 || pilihan == 3) {
            string idPegawai, namaProyek;
            int durasi;

            cout << "Masukkan ID Pegawai: ";
            cin >> idPegawai;
            Pegawai* pegawai = cariPegawai(head, idPegawai);

            if (pegawai != nullptr) {
                cout << "Masukkan Nama Proyek: ";
                cin.ignore();
                getline(cin, namaProyek);
                cout << "Masukkan Durasi Proyek (bulan): ";
                cin >> durasi;

                tambahProyek(pegawai, namaProyek, durasi);
                cout << "Proyek berhasil ditambahkan.\n";
            } else {
                cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
            }
        } else if (pilihan == 4) {
            string idPegawai, namaProyek;

            cout << "Masukkan ID Pegawai: ";
            cin >> idPegawai;
            Pegawai* pegawai = cariPegawai(head, idPegawai);

            if (pegawai != nullptr) {
                cout << "Masukkan Nama Proyek yang akan dihapus: ";
                cin.ignore();
                getline(cin, namaProyek);

                hapusProyek(pegawai, namaProyek);
            } else {
                cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
            }
        } else if (pilihan == 5) {
            tampilkanData(head);
        } \else if (pilihan == 6) {
            cout << "Program selesai. Terima kasih!\n";
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (pilihan != 6);

    return 0;
}

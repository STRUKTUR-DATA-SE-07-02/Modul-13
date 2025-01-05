#include <iostream>
#include <string>
using namespace std;

struct Tugas {
    string namaTugas;
    int durasiTugas;
    Tugas* tugasBerikutnya;
};

struct Karyawan {
    string namaKaryawan;
    string idKaryawan;
    Tugas* kepalaTugas;
    Karyawan* karyawanBerikutnya;
};

Karyawan* kepalaKaryawan = nullptr;

void tambahKaryawan(string nama, string id) {
    Karyawan* karyawanBaru = new Karyawan;
    karyawanBaru->namaKaryawan = nama;
    karyawanBaru->idKaryawan = id;
    karyawanBaru->kepalaTugas = nullptr;
    karyawanBaru->karyawanBerikutnya = kepalaKaryawan;
    kepalaKaryawan = karyawanBaru;
}

void tambahTugas(string idKaryawan, string namaTugas, int durasi) {
    Karyawan* karyawanSaatIni = kepalaKaryawan;
    while (karyawanSaatIni != nullptr) {
        if (karyawanSaatIni->idKaryawan == idKaryawan) {
            Tugas* tugasBaru = new Tugas;
            tugasBaru->namaTugas = namaTugas;
            tugasBaru->durasiTugas = durasi;
            tugasBaru->tugasBerikutnya = karyawanSaatIni->kepalaTugas;
            karyawanSaatIni->kepalaTugas = tugasBaru;
            return;
        }
        karyawanSaatIni = karyawanSaatIni->karyawanBerikutnya;
    }
    cout << "Karyawan dengan ID : " << idKaryawan << " tidak dapat ditemukan!\n";
}

void hapusTugas(string idKaryawan, string namaTugas) {
    Karyawan* karyawanSaatIni = kepalaKaryawan;
    while (karyawanSaatIni != nullptr) {
        if (karyawanSaatIni->idKaryawan == idKaryawan) {
            Tugas* tugasSaatIni = karyawanSaatIni->kepalaTugas;
            Tugas* tugasSebelumnya = nullptr;
            while (tugasSaatIni != nullptr) {
                if (tugasSaatIni->namaTugas == namaTugas) {
                    if (tugasSebelumnya == nullptr) {
                        karyawanSaatIni->kepalaTugas = tugasSaatIni->tugasBerikutnya;
                    } else {
                        tugasSebelumnya->tugasBerikutnya = tugasSaatIni->tugasBerikutnya;
                    }
                    delete tugasSaatIni;
                    return;
                }
                tugasSebelumnya = tugasSaatIni;
                tugasSaatIni = tugasSaatIni->tugasBerikutnya;
            }
        }
        karyawanSaatIni = karyawanSaatIni->karyawanBerikutnya;
    }
    cout << "Tugas : " << namaTugas << " tidak ditemukan untuk karyawan dengan ID : " << idKaryawan << "!\n";
}

void tampilkanData() {
    Karyawan* karyawanSaatIni = kepalaKaryawan;
    while (karyawanSaatIni != nullptr) {
        cout << "Karyawan : " << karyawanSaatIni->namaKaryawan << " (ID: " << karyawanSaatIni->idKaryawan << ")\n";
        Tugas* tugasSaatIni = karyawanSaatIni->kepalaTugas;
        while (tugasSaatIni != nullptr) {
            cout << "  Tugas : " << tugasSaatIni->namaTugas << " (Durasi : " << tugasSaatIni->durasiTugas << " bulan)\n";
            tugasSaatIni = tugasSaatIni->tugasBerikutnya;
        }
        karyawanSaatIni = karyawanSaatIni->karyawanBerikutnya;
    }
}

//int main() {
//    int menu;
//    do {
//        cout << "Program Management Data Pegawai dan Proyek";
//        cout << "\nMenu:\n";
//        cout << "1. Tambah Nama Karyawan\n";
//        cout << "2. Tambah Nama Tugas\n";
//        cout << "3. Hapus Nama Tugas\n";
//        cout << "4. Tampilkan Data Karyawan & Tugas\n";
//        cout << "5. Keluar\n";
//        cout << "Menu: ";
//        cin >> menu;
//        cin.ignore();
//
//        if (menu == 1) {
//            string nama, id;
//            cout << "Masukkan Nama Karyawan : ";
//            getline(cin, nama);
//            cout << "Masukkan ID Karyawan : ";
//            getline(cin, id);
//            tambahKaryawan(nama, id);
//        } else if (menu == 2) {
//            string id, namaTugas;
//            int durasi;
//            cout << "Masukkan ID Karyawan : ";
//            getline(cin, id);
//            cout << "Masukkan Nama Tugas : ";
//            getline(cin, namaTugas);
//            cout << "Masukkan Durasi Tugas (bulan) : ";
//            cin >> durasi;
//            cin.ignore();
//            tambahTugas(id, namaTugas, durasi);
//        } else if (menu == 3) {
//            string id, namaTugas;
//            cout << "Masukkan ID Karyawan : ";
//            getline(cin, id);
//            cout << "Masukkan Nama Tugas yang akan dihapus : ";
//            getline(cin, namaTugas);
//            hapusTugas(id, namaTugas);
//        } else if (menu == 4) {
//            tampilkanData();
//        } else if (menu != 5) {
//            cout << "Pilihan tidak tersedia.\n";
//        }
//    } while (menu != 5);
//
//    return 0;
//}

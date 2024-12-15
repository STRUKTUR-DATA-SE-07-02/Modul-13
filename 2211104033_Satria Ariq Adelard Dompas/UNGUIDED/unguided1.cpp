#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Proyek
{
    string namaProyek;
    int durasi;
    Proyek *next;
};

struct Pegawai
{
    string namaPegawai;
    string idPegawai;
    Proyek *proyekHead;
    Pegawai *next;
};

class ManajemenData
{
private:
    Pegawai *head;

public:
    ManajemenData() : head(nullptr) {}

    void tambahPegawai(const string &nama, const string &id)
    {
        Pegawai *pegawaiBaru = new Pegawai{nama, id, nullptr, head};
        head = pegawaiBaru;
    }

    void tambahProyek(const string &idPegawai, const string &namaProyek, int durasi)
    {
        Pegawai *pegawai = cariPegawai(idPegawai);
        if (pegawai)
        {
            Proyek *proyekBaru = new Proyek{namaProyek, durasi, pegawai->proyekHead};
            pegawai->proyekHead = proyekBaru;
        }
        else
        {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void hapusProyek(const string &idPegawai, const string &namaProyek)
    {
        Pegawai *pegawai = cariPegawai(idPegawai);
        if (pegawai)
        {
            Proyek *prev = nullptr;
            Proyek *current = pegawai->proyekHead;

            while (current && current->namaProyek != namaProyek)
            {
                prev = current;
                current = current->next;
            }

            if (current)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    pegawai->proyekHead = current->next;
                }
                delete current;
                cout << "Proyek " << namaProyek << " berhasil dihapus dari pegawai " << idPegawai << ".\n";
            }
            else
            {
                cout << "Proyek " << namaProyek << " tidak ditemukan pada pegawai " << idPegawai << ".\n";
            }
        }
        else
        {
            cout << "Pegawai dengan ID " << idPegawai << " tidak ditemukan.\n";
        }
    }

    void tampilkanData()
    {
        Pegawai *currentPegawai = head;
        cout << left << setw(20) << "Nama Pegawai" << setw(10) << "ID" << "Proyek dan Durasi" << endl;
        cout << string(50, '-') << endl;
        while (currentPegawai)
        {
            cout << left << setw(20) << currentPegawai->namaPegawai << setw(10) << currentPegawai->idPegawai;
            Proyek *currentProyek = currentPegawai->proyekHead;
            if (!currentProyek)
            {
                cout << "Tidak ada proyek";
            }
            cout << endl;
            while (currentProyek)
            {
                cout << right << setw(30) << "- " << currentProyek->namaProyek << " (" << currentProyek->durasi << " bulan)\n";
                currentProyek = currentProyek->next;
            }
            currentPegawai = currentPegawai->next;
            cout << endl;
        }
    }

private:
    Pegawai *cariPegawai(const string &idPegawai)
    {
        Pegawai *current = head;
        while (current)
        {
            if (current->idPegawai == idPegawai)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main()
{
    ManajemenData manajemen;

    // Tambahkan data pegawai
    manajemen.tambahPegawai("Andi", "P001");
    manajemen.tambahPegawai("Budi", "P002");
    manajemen.tambahPegawai("Citra", "P003");

    // Tambahkan proyek ke pegawai
    manajemen.tambahProyek("P001", "Aplikasi Mobile", 12);
    manajemen.tambahProyek("P002", "Sistem Akuntansi", 8);
    manajemen.tambahProyek("P003", "E-commerce", 10);

    // Tambahkan proyek baru
    manajemen.tambahProyek("P001", "Analisis Data", 6);

    // Hapus proyek "Aplikasi Mobile" dari Andi
    manajemen.hapusProyek("P001", "Aplikasi Mobile");

    // Tampilkan data pegawai dan proyek mereka
    manajemen.tampilkanData();

    return 0;
}
#include <iostream>
#include <string>

struct Buku
{
    std::string judul;
    std::string tanggal_kembali;
    Buku *selanjutnya;
};

struct AnggotaPerpus
{
    std::string nama;
    std::string id;
    Buku *buku_dipinjam;
    AnggotaPerpus *selanjutnya;
};

AnggotaPerpus *entri_depan = nullptr;

void tambah_anggota_perpus(std::string nama, std::string id)
{
    AnggotaPerpus *anggota_baru = new AnggotaPerpus;
    anggota_baru->nama = nama;
    anggota_baru->id = id;
    anggota_baru->buku_dipinjam = nullptr;
    anggota_baru->selanjutnya = nullptr;

    if (entri_depan == nullptr)
    {
        entri_depan = anggota_baru;
    }
    else
    {
        AnggotaPerpus *telusur_anggota = entri_depan;
        while (telusur_anggota->selanjutnya != nullptr)
        {
            telusur_anggota = telusur_anggota->selanjutnya;
        }
        telusur_anggota->selanjutnya = anggota_baru;
    }
}

void tambah_buku(std::string id_anggota, std::string judul, std::string tanggal_kembali)
{
    AnggotaPerpus *telusur_anggota = entri_depan;
    while (telusur_anggota != nullptr)
    {
        if (telusur_anggota->id == id_anggota)
        {
            Buku *buku_baru = new Buku;
            buku_baru->judul = judul;
            buku_baru->tanggal_kembali = tanggal_kembali;
            buku_baru->selanjutnya = nullptr;

            if (telusur_anggota->buku_dipinjam == nullptr)
            {
                telusur_anggota->buku_dipinjam = buku_baru;
            }
            else
            {
                Buku *telusur_buku = telusur_anggota->buku_dipinjam;
                while (telusur_buku->selanjutnya != nullptr)
                {
                    telusur_buku = telusur_buku->selanjutnya;
                }
                telusur_buku->selanjutnya = buku_baru;
            }
            return;
        }
        telusur_anggota = telusur_anggota->selanjutnya;
    }
}

void hapus_seluruh_data(std::string id_anggota)
{
    AnggotaPerpus *telusur_anggota = entri_depan;
    AnggotaPerpus *anggota_sebelumnya = nullptr;
    while (telusur_anggota != nullptr)
    {
        if (telusur_anggota->id == id_anggota)
        {
            Buku *telusur_buku = telusur_anggota->buku_dipinjam;
            while (telusur_buku != nullptr)
            {
                Buku *buku_akan_dihapus = telusur_buku;
                telusur_buku = telusur_buku->selanjutnya;
                delete buku_akan_dihapus;
            }

            if (anggota_sebelumnya != nullptr)
            {
                anggota_sebelumnya->selanjutnya = telusur_anggota->selanjutnya;
            }
            else
            {
                entri_depan = telusur_anggota->selanjutnya;
            }
            delete telusur_anggota;
            break;
        }
        anggota_sebelumnya = telusur_anggota;
        telusur_anggota = telusur_anggota->selanjutnya;
    }
}

// Kode ini sebaiknya tidak disentuh
void tampilkan_semua_anggota()
{
    AnggotaPerpus *daftar_anggota = entri_depan;
    while (daftar_anggota != nullptr)
    {
        std::cout << daftar_anggota->nama << " (" << daftar_anggota->id << ") = ";

        Buku *daftar_buku_dipinjam = daftar_anggota->buku_dipinjam;
        if (daftar_buku_dipinjam == nullptr)
        {
            // pass
        }
        else
        {
            while (daftar_buku_dipinjam != nullptr)
            {
                std::cout << daftar_buku_dipinjam->judul << " <" << daftar_buku_dipinjam->tanggal_kembali << "> -> ";
                daftar_buku_dipinjam = daftar_buku_dipinjam->selanjutnya;
            }
        }

        std::cout << "NULLPTR" << '\n';
        daftar_anggota = daftar_anggota->selanjutnya;
    }
}

int main()
{

    tambah_anggota_perpus("Rani", "A001");
    tambah_anggota_perpus("Dito", "A002");
    tambah_anggota_perpus("Vina", "A003");

    tambah_buku("A001", "Pemrograman C++", "01/12/2024");
    tambah_buku("A002", "Algoritma Pemrograman", "15/12/2024");
    tambah_buku("A001", "Struktur Data", "10/12/2024");

    hapus_seluruh_data("A002");

    tampilkan_semua_anggota();

    return 0;
}
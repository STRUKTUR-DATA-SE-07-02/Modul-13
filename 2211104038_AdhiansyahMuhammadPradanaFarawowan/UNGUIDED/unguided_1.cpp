#include <iostream>
#include <string>

struct Proyek
{
    std::string nama;
    int durasi; // Durasi dalam bulan
    Proyek *selanjutnya;
};

struct Pegawai
{
    std::string nama;
    std::string id;
    Proyek *proyek;
    Pegawai *selanjutnya;
};

Pegawai *awal_simpul = nullptr;

void tambah_pegawai(std::string nama, std::string id) {
    Pegawai *baru = new Pegawai;
    baru->nama = nama;
    baru->id = id;
    baru->proyek = nullptr;
    baru->selanjutnya = nullptr;

    if (awal_simpul == nullptr) {
        awal_simpul = baru;
    } else {
        Pegawai *telusur_pegawai = awal_simpul;
        while (telusur_pegawai->selanjutnya != nullptr) {
            telusur_pegawai = telusur_pegawai->selanjutnya;
        }
        telusur_pegawai->selanjutnya = baru;
    }
}


void tambah_proyek_baru(std::string id_pegawai, std::string nama_proyek_baru, int durasi_proyek) {
    Pegawai *telusur_pegawai = awal_simpul;
    while (telusur_pegawai != nullptr) {
        if (telusur_pegawai->id == id_pegawai) {
            Proyek *proyek_baru = new Proyek;
            proyek_baru->nama = nama_proyek_baru;
            proyek_baru->durasi = durasi_proyek;
            proyek_baru->selanjutnya = nullptr;

            if (telusur_pegawai->proyek == nullptr) {
                telusur_pegawai->proyek = proyek_baru;
            } else {
                Proyek *current_project = telusur_pegawai->proyek;
                while (current_project->selanjutnya != nullptr) {
                    current_project = current_project->selanjutnya;
                }
                current_project->selanjutnya = proyek_baru;
            }
            return;
        }
        telusur_pegawai = telusur_pegawai->selanjutnya;
    }
}


void hapus_proyek(std::string id_pegawai, std::string nama_proyek)
{
    Pegawai *telusur_pegawai = awal_simpul;
    while (telusur_pegawai != nullptr)
    {
        if (telusur_pegawai->id == id_pegawai)
        {
            Proyek *telusur_proyek = telusur_pegawai->proyek;
            while (telusur_proyek->selanjutnya != nullptr)
            {
                if (telusur_proyek->nama == nama_proyek)
                {
                    Proyek *proyek_akan_dihapus = telusur_proyek;
                    telusur_pegawai->proyek = telusur_proyek->selanjutnya;

                    delete proyek_akan_dihapus;
                }

                telusur_proyek = telusur_proyek->selanjutnya;
            }
        }

        telusur_pegawai = telusur_pegawai->selanjutnya;
    }
}

void tampilkan_data()
{
    Pegawai *p = awal_simpul;
    while (p != nullptr)
    {
        std::cout << p->nama << ": ";
        Proyek *proyek_pegawai = p->proyek;
        while (proyek_pegawai != nullptr)
        {
            std::cout << proyek_pegawai->nama << " -> ";
            proyek_pegawai = proyek_pegawai->selanjutnya;
        }
        
        std::cout << "NULLPTR" << '\n';
        p = p->selanjutnya;
    }
}

int main()
{
    tambah_pegawai("Andi", "P001");
    tambah_pegawai("Budi", "P002");
    tambah_pegawai("Citra", "P003");

    tambah_proyek_baru("P001", "Aplikasi Mobile", 12);
    tambah_proyek_baru("P002", "Sistem Akuntansi", 8);
    tambah_proyek_baru("P003", "E-commerce", 10);

    tambah_proyek_baru("P001", "Analisis Data", 6);

    hapus_proyek("P001", "Aplikasi Mobile");
    tampilkan_data();

    return 0;
}

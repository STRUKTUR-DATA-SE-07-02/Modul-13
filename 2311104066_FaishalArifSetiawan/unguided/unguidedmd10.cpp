#include <iostream>
#include <string>

using namespace std;

struct PegawaiNode {
    string nama;
    string id;
    PegawaiNode* next;
    struct ProyekNode* proyekHead;
};

struct ProyekNode {
    string nama;
    int durasi;
    ProyekNode* next;
};

PegawaiNode* createPegawaiNode(string nama, string id) {
    PegawaiNode* newNode = new PegawaiNode;
    newNode->nama = nama;
    newNode->id = id;
    newNode->next = NULL;
    newNode->proyekHead = NULL;
    return newNode;
}

ProyekNode* createProyekNode(string nama, int durasi) {
    ProyekNode* newNode = new ProyekNode;
    newNode->nama = nama;
    newNode->durasi = durasi;
    newNode->next = NULL;
    return newNode;
}

PegawaiNode* addPegawai(PegawaiNode* head, string nama, string id) {
    PegawaiNode* newNode = createPegawaiNode(nama, id);
    if (head == NULL) {
        return newNode;
    }
    PegawaiNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

void addProyek(PegawaiNode* head, string pegawaiID, string namaProyek, int durasi) {
    PegawaiNode* temp = head;
    while (temp != NULL) {
        if (temp->id == pegawaiID) {
            ProyekNode* newProyek = createProyekNode(namaProyek, durasi);
            if (temp->proyekHead == NULL) {
                temp->proyekHead = newProyek;
            } else {
                ProyekNode* proyekTemp = temp->proyekHead;
                while (proyekTemp->next != NULL) {
                    proyekTemp = proyekTemp->next;
                }
                proyekTemp->next = newProyek;
            }
            return;
        }
        temp = temp->next;
    }
}

void removeProyek(PegawaiNode* head, string pegawaiID, string namaProyek) {
    PegawaiNode* temp = head;
    while (temp != NULL) {
        if (temp->id == pegawaiID) {
            ProyekNode* proyekTemp = temp->proyekHead;
            ProyekNode* prev = NULL;
            while (proyekTemp != NULL) {
                if (proyekTemp->nama == namaProyek) {
                    if (prev == NULL) {
                        temp->proyekHead = proyekTemp->next;
                    } else {
                        prev->next = proyekTemp->next;
                    }
                    delete proyekTemp;
                    return;
                }
                prev = proyekTemp;
                proyekTemp = proyekTemp->next;
            }
        }
        temp = temp->next;
    }
}

void displayPegawai(PegawaiNode* head) {
    PegawaiNode* temp = head;
    cout << "\nData Pegawai dan Proyek:\n";
    while (temp != NULL) {
        cout << "Nama Pegawai: " << temp->nama << ", ID: " << temp->id << "\n";
        ProyekNode* proyekTemp = temp->proyekHead;
        if (proyekTemp == NULL) {
            cout << "  - Tidak ada proyek.\n";
        } else {
            while (proyekTemp != NULL) {
                cout << "  - Proyek: " << proyekTemp->nama << ", Durasi: " << proyekTemp->durasi << " bulan\n";
                proyekTemp = proyekTemp->next;
            }
        }
        temp = temp->next;
    }
}

int main() {
    PegawaiNode* headPegawai = NULL;

    // 1. Masukkan data pegawai
    headPegawai = addPegawai(headPegawai, "Andi", "P001");
    headPegawai = addPegawai(headPegawai, "Budi", "P002");
    headPegawai = addPegawai(headPegawai, "Citra", "P003");

    // 2. Tambahkan proyek ke pegawai
    addProyek(headPegawai, "P001", "Aplikasi Mobile", 12); // Untuk Andi
    addProyek(headPegawai, "P002", "Sistem Akuntansi", 8); // Untuk Budi
    addProyek(headPegawai, "P003", "E-commerce", 10);      // Untuk Citra

    // 3. Tambahkan proyek baru
    addProyek(headPegawai, "P001", "Analisis Data", 6);    // Untuk Andi

    // 4. Hapus proyek "Aplikasi Mobile" dari Andi
    removeProyek(headPegawai, "P001", "Aplikasi Mobile");

    // 5. Tampilkan data pegawai dan proyek mereka
    displayPegawai(headPegawai);

    return 0;
}

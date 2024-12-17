#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk data buku
typedef struct Buku {
    char judul[100];
    char pengembalian[15];
    struct Buku *next;
} Buku;

// Struktur untuk data anggota
typedef struct Anggota {
    char nama[50];
    char id[10];
    Buku *buku_head; // Pointer ke daftar buku yang dipinjam anggota
    struct Anggota *next;
} Anggota;

// Fungsi untuk menambahkan anggota baru
Anggota *tambahAnggota(Anggota *head, char nama[], char id[]) {
    Anggota *newAnggota = (Anggota *)malloc(sizeof(Anggota));
    strcpy(newAnggota->nama, nama);
    strcpy(newAnggota->id, id);
    newAnggota->buku_head = NULL; // Inisialisasi buku kosong
    newAnggota->next = head;
    return newAnggota;
}

// Fungsi untuk menambahkan buku ke anggota
void tambahBuku(Anggota *head, char id[], char judul[], char pengembalian[]) {
    Anggota *anggota = head;
    while (anggota != NULL) {
        if (strcmp(anggota->id, id) == 0) {
            Buku *newBuku = (Buku *)malloc(sizeof(Buku));
            strcpy(newBuku->judul, judul);
            strcpy(newBuku->pengembalian, pengembalian);
            newBuku->next = anggota->buku_head;
            anggota->buku_head = newBuku;
            return;
        }
        anggota = anggota->next;
    }
    printf("Anggota dengan ID %s tidak ditemukan.\n", id);
}

// Fungsi untuk menghapus anggota dan buku yang dipinjam
Anggota *hapusAnggota(Anggota *head, char id[]) {
    Anggota *current = head;
    Anggota *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            // Bebaskan semua buku yang dipinjam anggota
            Buku *buku = current->buku_head;
            while (buku != NULL) {
                Buku *temp = buku;
                buku = buku->next;
                free(temp);
            }

            // Hapus anggota
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Anggota dengan ID %s telah dihapus beserta buku yang dipinjam.\n", id);
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("Anggota dengan ID %s tidak ditemukan.\n", id);
    return head;
}

// Fungsi untuk menampilkan seluruh data anggota dan buku yang dipinjam
void tampilkanData(Anggota *head) {
    Anggota *current = head;
    while (current != NULL) {
        printf("Anggota: %s (ID: %s)\n", current->nama, current->id);
        Buku *buku = current->buku_head;
        while (buku != NULL) {
            printf("   - Buku: %s, Pengembalian: %s\n", buku->judul, buku->pengembalian);
            buku = buku->next;
        }
        current = current->next;
    }
}

// Main program
int main() {
    Anggota *head = NULL;

    // 1. Tambahkan data anggota
    head = tambahAnggota(head, "Rani", "A001");
    head = tambahAnggota(head, "Dito", "A002");
    head = tambahAnggota(head, "Vina", "A003");

    // 2. Tambahkan buku yang dipinjam
    tambahBuku(head, "A001", "Pemrograman C++", "01/12/2024");
    tambahBuku(head, "A002", "Algoritma Pemrograman", "15/12/2024");

    // 3. Tambahkan buku baru
    tambahBuku(head, "A001", "Struktur Data", "10/12/2024");

    // 4. Hapus anggota Dito beserta buku yang dipinjam
    head = hapusAnggota(head, "A002");

    // 5. Tampilkan seluruh data anggota dan buku yang dipinjam
    printf("\nData Anggota dan Buku yang Dipinjam:\n");
    tampilkanData(head);

    return 0;
}

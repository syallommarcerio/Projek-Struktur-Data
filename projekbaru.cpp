#include <iostream>
using namespace std;

// Struktur data untuk menyimpan info kontak
struct Kontak {
    string nama;
    string nomor;
    string email;
};

// Node untuk Double Linked List
struct Node {
    Kontak data;
    Node* next;
    Node* prev;
};

// Struktur Double Linked List
struct DoubleLL {
    Node* head = nullptr;
    Node* tail = nullptr;

    void tambahkontak(string nama, string nomor, string email) {
        Node* baru = new Node{{nama, nomor, email}, nullptr, nullptr};
        if (!head) {
            head = tail = baru;
        } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }
        cout << "Kontak berhasil ditambahkan!\n";
    }

    void tampilkankontak() {
        if (!head) {
            cout << "Belum ada kontak yang ditambahkan\n";
            return;
        }
        cout << "\n====== Daftar Kontak ======\n";
        Node* temp = head;
        while (temp) {
            cout << "Nama  : " << temp->data.nama << "\n";
            cout << "Nomor : " << temp->data.nomor << "\n";
            cout << "Email : " << temp->data.email << "\n\n";
            temp = temp->next;
        }
    }

    void sorting() {
        if (!head || !head->next) {
            cout << "Kontak tidak bisa diurutkan\n";
            return;
        }

        for (Node* i = head; i != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.nama < minNode->data.nama) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                Kontak temp = i->data;
                i->data = minNode->data;
                minNode->data = temp;
            }
        }
        cout << "Kontak berhasil diurutkan berdasarkan nama (A-Z).\n";
    }

    void search(string nama) {
        Node* tmp = head;
        while (tmp) {
            if (tmp->data.nama == nama) {
                cout << "Nama  : " << tmp->data.nama << "\n";
                cout << "Nomor : " << tmp->data.nomor << "\n";
                cout << "Email : " << tmp->data.email << "\n";
                return;
            }
            tmp = tmp->next;
        }
        cout << "Kontak tidak ditemukan!\n";
    }

bool hapusRekursif(Node* cur, string nama) {
    if (!cur) {
        return false;
    }

    if (cur->data.nama == nama) {
        if (cur == head) {
            head = cur->next;
        }
        if (cur == tail) {
            tail = cur->prev;
        }
        if (cur->prev) {
            cur->prev->next = cur->next;
        }
        if (cur->next) {
            cur->next->prev = cur->prev;
        }
        delete cur;
        return true;
    }
    return hapusRekursif(cur->next, nama);
}


    void hapus(string namaHapus) {
        if (!head) {
            cout << "Belum ada data!\n";
            return;
        }
        if (hapusRekursif(head, namaHapus)) {
            cout << "Kontak dengan nama \"" << namaHapus << "\" berhasil dihapus!\n";
        } else {
            cout << "Kontak dengan nama \"" << namaHapus << "\" tidak ditemukan!\n";
        }
    }
};

int main() {
    DoubleLL list;

    int pilihan = -1;
    string nama, nomor, email;

    while (pilihan != 0) {
        cout << "\n======= MENU KONTAK =======\n";
        cout << "1. Tambah Kontak\n";
        cout << "2. Tampilkan Semua Kontak\n";
        cout << "3. Urutkan Kontak (A-Z)\n";
        cout << "4. Cari Kontak (berdasarkan nama lengkap)\n";
        cout << "5. Hapus Kontak (berdasarkan nama)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan Nama  : ";
                getline(cin, nama);
                cout << "Masukkan Nomor : ";
                cin >> nomor;
                cin.ignore();
                cout << "Masukkan Email : ";
                getline(cin, email);
                list.tambahkontak(nama, nomor, email);
                break;

            case 2:
                list.tampilkankontak();
                break;

            case 3:
                list.sorting();
                list.tampilkankontak();
                break;

            case 4:
                cout << "Masukkan Nama: ";
                getline(cin, nama);
                list.search(nama);
                break;

            case 5:
                cout << "Masukkan Nama Kontak yang ingin dihapus: ";
                getline(cin, nama);
                list.hapus(nama);
                break;

            case 0:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// MEMBUAT SISTEM  KASIR SEDERHANA 

//Nuralfisyah 2400018147
struct MenuItem {
    string nama;
    int harga;
};

struct OrderItem {
    string nama;
    int harga;
    int jumlah;
};

struct Transaction {
    OrderItem* pesanan;
    int jumlahPesanan;
    int total;
    int bayar;
    int kembalian;
};

MenuItem menu[] = {
    {"Nasi Goreng", 20000},
    {"Mie Goreng", 18000},
    {"Ayam Bakar", 25000},
    {"Es Teh", 5000},
    {"Jus Jeruk", 10000}
};
int menuCount = 5;

void tampilkanMenu() {
    cout << "\nDaftar Menu:" << endl;
    for (int i = 0; i < menuCount; i++) {
        cout << i + 1 << ". " << menu[i].nama << " - Rp" << menu[i].harga << endl;
    }
}

//Naurah Mufidah Santosa 2400018111
void tampilkanInvoice(Transaction transaksi) {
    cout << "\n============================== Invoice ============================\n";
    cout << left << setw(20) << "Nama Menu" << setw(10) << "Jumlah" << setw(15) << "Harga" << setw(15) << "Subtotal" << endl;
    cout << "------------------------------------------------------------------\n";
    for (int i = 0; i < transaksi.jumlahPesanan; i++) {
        int subtotal = transaksi.pesanan[i].harga * transaksi.pesanan[i].jumlah;
        cout << left << setw(20) << transaksi.pesanan[i].nama
             << setw(10) << transaksi.pesanan[i].jumlah
             << setw(15) << transaksi.pesanan[i].harga
             << setw(15) << subtotal << endl;
    }
    cout << "------------------------------------------------------------------\n";
    cout << left << setw(35) << "Total:" << "Rp" << transaksi.total << endl;
    cout << left << setw(35) << "Bayar:" << "Rp" << transaksi.bayar << endl;
    cout << left << setw(35) << "Kembalian:" << "Rp" << transaksi.kembalian << endl;
    cout << "==================================================================\n";
}

void transaksiBaru() {
    cout << "\nTransaksi Baru" << endl;
    tampilkanMenu();

    int jumlahPesanan;
    cout << "Berapa menu yang ingin dipesan? ";
    cin >> jumlahPesanan;

    OrderItem* pesanan = new OrderItem[jumlahPesanan];

    for (int i = 0; i < jumlahPesanan; i++) {
        int pilihan;
        cout << "Pilih menu (nomor): ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > menuCount) {
            cout << "Pilihan tidak valid.\n";
            i--;
            continue;
        }

        cout << "Jumlah: ";
        cin >> pesanan[i].jumlah;
        pesanan[i].nama = menu[pilihan - 1].nama;
        pesanan[i].harga = menu[pilihan - 1].harga;
    }

    int total = 0;
    cout << "\nRincian Pesanan:" << endl;
    for (int i = 0; i < jumlahPesanan; i++) {
        int subtotal = pesanan[i].harga * pesanan[i].jumlah;
        total += subtotal;
        cout << pesanan[i].nama << " x" << pesanan[i].jumlah << " = Rp" << subtotal << endl;
    }
    cout << "Total: Rp" << total << endl;


//Nabila Putri Nuraini 2400018133
    int bayar;
    cout << "Bayar: ";
    cin >> bayar;

    if (bayar < total) {
        cout << "Uang tidak cukup. Transaksi dibatalkan.\n";
        delete[] pesanan;
        return;
    }

    cout << "Kembalian: Rp" << bayar - total << endl;
    cout << "Transaksi selesai.\n";

    Transaction transaksi = {pesanan, jumlahPesanan, total, bayar, bayar - total};

    // Tampilkan invoice
    tampilkanInvoice(transaksi);

    // Simpan transaksi ke file
    ofstream file("transaksi.txt", ios::app);
    file << "Transaksi Baru:\n";
    for (int i = 0; i < transaksi.jumlahPesanan; i++) {
        file << transaksi.pesanan[i].nama << " x" << transaksi.pesanan[i].jumlah << " = Rp" << transaksi.pesanan[i].harga * transaksi.pesanan[i].jumlah << endl;
    }
    file << "Total: Rp" << transaksi.total << endl;
    file << "Bayar: Rp" << transaksi.bayar << endl;
    file << "Kembalian: Rp" << transaksi.kembalian << endl;
    file.close();

    delete[] pesanan;
}

void menuUtama() {
    int pilihan;
    while (true) {
        cout << "\nKasir Rumah Makan" << endl;
        cout << "1. Lihat Menu" << endl;
        cout << "2. Transaksi Baru" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanMenu();
                break;
            case 2:
                transaksiBaru();
                break;
            case 3:
                cout << "Keluar dari program.\n";
                return;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
}

int main() {
    menuUtama();
    return 0;
}


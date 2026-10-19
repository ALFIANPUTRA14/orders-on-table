#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

struct Menu {
    string nama;
    int harga;
    int stok;
};

struct Pesanan {
    string nama;
    int harga;
    int jumlah;
};

Menu daftarMenu[8] = {
    {"Nasi Goreng", 25000, 10},
    {"Mie Goreng", 22000, 8},
    {"Ayam Geprek", 24000, 6},
    {"Sate Ayam", 28000, 5},
    {"Soto Ayam", 20000, 0},
    {"Es Teh Manis", 6000, 20},
    {"Es Jeruk", 8000, 15},
    {"Kopi Susu", 15000, 12}
};

void tampilkanMenu() {
    cout << "\n===== DAFTAR MENU =====\n";
    cout << left << setw(4) << "No" << setw(15) << "Menu" << setw(10) << "Harga" << "Stok\n";
    for (int i = 0; i < 8; i++) {
        cout << left << setw(4) << i + 1 << setw(15) << daftarMenu[i].nama << setw(10) << daftarMenu[i].harga;
        if (daftarMenu[i].stok > 0) {
            cout << daftarMenu[i].stok << endl;
        } else {
            cout << "HABIS" << endl;
        }
    }
}

int hitungTotal(Pesanan p[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total = total + p[i].harga * p[i].jumlah;
    }
    return total;
}

void loading() {
    cout << "\nMemvalidasi pembayaran ";
    for (int i = 0; i < 10; i++) {
        cout << "." << flush;
        clock_t mulai = clock();
        while (clock() - mulai < CLOCKS_PER_SEC * 3 / 10) {
        }
    }
    cout << " Berhasil!\n";
}

void cetakStruk(int meja, string area, string metode, int total, int bayar, Pesanan p[], int n) {
    time_t sekarang = time(0);
    cout << "\n======================================\n";
    cout << "            NOTA PEMBAYARAN\n";
    cout << "======================================\n";
    cout << "Waktu : " << ctime(&sekarang);
    cout << "Meja  : " << meja << " (" << area << ")\n";
    cout << "--------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(20) << p[i].nama << setw(5) << p[i].jumlah;
        cout << "Rp " << right << setw(8) << p[i].harga * p[i].jumlah << left << endl;
    }
    cout << "--------------------------------------\n";
    cout << left << setw(25) << "TOTAL" << "Rp " << right << setw(8) << total << left << endl;
    cout << setw(25) << "Metode" << metode << endl;
    if (metode == "Cash") {
        cout << setw(25) << "Uang diterima" << "Rp " << right << setw(8) << bayar << left << endl;
        cout << setw(25) << "Kembalian" << "Rp " << right << setw(8) << bayar - total << left << endl;
    }
    cout << "Status: LUNAS\n";
    cout << "======================================\n";
    cout << "   Terima kasih, selamat menikmati!\n";
}

int main() {
    Pesanan pesanan[20];
    int n = 0;
    int meja;
    string area;

    cout << "===== SELAMAT DATANG - ORDERS ON TABLE =====\n";

    do {
        cout << "Masukkan nomor meja (1-20): ";
        cin >> meja;
        if (meja < 1 || meja > 20) {
            cout << "Nomor meja tidak valid!\n";
        }
    } while (meja < 1 || meja > 20);

    if (meja <= 10) {
        area = "Indoor";
    } else {
        area = "Outdoor";
    }
    cout << "Meja " << meja << " - area " << area << endl;

    tampilkanMenu();

    char lagi = 'y';
    while ((lagi == 'y' || lagi == 'Y') && n < 20) {
        int pilih;
        do {
            cout << "\nPilih nomor menu (1-8): ";
            cin >> pilih;
            if (pilih < 1 || pilih > 8) {
                cout << "Menu tidak tersedia!\n";
            }
        } while (pilih < 1 || pilih > 8);

        if (daftarMenu[pilih - 1].stok == 0) {
            cout << "Stok " << daftarMenu[pilih - 1].nama << " habis, pilih menu lain.\n";
            continue;
        }

        int jumlah;
        do {
            cout << "Jumlah (maksimal " << daftarMenu[pilih - 1].stok << "): ";
            cin >> jumlah;
            if (jumlah < 1 || jumlah > daftarMenu[pilih - 1].stok) {
                cout << "Jumlah tidak valid!\n";
            }
        } while (jumlah < 1 || jumlah > daftarMenu[pilih - 1].stok);

        pesanan[n].nama = daftarMenu[pilih - 1].nama;
        pesanan[n].harga = daftarMenu[pilih - 1].harga;
        pesanan[n].jumlah = jumlah;
        n++;
        daftarMenu[pilih - 1].stok = daftarMenu[pilih - 1].stok - jumlah;
        cout << "Ditambahkan: " << jumlah << " x " << daftarMenu[pilih - 1].nama;
        cout << " (sisa stok " << daftarMenu[pilih - 1].stok << ")\n";

        cout << "Pesan lagi? (y/n): ";
        cin >> lagi;
    }

    int total = hitungTotal(pesanan, n);
    cout << "\nTotal pesanan: Rp " << total << endl;

    int pilihBayar;
    cout << "\nMetode pembayaran:\n";
    cout << "1. QRIS\n";
    cout << "2. Cash\n";
    do {
        cout << "Pilih metode (1-2): ";
        cin >> pilihBayar;
        if (pilihBayar < 1 || pilihBayar > 2) {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihBayar < 1 || pilihBayar > 2);

    string metode;
    int bayar = total;

    if (pilihBayar == 1) {
        metode = "QRIS";
        cout << "Silakan scan QRIS untuk membayar Rp " << total << endl;
    } else {
        metode = "Cash";
        bayar = 0;
        while (bayar < total) {
            cout << "Masukkan uang pembayaran: ";
            cin >> bayar;
            if (bayar < total) {
                cout << "Uang kurang Rp " << total - bayar << "!\n";
            }
        }
    }

    loading();
    cetakStruk(meja, area, metode, total, bayar, pesanan, n);

    return 0;
}
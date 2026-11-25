#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;
 
const int kapasitasAwal = 5;
const int batasMenipis = 10;

struct Barang
{
    string kode;
    string nama;
    int stok;
    int harga;
};

Barang *daftarBarang = nullptr;
int jumlahData = 0;
int kapasitas = 0;
long long totalPenjualan = 0;

//aray dinamis
void PerbesarArray(bool munculPesan = true) {
    int kapasitasBaru = (kapasitas == 0) ? kapasitasAwal : kapasitas * 2;
    Barang *arrayBaru = new Barang[kapasitasBaru];
    for (int i = 0; i < jumlahData; i++)
        arrayBaru[i] = daftarBarang[i];

    delete[] daftarBarang;
    daftarBarang = arrayBaru;
    kapasitas = kapasitasBaru;
    if (munculPesan)
        cout << "[Info!] Kapasitas Array diperbesar menjadi " << kapasitas << "\n";
}

// FUNGSI TAMBAHAN/BANTUAN
string hurufKecil(string s) {
    for (int i = 0; i < (int)s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}

int bacaAngka(const string &tanya) {
    int x;
    while (true)
    {
        cout << tanya;
        if (cin >> x && x >= 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid, silahkan masukkan angka dari >= 0.\n";
    }
}


void garis() { cout << string(60, '-') << "\n"; }

void header() {
    garis();
    cout << left << setw(5) << "No" << setw(10) << "Kode" << setw(25) << "Nama Barang" << setw(8) << "Stok" << "Harga\n";
    garis();
}

void tampilkanBaris(int urutan, const Barang &brg) {
    cout << left << setw(5) << urutan << setw(10) << brg.kode << setw(25) << brg.nama << setw(8) << brg.stok << "Rp" << brg.harga << "\n";
}

// FITUR
void tambahBarang() {
    Barang baru;
    cout << "Kode Barang : ";
    getline(cin, baru.kode);

    for (int i = 0; i < jumlahData; i++)
    {
        if (hurufKecil(daftarBarang[i].kode) == hurufKecil(baru.kode))
        {
            cout << "Kode sudah dipakai!\n";
            return;
        }
    }
    cout << "Nama Barang : ";
    getline(cin, baru.nama);
    baru.stok  = bacaAngka("Stok        : ");
    baru.harga = bacaAngka("Harga (Rp) : ");

    if (jumlahData >= kapasitas)
        PerbesarArray();

    daftarBarang[jumlahData++] = baru;
    cout << "Barang berhasil ditambahkan.\n";
}

void tampilSemua() {
    if (jumlahData == 0) {
        cout << "Belum ada data barang.\n";
        return;
    }
    header();
    for (int i = 0; i < jumlahData; i++)
        tampilkanBaris(i + 1, daftarBarang[i]);
    garis();
}

// SEARCHING
// cari berdasarkan kode (cocok persis), return indeks atau -1
int carikode(const string &kodecari) {
    string target = hurufKecil(kodecari);
for (int i = 0; i < jumlahData; i++)
    {
        if (hurufKecil(daftarBarang[i].kode) == target)
            return i;
    }
    return -1;
}

// mencari barang lewat KODE maupun NAMA
int cariBarang(const string &kunci) {
    if (kunci.empty()) return -1;

    // cek cocok ga dengan kode barang
    int idxKode = carikode(kunci);
    if (idxKode != -1) return idxKode;

    // cek dgn nama barang (persis atau sebagian)
    string target = hurufKecil(kunci);
    int *indeksCocok = new int[jumlahData > 0 ? jumlahData : 1];  
    int hitung = 0;
    int hasil = -1;

    for (int i = 0; i < jumlahData; i++)
    {
        string namaKecil = hurufKecil(daftarBarang[i].nama);
        if (namaKecil == target)  
        {
            delete[] indeksCocok;
            return i;
        }
        if (namaKecil.find(target) != string::npos)
            indeksCocok[hitung++] = i;
    }

    if (hitung == 1)
    {
        hasil = indeksCocok[0];
    }
    else if (hitung > 1)
    {
        // lebih dari 1 barang cocok
        cout << "Ditemukan beberapa barang yang mirip:\n";
        header();
        for (int i = 0; i < hitung; i++)
            tampilkanBaris(i + 1, daftarBarang[indeksCocok[i]]);
        garis();

        string kodePilih;
        cout << "Masukkan kode barang dari daftar di atas: ";
        getline(cin, kodePilih);
        hasil = carikode(kodePilih);
    }

    delete[] indeksCocok;  
    return hasil;
}

void menuCari() {
    string kata;
    cout << "Masukkan kode atau nama barang: ";
    getline(cin, kata);
    string target = hurufKecil(kata);

    bool ketemu = false;
    for (int i = 0; i < jumlahData; i++)
    {
        bool cocokKode = (hurufKecil(daftarBarang[i].kode) == target);
        bool cocokNama = (hurufKecil(daftarBarang[i].nama).find(target) != string::npos);

        if (cocokKode || cocokNama)
        {
            if (!ketemu) header();
            tampilkanBaris(i + 1, daftarBarang[i]);
            ketemu = true;
        }
    }

    if (ketemu) garis();
    else cout << "Barang \"" << kata << "\" tidak ditemukan.\n";
}

// SORTING
void tukar(Barang *brgA, Barang *brgB) {
    Barang temp = *brgA;
    *brgA = *brgB;
    *brgB = temp;
}

void urutkanStok(Barang *array, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < jumlah; j++)
        {
            if (array[j].stok < array[min].stok)
                min = j;
        }
        if (min != i) tukar(&array[i], &array[min]);
    }
}

void tampilUrutStok() {
    if (jumlahData == 0) {
        cout << "Belum ada data barang.\n";
        return;
    }
    Barang *salinan = new Barang[jumlahData];
    for (int i = 0; i < jumlahData; i++)
        salinan[i] = daftarBarang[i];

    urutkanStok(salinan, jumlahData);

    cout << "Daftar barang diurutkan dari stok paling sedikit:\n";
    header();
    for (int i = 0; i < jumlahData; i++)
        tampilkanBaris(i + 1, salinan[i]);
    garis();

    delete[] salinan;
}

void laporanMenipis() {
    if (jumlahData == 0) {
        cout << "Belum ada data barang.\n";
        return;
    }
    Barang *salinan = new Barang[jumlahData];
    int n = 0;
    for (int i = 0; i < jumlahData; i++)
        if (daftarBarang[i].stok <= batasMenipis)
            salinan[n++] = daftarBarang[i];

    if (n == 0) {
        cout << "Semua stok aman (di atas " << batasMenipis << ").\n";
        delete[] salinan;
        return;
    }
    urutkanStok(salinan, n);
    cout << "!! LAPORAN STOK MENIPIS (stok <= " << batasMenipis << ") !!\n";
    header();
    for (int i = 0; i < n; i++)
        tampilkanBaris(i + 1, salinan[i]);
    garis();
    cout << n << " barang perlu segera direstok.\n";

    delete[] salinan;
}

void ubahStok() {
    string input;
    cout << "Kode atau nama barang: ";
    getline(cin, input);
    int idx = cariBarang(input);
    if (idx == -1) {
        cout << "Barang tidak ditemukan.\n";
        return;
    }
    cout << "Barang: " << daftarBarang[idx].nama << " [" << daftarBarang[idx].kode << "] " << "(stok sekarang " << daftarBarang[idx].stok << ")\n";
    daftarBarang[idx].stok = bacaAngka("Stok baru: ");
    cout << "Stok diperbarui.\n";
}

void hapusBarang() {
    string input;
    cout << "Kode atau nama barang yang dihapus: ";
    getline(cin, input);
    int idx = cariBarang(input);
    if (idx == -1) {
        cout << "Barang tidak ditemukan.\n";
        return;
    }
    string namaTerhapus = daftarBarang[idx].nama;
    for (int i = idx; i < jumlahData - 1; i++)
        daftarBarang[i] = daftarBarang[i + 1];
    jumlahData--;
    cout << "Barang \"" << namaTerhapus << "\" dihapus.\n";
}

void jualBarang() {
    string input;
    cout << "Kode atau nama barang yang dijual: ";
    getline(cin, input);
    int idx = cariBarang(input);
    if (idx == -1) {
        cout << "Barang tidak ditemukan.\n";
        return;
    }

    Barang *b = &daftarBarang[idx]; 
    cout << "Barang : " << b->nama << " [" << b->kode << "]\n" << "Harga  : Rp" << b->harga << "\n" << "Stok   : " << b->stok << "\n";

    if (b->stok == 0) {
        cout << "Stok habis, tidak bisa dijual.\n";
        return;
    }

    int qty = bacaAngka("Jumlah dijual: ");
    if (qty <= 0) {
        cout << "Jumlah harus lebih dari 0.\n";
        return;
    }
    if (qty > b->stok) {
        cout << "Stok tidak cukup! Stok tersedia hanya " << b->stok << ".\n";
        return;
    }

    b->stok -= qty;
    totalPenjualan += (long long)qty * b->harga;

    garis();
    cout << "NOTA PENJUALAN\n";
    cout << b->nama << "  " << qty << " x Rp" << b->harga << " = Rp" << (long long)qty * b->harga << "\n";
    garis();
    cout << "Sisa stok " << b->nama << ": " << b->stok << "\n";
    if (b->stok <= batasMenipis)
        cout << "PERHATIAN: stok " << b->nama << " menipis, segera restok!\n";
}

void dataAwal() {
    Barang contoh[] = {
        {"B001", "Beras 5kg",      25, 68000},
        {"B002", "Minyak Goreng",   6, 18000},
        {"B003", "Gula Pasir",     12, 16000},
        {"B004", "Mie Instan",      4,  3500},
        {"B005", "Teh Celup",       9,  7000},
        {"B006", "Sabun Mandi",    30,  4500},
    };
    int n = sizeof(contoh) / sizeof(contoh[0]);
    for (int i = 0; i < n; i++)
    {
        if (jumlahData >= kapasitas)
            PerbesarArray(false); 
        daftarBarang[jumlahData++] = contoh[i];
    }
}

int main() {
    dataAwal();
    int pilih;
    do
    {
        cout << "\n===== MANAJEMEN STOK TOKO =====\n"
             << "1. Tambah barang\n"
             << "2. Tampilkan semua barang\n"
             << "3. Cari barang (kode/nama)\n"
             << "4. Urutkan stok (paling sedikit dulu)\n"
             << "5. Laporan stok menipis\n"
             << "6. Ubah stok barang\n"
             << "7. Hapus barang\n"
             << "8. Jual barang\n"
             << "0. Keluar\n"
             << "Pilih menu: ";
        if (!(cin >> pilih)) {
            cin.clear();
            pilih = -1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        switch (pilih)
        {
            case 1: tambahBarang();   break;
            case 2: tampilSemua();    break;
            case 3: menuCari();       break;
            case 4: tampilUrutStok(); break;
            case 5: laporanMenipis(); break;
            case 6: ubahStok();       break;
            case 7: hapusBarang();    break;
            case 8: jualBarang();     break;
            case 0:
                cout << "Total penjualan sesi ini: Rp" << totalPenjualan << "\n";
                cout << "Terima kasih!\n";
                break;
            default: cout << "Menu tidak valid.\n";
        }
    } while (pilih != 0);

    delete[] daftarBarang;
    daftarBarang = nullptr;
    return 0;
}

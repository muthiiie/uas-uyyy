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
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

Barang *daftarBarang + nullptr;
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

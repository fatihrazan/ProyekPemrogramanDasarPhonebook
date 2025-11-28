#include "DaftarKontak.h"
#include <string>
using namespace std;

DaftarKontak::DaftarKontak(string nama, string nomor){
    Nama = nama;
    Nomor = nomor;
}

string DaftarKontak::getNama() const{
    return Nama;
}
string DaftarKontak::getNomor() const{
    return Nomor;
}

void DaftarKontak::setNama(const string &nama){
    Nama = nama;
}
void DaftarKontak::setNomor(const string &nomor){
    Nomor = nomor;
}
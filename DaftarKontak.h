#ifndef KONTAK_H
#define KONTAK_H

#include <string>
using namespace std;

class DaftarKontak{
public:
    DaftarKontak(string nama="", string nomor="");

    string getNama() const;
    string getNomor() const;

    void setNama(const string &nama);
    void setNomor(const string &nomor);

private:
    string Nama;
    string Nomor;
};

#endif
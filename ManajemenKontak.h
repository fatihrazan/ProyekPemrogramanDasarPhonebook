#ifndef MANAJEMEN_H
#define MANAJEMEN_H

#include <vector>
#include <string>
#include "DaftarKontak.h"


class ManajemenKontak{
public:
    ManajemenKontak();

    void muatKontak(const string& filename);
    void simpanKontak(const string& filename);

    void tambahKontak();
    void tampilkanKontak() const;
    void cariKontak() const;
    void editKontak();
    void hapusKontak();
    void exportKontak();
    void menuLoop();

private:
    vector <DaftarKontak> database;
};

#endif
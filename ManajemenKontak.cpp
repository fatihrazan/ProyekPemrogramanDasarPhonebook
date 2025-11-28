#include "ManajemenKontak.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <filesystem>
using namespace std;
namespace fs = filesystem;


const string FILE_NAME = "daftarkontak.txt";
const char DELIMITER =',';

ManajemenKontak::ManajemenKontak(){
    muatKontak(FILE_NAME);
}

void ManajemenKontak::muatKontak(const string& filename){
    ifstream inFile(filename);

    if(inFile.is_open()){
        string line;
        while(getline(inFile,line)){
            stringstream ss(line);
            string temp_nama;
            string temp_notelpon;

            if(getline(ss,temp_nama,DELIMITER)){
                if(getline(ss,temp_notelpon)){
                    database.push_back(DaftarKontak(temp_nama,temp_notelpon));
                }
            }
        }
        inFile.close();
    } else{
        cout << "Peringatan: File " << filename << " belum ada. Memulai dengan data kosong." << endl;
    }
}

void ManajemenKontak::simpanKontak(const string& filename){
    ofstream outFile(filename, ios::trunc);

    if(outFile.is_open()){
        for(const auto& k: database){
            outFile << k.getNama() << DELIMITER << k.getNomor() << endl;
        }
        outFile.close();
    }else{
        cerr << "\nERROR: Gagal membuka file untuk penulisan: " <<filename <<endl;
    }
}

void ManajemenKontak::tambahKontak(){
    string input_nama;
    string input_nomor;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n----Input Kontak Baru----" << endl;
    cout << "Masukkan Nama: ";
    getline(cin, input_nama);
    cout << "Masukkan Nomor Hp: ";
    getline(cin, input_nomor);
    
    if(!input_nomor.empty() && !input_nomor.empty()){
        cout <<"Kontak '" << input_nama << "' berhasil disimpan di aplikasi" << endl;
        database.push_back(DaftarKontak(input_nama,input_nomor));
    }else{
        cout <<"Isikan dengan lengkap nama dan nomor kontak!";
        tambahKontak();
    }
    simpanKontak(FILE_NAME);

}

void ManajemenKontak::tampilkanKontak() const{
    cout << "\n----DAFTAR KONTAK----" << endl;

    if(database.empty()){
        cout << "Tidak ada kontak di dalam file ini" << endl;
    }else{
        for(const auto& k: database){
            cout << "NAMA: " << k.getNama() << endl;
            cout << "NOMOR: " << k.getNomor() << endl;
            cout << "-----------------" << endl;
        }
    }
}

void ManajemenKontak::cariKontak() const{
    bool found = false;
    string temp_kontak;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout <<"Masukkan Nama Kontak: ";
    getline(cin, temp_kontak);
    cout <<"-----Hasil Pencarian untuk Kontak '" << temp_kontak <<"'-----" << endl;
    for(const auto& k: database){
        if(k.getNama() == temp_kontak){
            cout << "Kontak: " << k.getNama() << endl;
            cout << "Nomor: " << k.getNomor() << endl;
            found = true;
        }
    }
    if(!found){
        cout << "Kontak Tidak Ditemukan, silahkan tambahkan kontak terlebih dahulu" << endl;
    }
    cout << "-------------------------" << endl;
}

void ManajemenKontak::editKontak(){
    string nama_dicari;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n----EDIT KONTAK----" << endl;
    cout << "Masukkan Nama Kontak yang akan di-EDIT: ";
    getline(cin, nama_dicari);

    bool found = false;
    for (auto &k : database) { 
        if (k.getNama() == nama_dicari) {
            cout << "\nKontak Ditemukan:" << endl;
            cout << "NAMA: " << k.getNama() << endl;
            cout << "NOMOR: " << k.getNomor() << endl;
            cout << "-----------------" << endl;

            string input_nama_baru;
            string input_nomor_baru;

            cout << "\nMasukkan Nama BARU (Kosongkan jika tidak diubah): ";
            getline(cin, input_nama_baru);

            cout << "Masukkan Nomor Hp BARU (Kosongkan jika tidak diubah): ";
            getline(cin, input_nomor_baru);

            if (!input_nama_baru.empty()) {
                k.setNama(input_nama_baru);
            }
            if (!input_nomor_baru.empty()) {
                k.setNomor(input_nomor_baru);
            }
            
            simpanKontak(FILE_NAME);
            cout << "\nSukses: Kontak berhasil diubah menjadi:" << endl;
            cout << "NAMA: " << k.getNama() << endl;
            cout << "NOMOR: " << k.getNomor() << endl;
            cout << "-----------------" << endl;
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "ERROR: Kontak '" << nama_dicari << "' tidak ditemukan." << endl;
    }
}

void ManajemenKontak::hapusKontak(){
    string nama_dicari;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n----HAPUS KONTAK----" << endl;
    cout << "Masukkan Nama Kontak yang akan di-HAPUS: ";
    getline(cin, nama_dicari);

    bool found = false;
    for (auto it = database.begin(); it != database.end(); ++it) {
        if (it->getNama() == nama_dicari) {
            cout << "\nKontak Ditemukan dan Dihapus:" << endl;
            cout << "NAMA: " << it->getNama() << endl;
            cout << "NOMOR: " << it->getNomor() << endl;
            cout << "-----------------" << endl;
            
            database.erase(it); // FUNGSI INTI PENGHAPUSAN
            
            simpanKontak(FILE_NAME);
            cout << "Sukses: Kontak '" << nama_dicari << "' telah dihapus dari memori." << endl;
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "ERROR: Kontak '" << nama_dicari << "' tidak ditemukan." << endl;
    }
}

void ManajemenKontak::exportKontak(){
    string target_kontak;
    string nama_file;
    int i;
    bool found = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "tentukan nama file anda (belakang ditambahkan .txt): ";
    getline(cin,nama_file);
    fs::path p = nama_file;

    vector<DaftarKontak> export_kontak;

    cout << "Berapa kontak yang ingin di export?: ";
    cin >> i;

    while(i > 0){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Masukkan Nama Kontak: ";
        getline(cin, target_kontak);
        for(const auto& k: database){
            if(k.getNama() == target_kontak){
                DaftarKontak x = k;
                export_kontak.push_back(x);
                found = true;
            }
        }
        if(!found){
            cout << "Kontak yang anda cari tidak ditemukan silahkan cari kontak lain!" << endl;
            continue;
        }
        i--;
    }

    ofstream outFile(nama_file);
    if(outFile.is_open()){
        for(const auto& k: export_kontak){
            outFile << k.getNama() << DELIMITER << k.getNomor() << endl;
        }
        outFile.close();
        cout << "File '" << nama_file <<"' berhasil diexport silahkan di cek di " << fs::absolute(p) << endl;
    }else{
        cerr << "\nERROR: Gagal membuka file untuk penulisan: " <<nama_file <<endl;
    } 
}

void ManajemenKontak::menuLoop(){
     int i;
    cout << "----Aplikasi Phonebook----" << endl;
    do{
        cout <<"--MENU--"<<endl;
        cout <<"1. Tambah Kontak" << endl;
        cout <<"2. Tampilkan Kontak" << endl;
        cout <<"3. Cari Kontak"<< endl;
        cout <<"4. Edit Kontak" << endl;
        cout <<"5. Hapus Kontak" << endl;
        cout <<"6. Export Kontak" << endl;
        cout <<"7. Keluar" << endl;

        cout << "Masukkan angka: ";
        cin >> i;
        switch (i)
        {
        case 1:
            tambahKontak();
            break;
        case 2:
            tampilkanKontak();
            break;
        case 3:
            cariKontak();
            break;
        case 4:
            editKontak();
            break;
        case 5:
            hapusKontak();
            break;
        case 6:
            exportKontak();
            break;
        case 7:
            cout << "Keluar dari Program" << endl;
            break;
        default:
            cout <<"Masukkan angka sesuai pilihan di menu" << endl;
            break;
        }
    } while(i != 7);
}